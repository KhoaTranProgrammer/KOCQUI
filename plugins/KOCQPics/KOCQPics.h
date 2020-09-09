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
 * VERSION: 1.0.2 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This class implements digital image processing algorithm by using*
 * OpenCV                                                           *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version supports some algorithms:                 *
 *        LinearTransforms, Negatives, GammaCorrection, Erosion,    *
 *        Dilation, Morphology, Drawing, Smoothing, Threshold,      *
 *        Transforms, Hough                                         *
 * 1.0.1: Aug-10-2020                                               *
 *        Support get default input image data/lena.jpg             *
 * 1.0.2: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot          *
 *******************************************************************/

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
#include <iostream>

using namespace cv;
using namespace std;

#define w 400

extern "C" KOCQPICSSHARED_EXPORT void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQPICSSHARED_EXPORT KOCQPics : public KOCQPluginBase
{
    Q_OBJECT
public:
    static void createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    void onPluginLoad();

    // Internal functions of Drawing
    void MyLine(Mat img, Point start, Point end);
    void MyPolygon(Mat img);
    void MyEllipse(Mat img, double angle);
    void MyFilledCircle(Mat img, Point center);

public slots:
    void addIconSlot(const QVariant &v, const QString &type);
    void iConClicked();
    QImage convertMat2QImage(const QString &input);
    QString defaultInput() const;

    QImage basicLinearTransforms(const QString &input, double alpha, int beta);

    // Intensity Transformations and Spatial Filtering
    QImage imageNegatives(const QString &input);
    QImage gammaCorrection(const QString &input, int gamma_cor);

    // Morphological Image Processing
    QImage erosion(const QString &input, int erosion_elem, int erosion_size);
    QImage dilation(const QString &input, int dilation_elem, int dilation_size);
    QImage morphologyOperations(const QString &input, int morph_elem, int morph_size, int morph_operator);

    // Drawings
    QImage simpleDrawing1();
    QImage simpleDrawing2();

    // Smoothing
    QImage homogeneousBlur(const QString &input, int kernel_length);
    QImage gaussianBlur(const QString &input, int kernel_length);
    QImage medianFilterBlur(const QString &input, int kernel_length);
    QImage bilateralFilterBlur(const QString &input, int kernel_length);

    // Threshold
    QImage threshold_Demo(const QString &input, int threshold_value, int threshold_type);

    // Image Transforms
    QImage copyMakeBorder_Demo(const QString &input, int borderType);
    QImage sobel_Demo(const QString &input, int ksize, int scale, int delta);
    QImage laplacian_Demo(const QString &input, int kernel_size, int scale, int delta);
    QImage canny_Demo(const QString &input, int threshold_value);
    QImage remapping(const QString &input, int types);

    // Hough Transforms
    QImage standardHoughLines(const QString &input, int s_trackbar, int min_threshold);
    QImage probabilisticHoughLines(const QString &input, int p_trackbar, int min_threshold);
    QImage houghCirclesDetection(const QString &input, int cannyThreshold, int accumulatorThreshold);

private:
    KOCQPics(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);
    Mat readImage(const QString &input);
    QImage convertMat2QImage(Mat image);
};

#endif // KOCQPICS_H
