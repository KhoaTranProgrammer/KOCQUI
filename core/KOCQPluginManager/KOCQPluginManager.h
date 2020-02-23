#ifndef KOCQPLUGINMANAGER_H
#define KOCQPLUGINMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QtQuick>
#include "KOCQPluginManager_Global.h"

typedef void (*CreateWidgetFunction)(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQPLUGINMANAGERSHARED_EXPORT KOCQPluginManager : public QObject
{
    Q_OBJECT
public:
    static KOCQPluginManager* getInstance();
    void setQmlEngine(QQmlEngine* engine);
    void setRootObject(QObject* rootObject);
    void setSource(QUrl source);
    void setPluinPath(QString pluinPath);
    void loadAllPlugins();

public slots:
    void addIconSlot(const QVariant &v);

signals:
    void addIconSignal(QVariant);

private:
    KOCQPluginManager();

    QVector<CreateWidgetFunction> m_pluginQLibrary;

    QQmlEngine* m_engine;
    QObject* m_rootObject;
    QUrl m_source;
    QString m_pluinPath;
};

#endif // KOCQPLUGINMANAGER_H
