#include "KOCQPluginBase.h"

KOCQPluginBase::KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source)
{
    m_engine = engine;
    m_source = source;
    QObject::connect(parent, SIGNAL(qmlSignal(QVariant)),
                       this, SLOT(cppSlot(QVariant)));
}
