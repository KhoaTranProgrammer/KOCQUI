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
 * This class demonstrates OpenCV detect face&eye using camera input*
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-29-2020                                               *
 *        Initial version supports to detect face&eye using camera  *
 *        input in Windows                                          *
 *******************************************************************/

#ifndef KOCQFACEDETECTIONCAMFILTER_H
#define KOCQFACEDETECTIONCAMFILTER_H

#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>

#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

class KOCQFaceDetectionCamFilter : public QQuickPaintedItem
{
    Q_OBJECT
public:
    KOCQFaceDetectionCamFilter(QQuickItem *parent = 0);

    void paint(QPainter *painter);

public slots:
    void getVideoFrame();
    void clearImage();

private:
    bool isImage;   // Image is available or not
    QImage m_image; // QImage image content
    VideoCapture cap;

    void setImage(const QImage &image);
    QImage convertMat2QImage(Mat image);
    void faceDetect();
    void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                        CascadeClassifier& nestedCascade,
                        double scale, bool tryflip );

    CascadeClassifier cascade, nestedCascade;
    bool tryflip;
    double scale;
};

#endif // KOCQFACEDETECTIONCAMFILTER_H
