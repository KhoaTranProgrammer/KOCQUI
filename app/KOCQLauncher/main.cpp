/*
 * MIT License
 * 
 * Copyright (c) 2020 KhoaTran Programmer
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
 * VERSION: 1.1.1 *
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

#endif

    return app.exec();
}
