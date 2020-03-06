#ifndef KOCQPICS_H
#define KOCQPICS_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QtQuick>
#include "KOCQPluginBase.h"
#include "KOCQPics_Global.h"

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

extern "C" KOCQPICSSHARED_EXPORT void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQPICSSHARED_EXPORT KOCQPics : public KOCQPluginBase
{
    Q_OBJECT
public:
    static void createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    void onPluginLoad();

public slots:
    void addIconSlot(const QVariant &v);
    void iConClicked();
    QImage convertMat2QImage(const QString &input);

    QImage basicLinearTransforms(const QString &input, double alpha, int beta);

private:
    KOCQPics(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    Mat readImage(const QString &input);
    QImage convertMat2QImage(Mat image);
};

#endif // KOCQPICS_H
