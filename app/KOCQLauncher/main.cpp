#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtQuick>

typedef void (*CreateWidgetFunction)(QQmlEngine* engine, QObject* parent, QUrl source);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    QQuickView view;
    view.setSource(QUrl("qrc:///main.qml"));
    view.resize(720, 480);
    view.show();

    return app.exec();
}
