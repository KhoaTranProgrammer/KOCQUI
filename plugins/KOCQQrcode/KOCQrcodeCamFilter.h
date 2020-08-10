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
 * This class demonstrates OpenCV QRCodeDetect using camera input   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-08-2020                                               *
 *        Initial version supports to detect QRCode using camera    *
 *        input in Windows                                          *
 *******************************************************************/

#ifndef KOCQRCODECAMFILTER_H
#define KOCQRCODECAMFILTER_H

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

class KOCQrcodeCamFilter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString qrResult READ qrResult NOTIFY qrResultChanged)
public:
    KOCQrcodeCamFilter(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    QString qrResult() const;

public slots:
    void getVideoFrame();
    void clearImage();

signals:
    void qrResultChanged();

private:
    bool isImage;   // Image is available or not
    QImage m_image; // QImage image content
    VideoCapture cap;
    QString m_qrResult;

    void liveQRCodeDetect();
    void setImage(const QImage &image);
    QImage convertMat2QImage(Mat image);
    void drawQRCodeContour(Mat &color_image, vector<Point> transform);
    void drawFPS(Mat &color_image, double fps);
};

#endif // KOCQRCODECAMFILTER_H
