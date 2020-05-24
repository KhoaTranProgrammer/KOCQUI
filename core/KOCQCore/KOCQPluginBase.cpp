/*
 * MIT License
 * 
 * Copyright (c) 2020 KhoaTran Programmer
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/******************
 * VERSION: 1.0.1 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file implements basic methods/properties to control Plugin  *
 * in KOCQ                                                          *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version implements method to manipulate KOCQ      *
 *        Plugin                                                    *
 * 1.0.1: May-25-2020                                               *
 *        Update the method to load icon and plugin screen by       *
 *        resource instead of local file                            *
 *******************************************************************/

#include "KOCQPluginBase.h"

KOCQPluginBase::KOCQPluginBase(QQmlEngine* engine, QObject* rootObject, QUrl source, QString name, QString defaultPath, QObject* pluginManagerObject)
{
    m_engine = engine;
    m_source = source;
    m_quickItemIcon = NULL;
    m_pluginName = name;
    m_qmlRootObject = rootObject;
    m_pluginManagerObject = pluginManagerObject;
    m_pluginstate = KOCQ_INIT;
    m_defaultPath = defaultPath;
    QObject::connect(m_pluginManagerObject, SIGNAL(addIconSignal(QVariant)),
                       this, SLOT(addIconSlot(QVariant)));
}

QObject* KOCQPluginBase::getRootObject() const
{
    return m_qmlRootObject;
}

QQmlEngine* KOCQPluginBase::getEngine() const
{
    return m_engine;
}

QUrl KOCQPluginBase::getUrlSource() const
{
    return m_source;
}

QString KOCQPluginBase::getPluginName() const
{
    return m_pluginName;
}

QString KOCQPluginBase::getDefaultPath() const
{
    return m_defaultPath;
}

QQuickItem* KOCQPluginBase::getPluginQuickItem() const
{
    return m_quickItemPlugin;
}

QQmlContext* KOCQPluginBase::getPluginContext() const
{
    return m_contextPlugin;
}

void KOCQPluginBase::addIcon(const QVariant &v, const QString icon)
{
    if(m_pluginstate == KOCQ_INIT) // First time load Icon
    {
        QQuickItem *parent = qobject_cast<QQuickItem*>(v.value<QObject*>());
        QString text = "\"" + getPluginName() + "\"";
        QString iconUrl = "\"" + icon + "\"";
        QString data = "import QtQuick 2.0; "
                       "Item { "
                            "anchors.fill: parent; "
                            "signal iConClicked(); "
                            "Rectangle { "
                                "id: id_name; "
                                "color: \"transparent\";"
                                "anchors.bottom: parent.bottom; "
                                "anchors.left: parent.left; "
                                "anchors.right: parent.right; "
                                "height: parent.height * 0.15; "
                                "Text {"
                                    "anchors.centerIn: parent; "
                                    "text: " + text + ";"
                                    "font.pointSize: parent.height * 0.9; "
                                "}"
                            "}"
                            "Image { "
                                 "anchors.top: parent.top; "
                                 "anchors.left: parent.left; "
                                 "anchors.right: parent.right; "
                                 "anchors.bottom: id_name.top; "
                                 "anchors.margins: parent.height * 0.01; "
                                 "fillMode: Image.PreserveAspectFit; "
                                 "source: " + iconUrl + "; "
                                 "onStatusChanged: { "
                                    "if (status == Image.Error) {"
                                        "source = \"image/380d597942266fe55226d719d98070a8.png\""
                                    "}"
                                 "}"
                                 "MouseArea {"
                                    "anchors.fill: parent; "
                                    "onClicked: { iConClicked() }"
                                 "}"
                            "}"
                       "}";

        QQmlComponent *component = new QQmlComponent(getEngine());
        component->setData(data.toUtf8(), getUrlSource());
        m_quickItemIcon = qobject_cast<QQuickItem*>(component->create());
        m_quickItemIcon->setParentItem(parent);
        QObject::connect(m_quickItemIcon, SIGNAL(iConClicked()),
                           this, SLOT(iConClicked()));
        m_pluginManagerObject->disconnect(this);

        m_pluginstate = KOCQ_ICONLOAD;
    }
}

void KOCQPluginBase::loadPlugin(const QString qmlFile)
{
    switch (m_pluginstate)
    {
        case KOCQ_ICONLOAD:
        {
            m_contextPlugin = getEngine()->rootContext();
            m_component = new QQmlComponent(getEngine(), QUrl(qmlFile));
            m_quickItemPlugin = qobject_cast<QQuickItem*>(m_component->create());

            m_loader = getRootObject()->findChild<QObject*>("PluginLoader");
            if (m_loader)
            {
                m_loader->setProperty("sourceComponent", QVariant::fromValue<QQmlComponent*>(m_component));
                m_pluginstate = KOCQ_PLUGINLOAD;
                QObject::connect(getRootObject(), SIGNAL(homeSignal()),
                                   this, SLOT(unloadPluginSlot()));
                onPluginLoad();
            }
            break;
        }
        case KOCQ_PLUGINUNLOAD:
        {
            if (m_loader)
            {
                m_loader->setProperty("sourceComponent", QVariant::fromValue<QQmlComponent*>(m_component));
                m_pluginstate = KOCQ_PLUGINLOAD;
                QObject::connect(getRootObject(), SIGNAL(homeSignal()),
                                   this, SLOT(unloadPluginSlot()));
                onPluginLoad();
            }
            break;
        }
        default:
            break;
    }
}

void KOCQPluginBase::unloadPluginSlot()
{
    m_loader->setProperty("sourceComponent", QVariant::fromValue<QQmlComponent*>(NULL));
    QObject::disconnect(getRootObject(), SIGNAL(homeSignal()), 0, 0);
    m_pluginstate = KOCQ_PLUGINUNLOAD;
}
