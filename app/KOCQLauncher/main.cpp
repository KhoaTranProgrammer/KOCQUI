#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtQuick>
#include "KOCQPluginManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    QQuickView view;
    view.setSource(QUrl("qrc:///main.qml"));
    view.resize(720, 480);
    view.show();

    QString libLocation = LIBRARY_PATH;
    libLocation = libLocation.left(libLocation.size() - 16);
    libLocation += "lib/plugins/";

    KOCQPluginManager::getInstance()->setQmlEngine(view.engine());
    KOCQPluginManager::getInstance()->setRootObject(view.rootObject());
    KOCQPluginManager::getInstance()->setSource(view.source());
    KOCQPluginManager::getInstance()->setPluinPath(libLocation);
    KOCQPluginManager::getInstance()->loadAllPlugins();

    return app.exec();
}
