#include "KOCQPluginBase.h"

KOCQPluginBase::KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source, QString name, QString defaultPath)
{
    m_engine = engine;
    m_source = source;
    m_quickItemIcon = NULL;
    m_pluginName = name;
    m_parent = parent;
    m_pluginstate = KOCQ_INIT;
    m_defaultPath = defaultPath;
    QObject::connect(parent, SIGNAL(addIconSignal(QVariant)),
                       this, SLOT(addIconSlot(QVariant)));
}

QObject* KOCQPluginBase::getRootObject() const
{
    return m_parent;
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
        QString iconUrl = "\"file:" + getDefaultPath() + "/" + icon + "\"";
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

        m_pluginstate = KOCQ_ICONLOAD;
    }
}

void KOCQPluginBase::loadPlugin(const QString qmlFile)
{
    switch (m_pluginstate)
    {
        case KOCQ_ICONLOAD:
        {
            m_contextPlugin = new QQmlContext(getEngine()->rootContext());
            m_component = new QQmlComponent(getEngine(), QUrl::fromLocalFile(getDefaultPath() + "/" + qmlFile));
            m_quickItemPlugin = qobject_cast<QQuickItem*>(m_component->create(m_contextPlugin));

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
