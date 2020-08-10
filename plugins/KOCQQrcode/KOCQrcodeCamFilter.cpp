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

#include "KOCQrcodeCamFilter.h"

KOCQrcodeCamFilter::KOCQrcodeCamFilter(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    isImage = false;
    cap = VideoCapture(0);
}

void KOCQrcodeCamFilter::paint(QPainter *painter)
{
    if(isImage == true)
    {
        float scale = (this->width() / m_image.width()) < (this->height() / m_image.height()) ?
                    (this->width() / m_image.width()) : (this->height() / m_image.height());
        float startX, startY;
        startX = this->width() / 2 - (m_image.width() * scale) / 2;
        startY = this->height() / 2 - (m_image.height() * scale) / 2;
        QRectF r1(startX, startY, m_image.width() * scale, m_image.height() * scale);
        painter->drawImage(r1, m_image);
    }
    else
    {
        QRectF r1(0, 0, this->width(), this->height());
        painter->fillRect(r1, QColor("transparent"));
    }
}

QString KOCQrcodeCamFilter::qrResult() const
{
    return m_qrResult;
}

void KOCQrcodeCamFilter::getVideoFrame()
{
    liveQRCodeDetect();
}

void KOCQrcodeCamFilter::liveQRCodeDetect()
{
    Mat frame;
    QRCodeDetector qrcode;
    TickMeter total;
    {
        Mat frame, src, straight_barcode;
        string decode_info;
        vector<Point> transform;
        cap >> frame;
        cvtColor(frame, src, COLOR_BGR2GRAY);

        total.start();
        bool result_detection = qrcode.detect(src, transform);
        if (result_detection)
        {
            decode_info = qrcode.decode(src, transform, straight_barcode);
            if (!decode_info.empty())
            {
                m_qrResult = QString::fromStdString(decode_info);
                emit qrResultChanged();
            } else {
                m_qrResult = "";
                emit qrResultChanged();
            }
        } else {
            m_qrResult = "";
            emit qrResultChanged();
        }

        total.stop();
        double fps = 1 / total.getTimeSec();
        total.reset();

        if (result_detection) { drawQRCodeContour(frame, transform); }
        drawFPS(frame, fps);

        setImage(convertMat2QImage(frame));
    }
}

void KOCQrcodeCamFilter::setImage(const QImage &image)
{
    this->isImage = true;
    this->m_image = image;
    update();
}

QImage KOCQrcodeCamFilter::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

void KOCQrcodeCamFilter::drawQRCodeContour(Mat &color_image, vector<Point> transform)
{
    if (!transform.empty())
    {
        double show_radius = (color_image.rows  > color_image.cols)
                   ? (2.813 * color_image.rows) / color_image.cols
                   : (2.813 * color_image.cols) / color_image.rows;
        double contour_radius = show_radius * 0.4;

        vector< vector<Point> > contours;
        contours.push_back(transform);
        drawContours(color_image, contours, 0, Scalar(211, 0, 148), cvRound(contour_radius));

        RNG rng(1000);
        for (size_t i = 0; i < 4; i++)
        {
            Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
            circle(color_image, transform[i], cvRound(show_radius), color, -1);
        }
    }
}

void KOCQrcodeCamFilter::drawFPS(Mat &color_image, double fps)
{
    ostringstream convert;
    convert << cvRound(fps) << " FPS (QR detection)";
    putText(color_image, convert.str(), Point(25, 25), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);
}

void KOCQrcodeCamFilter::clearImage()
{
    this->isImage = false;
    update();
}
