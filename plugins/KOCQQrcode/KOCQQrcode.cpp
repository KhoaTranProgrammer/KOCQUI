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
 * 1.0.0: June-07-2020                                              *
 *        Initial version supports to detect QRCode in image        *
 *******************************************************************/

#include "KOCQQrcode.h"

static KOCQQrcode *myPluginInstance = NULL;
static QString pluginName = "KOCQ Qrcode";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQQrcode::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQQrcode::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQQrcode(engine, rootObject, source, pluginManagerObject);
    }
}

KOCQQrcode::KOCQQrcode(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQQrcode::addIconSlot(const QVariant &v)
{
    addIcon(v, "a5d64ea9f353bd0813935b93e20a39a4/images/qr_code.png");
}

void KOCQQrcode::iConClicked()
{
    loadPlugin("qrc:/a5d64ea9f353bd0813935b93e20a39a4/qml/MainScreen.qml");
}

void KOCQQrcode::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqQrcodeObject", this);
}

QImage KOCQQrcode::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

void KOCQQrcode::drawQRCodeContour(Mat &color_image, vector<Point> transform)
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

void KOCQQrcode::drawFPS(Mat &color_image, double fps)
{
    ostringstream convert;
    convert << cvRound(fps) << " FPS (QR detection)";
    putText(color_image, convert.str(), Point(25, 25), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);
}

QImage KOCQQrcode::openImage(const QString& in_file)
{
    QByteArray byteArr = in_file.toLocal8Bit();
    Mat color_src = imread(byteArr.data(), IMREAD_COLOR);
    return convertMat2QImage(color_src);
}

QImage KOCQQrcode::imageQRCodeDetect(const QString& in_file)
{
    QByteArray byteArr = in_file.toLocal8Bit();
    Mat color_src = imread(byteArr.data(), IMREAD_COLOR);
    Mat src;
    cvtColor(color_src, src, COLOR_BGR2GRAY);
    Mat straight_barcode;
    string decoded_info;
    vector<Point> transform;
    const int count_experiments = 10;
    double transform_time = 0.0;
    bool result_detection = false;
    TickMeter total;
    QRCodeDetector qrcode;
    for (size_t i = 0; i < count_experiments; i++)
    {
        total.start();
        transform.clear();
        result_detection = qrcode.detect(src, transform);
        total.stop();
        transform_time += total.getTimeSec();
        total.reset();
        if (!result_detection)
            continue;

        total.start();
        decoded_info = qrcode.decode(src, transform, straight_barcode);
        total.stop();
        transform_time += total.getTimeSec();
        total.reset();
    }
    double fps = count_experiments / transform_time;
    if (!result_detection)
        cout << "QR code not found" << endl;
    if (decoded_info.empty())
        cout << "QR code cannot be decoded" << endl;

    drawQRCodeContour(color_src, transform);
    drawFPS(color_src, fps);

//    cout << "Input  image file path: " << in_file  << endl;
    cout << "Size: " << color_src.size() << endl;
    cout << "FPS: " << fps << endl;
    cout << "Decoded info: " << decoded_info << endl;

    return convertMat2QImage(color_src);
}
