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
 * VERSION: 1.0.0 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This class implements OpenCV QRCodeDetect                        *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-29-2020                                               *
 *        Initial version supports to detect Face and eyes from     *
 *        camera                                                    *
 *******************************************************************/

#include "KOCQFaceDetection.h"
#include "KOCQFaceDetectionCamFilter.h"

static KOCQFaceDetection *myPluginInstance = NULL;
static QString pluginName = "KOCQ FaceDetection";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQFaceDetection::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQFaceDetection::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQFaceDetection(engine, rootObject, source, pluginManagerObject);
    }
}

KOCQFaceDetection::KOCQFaceDetection(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQFaceDetection::addIconSlot(const QVariant &v)
{
    // KOCQrcodeCamFilter
    qmlRegisterType<KOCQFaceDetectionCamFilter>("KOCQFaceDetectionCamFilter", 1, 0, "KOCQFaceDetectionCamFilter");

    addIcon(v, "524b8a9c91a48c16544e57b8e826a84d/images/icon.png");
}

void KOCQFaceDetection::iConClicked()
{
    loadPlugin("qrc:/524b8a9c91a48c16544e57b8e826a84d/qml/MainScreen.qml");
}

void KOCQFaceDetection::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqFaceDetObject", this);
}
