#include "KOCQPluginBase.h"

KOCQPluginBase::KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source, QString name)
{
    m_engine = engine;
    m_source = source;
    m_quickItemIcon = NULL;
    m_pluginName = name;
    m_parent = parent;
    m_pluginstate = KOCQ_INIT;
    QObject::connect(parent, SIGNAL(qmlSignal(QVariant)),
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

        m_pluginstate = KOCQ_ICONLOAD;
    }
}

void KOCQPluginBase::loadPlugin(const QUrl qmlFile)
{
    switch (m_pluginstate)
    {
        case KOCQ_ICONLOAD:
        {
            m_component = new QQmlComponent(getEngine(), qmlFile);
            m_component->create();
            m_loader = getRootObject()->findChild<QObject*>("PluginLoader");
            if (m_loader)
            {
                m_loader->setProperty("sourceComponent", QVariant::fromValue<QQmlComponent*>(m_component));
            }
            break;
        }
        case KOCQ_PLUGINUNLOAD:
        {
            if (m_loader)
            {
                m_loader->setProperty("sourceComponent", QVariant::fromValue<QQmlComponent*>(m_component));
            }
            break;
        }
        default:
            break;
    }

}
