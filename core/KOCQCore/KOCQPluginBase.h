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
 * VERSION: 1.0.2 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file defines basic methods/properties to control Plugin     *
 * in KOCQ                                                          *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version supports KOCQPLUGINSTATE, method to       *
 *        manipulate KOCQ Plugin                                    *
 * 1.0.1: Aug-08-2020                                               *
 *        Provide methods to get plugin state: getPluginState,      *
 *        getState_UNINIT, getState_INIT, getState_ICONLOAD,        *
 *        getState_PLUGINLOAD, getState_PLUGINUNLOAD                *
 * 1.0.2: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot, addIcon.*
 *        Add method to load plugin in Grid/List/Path view.         *
 *        setupIconConnection when icon view type change.           *
 *******************************************************************/

#ifndef KOCQPLUGINBASE_H
#define KOCQPLUGINBASE_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QtQuick>
#include "KOCQCore_Global.h"

class KOCQCORESHARED_EXPORT KOCQPluginBase : public QObject
{
    Q_OBJECT
    Q_ENUMS(KOCQPLUGINSTATE)
protected:
    KOCQPluginBase(QQmlEngine* engine, QObject* rootObject, QUrl source, QString name, QString defaultPath, QObject* pluginManagerObject);

public:
    enum KOCQPLUGINSTATE
    {
        KOCQ_UNINIT,        // Default state when nothing load
        KOCQ_INIT,          // Instance is created, nothing done
        KOCQ_ICONLOAD,      // Icon is loaded
        KOCQ_PLUGINLOAD,    // When plugin is loaded
        KOCQ_PLUGINUNLOAD,  // Plugin is unloaded after loading
    };

    QObject* getRootObject() const;
    QQmlEngine* getEngine() const;
    QUrl getUrlSource() const;
    QString getPluginName() const;
    QString getDefaultPath() const;
    QQuickItem* getPluginQuickItem() const;
    QQmlContext* getPluginContext() const;
    void setupIconConnection();

    void addIcon(const QVariant &v, const QString icon, const QString type, const QString pluginDetail);
    void addIcon4GridView(const QVariant &v, const QString icon);
    void addIcon4ListView(const QVariant &v, const QString icon, const QString pluginDetail);
    void addIcon4PathView(const QVariant &v, const QString icon);
    void loadPlugin(const QString qmlFile);
    virtual void onPluginLoad() = 0;

public slots:
    virtual void addIconSlot(const QVariant &v, const QString &type) = 0;
    virtual void iConClicked() = 0;
    void unloadPluginSlot();
    KOCQPLUGINSTATE getPluginState() const;
    KOCQPLUGINSTATE getState_UNINIT() const { return KOCQ_UNINIT; }
    KOCQPLUGINSTATE getState_INIT() const { return KOCQ_INIT; }
    KOCQPLUGINSTATE getState_ICONLOAD() const { return KOCQ_ICONLOAD; }
    KOCQPLUGINSTATE getState_PLUGINLOAD() const { return KOCQ_PLUGINLOAD; }
    KOCQPLUGINSTATE getState_PLUGINUNLOAD() const { return KOCQ_PLUGINUNLOAD; }

private:
    KOCQPluginBase(); // private default constructor
    KOCQPluginBase(const KOCQPluginBase&); // prevent copying
    KOCQPluginBase& operator=(const KOCQPluginBase&);

    KOCQPLUGINSTATE m_pluginstate = KOCQ_UNINIT;
    QQmlComponent* m_component;
    QQmlEngine* m_engine;
    QUrl m_source;
    QQuickItem* m_quickItemIcon;
    QQuickItem* m_quickItemPlugin;
    QQmlContext* m_contextPlugin;
    QString m_pluginName;
    QObject* m_qmlRootObject;
    QObject* m_pluginManagerObject;
    QObject* m_loader;
    QString m_defaultPath = NULL;
};

#endif // KOCQPLUGINBASE_H
