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
protected:
    KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source, QString name);

public:
    QObject* getRootObject() const;
    QQmlEngine* getEngine() const;
    QUrl getUrlSource() const;
    QString getPluginName() const;

    void addIcon(const QVariant &v);
    void loadPlugin(const QUrl qmlFile);

public slots:
    virtual void addIconSlot(const QVariant &v) = 0;
    virtual void iConClicked() = 0;

private:
    KOCQPluginBase(); // private default constructor
    KOCQPluginBase(const KOCQPluginBase&); // prevent copying
    KOCQPluginBase& operator=(const KOCQPluginBase&);

    QQmlComponent* m_component;
    QQmlEngine* m_engine;
    QUrl m_source;
    QQuickItem *m_quickItemIcon;
    QString m_pluginName;
    QObject* m_parent;
    QObject* m_loader;
};

#endif // KOCQPLUGINBASE_H
