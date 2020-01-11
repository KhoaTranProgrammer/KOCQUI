#include "KOCQPluginBase.h"

KOCQPluginBase::KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source)
{
    m_engine = engine;
    m_source = source;
    m_quickItemIcon = NULL;
    QObject::connect(parent, SIGNAL(qmlSignal(QVariant)),
                       this, SLOT(addIconSlot(QVariant)));
}

QQmlEngine* KOCQPluginBase::getEngine() const
{
    return m_engine;
}

QUrl KOCQPluginBase::getUrlSource() const
{
    return m_source;
}

void KOCQPluginBase::addIcon(const QVariant &v, QString data)
{
    QQuickItem *parent = qobject_cast<QQuickItem*>(v.value<QObject*>());

    if(m_quickItemIcon == NULL)
    {
        QQmlComponent *component = new QQmlComponent(getEngine());
        component->setData(data.toUtf8(), getUrlSource());
        m_quickItemIcon = qobject_cast<QQuickItem*>(component->create());
        m_quickItemIcon->setParentItem(parent);
    }
}
