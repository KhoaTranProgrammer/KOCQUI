#ifndef KOCQPLUGINBASE_H
#define KOCQPLUGINBASE_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QtQuick>
#include "kocqcore_global.h"

class KOCQCORESHARED_EXPORT KOCQPluginBase : public QObject
{
    Q_OBJECT
public:
    KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source);

public:
    QQmlEngine* getEngine() const;
    QUrl getUrlSource() const;
    void addIcon(const QVariant &v, QString data);

public slots:
    virtual void addIconSlot(const QVariant &v) = 0;

private:
    QQmlEngine* m_engine;
    QUrl m_source;
    QQuickItem *m_quickItemIcon;
};

#endif // KOCQPLUGINBASE_H
