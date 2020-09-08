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
 * VERSION: 1.0.1 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This class demonstrates OpenCV Affine Transform                  *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-26-2020                                               *
 *        Initial version demo Affine Transform                     *
 * 1.0.1: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot          *
 *******************************************************************/

#ifndef KOCQAFFINE_H
#define KOCQAFFINE_H

#include "KOCQAffine_Global.h"
#include "KOCQPluginBase.h"

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

extern "C" KOCQAFFINESHARED_EXPORT void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQAFFINESHARED_EXPORT KOCQAffine : public KOCQPluginBase
{
    Q_OBJECT
public:
    static void createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    void onPluginLoad();

    QImage convertMat2QImage(Mat image);

public slots:
    void addIconSlot(const QVariant &v, const QString &type);
    void iConClicked();
    QString defaultInput() const;
    void affineTransforms(const QString& in_file, double point1, double point2, double point3);
    QImage getWarpDst();
    QImage getWarpRotateDst();

private:
    KOCQAffine(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    Mat m_warpDst;
    Mat m_warpRotateDst;
};

#endif // KOCQAFFINE_H
