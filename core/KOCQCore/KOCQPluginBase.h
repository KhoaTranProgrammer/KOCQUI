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
    Q_ENUMS(KOCQPLUGINSTATE)
protected:
    KOCQPluginBase(QQmlEngine* engine, QObject* parent, QUrl source, QString name, QString defaultPath);

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

    void addIcon(const QVariant &v, const QString icon);
    void loadPlugin(const QString qmlFile);

public slots:
    virtual void addIconSlot(const QVariant &v) = 0;
    virtual void iConClicked() = 0;
    void unloadPluginSlot();

private:
    KOCQPluginBase(); // private default constructor
    KOCQPluginBase(const KOCQPluginBase&); // prevent copying
    KOCQPluginBase& operator=(const KOCQPluginBase&);

    KOCQPLUGINSTATE m_pluginstate = KOCQ_UNINIT;
    QQmlComponent* m_component;
    QQmlEngine* m_engine;
    QUrl m_source;
    QQuickItem *m_quickItemIcon;
    QString m_pluginName;
    QObject* m_parent;
    QObject* m_loader;
    QString m_defaultPath = NULL;
};

#endif // KOCQPLUGINBASE_H
