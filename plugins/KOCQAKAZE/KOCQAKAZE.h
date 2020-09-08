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
 * This class demonstrates how to use AKAZE [5] local features to   *
 * detect and match keypoints on two images                         *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-22-2020                                               *
 *        Initial version supports for Windows                      *
 * 1.0.1: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot          *
 *******************************************************************/

#ifndef KOCQAKAZE_H
#define KOCQAKAZE_H

#include "KOCQAKAZE_Global.h"
#include "KOCQPluginBase.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include <opencv2/calib3d.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

extern "C" KOCQAKAZESHARED_EXPORT void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQAKAZESHARED_EXPORT KOCQAKAZE : public KOCQPluginBase
{
    Q_OBJECT
public:
    static void createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    void onPluginLoad();
    QImage convertMat2QImage(Mat image);

public slots:
    void addIconSlot(const QVariant &v, const QString &type);
    void iConClicked();
    QString defaultInputImage_1() const;
    QString defaultInputImage_2() const;
    QString defaultHomography() const;
    QImage AKAZE_match(QString str_img1, QString str_img2, QString str_homography);
    QString getMatchingResults();

private:
    KOCQAKAZE(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    QString m_matchingResults;
};

#endif // KOCQAKAZE_H
