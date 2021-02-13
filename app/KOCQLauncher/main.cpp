/*
 * MIT License
 * 
 * Copyright (c) 2020-2021 KhoaTran Programmer
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/******************
 * VERSION: 1.1.9 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file is the main function of KOCQLauncher. It manipulates   *
 * all of Plugins                                                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version uses KOCQPluginManager to load all of     *
 *        Plugins                                                   *
 * 1.1.0: May-25-2020                                               *
 *        Support to load Plugins for Android: KOCQDraw, KOCQPics   *
 *        June-04-2020                                              *
 *        Fix library location for Windows                          *
 *        June-13-2020                                              *
 *        Support to load Plugins for Android: KOCQQrcode           *
 * 1.1.1: Aug-10-2020                                               *
 *        Support to load Plugins for Windows by setting correct    *
 *        plugin name                                               *
 * 1.1.2: Aug-17-2020                                               *
 *        Support to load Plugins KOCQSegmentation for Windows      *
 * 1.1.3: Aug-22-2020                                               *
 *        Support to load Plugins KOCQAKAZE for Windows             *
 * 1.1.4: Aug-25-2020                                               *
 *        Support to load Plugins KOCQHISTOGRAM for Windows         *
 * 1.1.5: Aug-26-2020                                               *
 *        Support to load Plugins KOCQAffine for Windows            *
 * 1.1.6: Aug-29-2020                                               *
 *        Support to load Plugins KOCQFaceDetection for Windows     *
 * 1.1.7: Jan-24-2021                                               *
 *        Support to load Plugins KOCQSegmentation for Android      *
 * 1.1.8: Feb-09-2021                                               *
 *        Support to load Plugins KOCQAKAZE for Android             *
 * 1.1.9: Feb-10-2021                                               *
 *        Support to load Plugins KOCQHISTOGRAM for Android         *
 * 1.1.10: Feb-12-2021                                              *
 *        Support to load Plugins KOCQAffine for Android            *
 * 1.1.11: Feb-13-2021                                              *
 *        Support to load Plugins KOCQFaceDetection for Android     *
 *******************************************************************/

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtQuick>
#include "KOCQPluginManager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    QQuickView view;
    view.setSource(QUrl("qrc:///main.qml"));
    QObject::connect((QObject*)view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view.showFullScreen();

    KOCQPluginManager::getInstance()->setQmlEngine(view.engine());
    KOCQPluginManager::getInstance()->setRootObject(view.rootObject());
    KOCQPluginManager::getInstance()->setSource(view.source());

#if defined(Q_OS_ANDROID)
    QDir dir;
    dir.cdUp();
    QString libLocation = dir.absolutePath() + "/lib";

    // Load KOCQDraw
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQDraw.so");

    // Load KOCQPics
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQPics.so");

    // Load KOCQQrcode
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQQrcode.so");

    // Load KOCQSegmentation
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQSegmentation.so");

    // Load KOCQAKAZE
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQAKAZE.so");

    // Load KOCQHISTOGRAM
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQHISTOGRAM.so");

    // Load KOCQAffine
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQAffine.so");

    // Load KOCQFaceDetection
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "/libKOCQFaceDetection.so");
#else
    QDir dir;
    dir.cdUp();
    QString libLocation = dir.absolutePath() + "/lib/plugins/";

    // Load KOCQDraw
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQDraw.dll");

    // Load KOCQPics
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQPics.dll");

    // Load KOCQQrcode
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQQrcode.dll");

    // Load KOCQSegmentation
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQSegmentation.dll");

    // Load KOCQSegmentation
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQAKAZE.dll");

    // Load KOCQHISTOGRAM
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQHISTOGRAM.dll");

    // Load KOCQAffine
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQAffine.dll");

    // Load KOCQFaceDetection
    KOCQPluginManager::getInstance()->loadPlugin(libLocation + "KOCQFaceDetection.dll");
#endif

    return app.exec();
}
