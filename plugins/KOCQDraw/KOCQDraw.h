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
 * This class demonstrates OpenCV drawing and text output functions *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-18-2020                                               *
 *        Initial version supports 8 drawing types                  *
 *******************************************************************/

#ifndef KOCQDRAW_H
#define KOCQDRAW_H

#include "KOCQPluginBase.h"
#include "KOCQDraw_Global.h"

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

extern "C" KOCQDRAWSHARED_EXPORT void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQDRAWSHARED_EXPORT KOCQDraw : public KOCQPluginBase
{
    Q_OBJECT
public:
    static void createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    void onPluginLoad();

    QImage convertMat2QImage(Mat image);

public slots:
    void addIconSlot(const QVariant &v);
    void iConClicked();

    QImage drawingType001(int NUMBER);
    QImage drawingType002(int NUMBER);
    QImage drawingType003(int NUMBER);
    QImage drawingType004(int NUMBER);
    QImage drawingType005(int NUMBER);
    QImage drawingType006(int NUMBER);
    QImage drawingType007(int NUMBER);

private:
    KOCQDraw(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

};

#endif // KOCQDRAW_H
