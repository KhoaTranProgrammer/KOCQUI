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
 * This class demonstrates OpenCV drawing and text output functions *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-25-2020                                               *
 *        Initial version calculate Histogram using calcHist        *
 * 1.0.1: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot.         *
 *        setupIconConnection in case of plugin is created.         *
 *        Add plugin detail description.                            *
 *******************************************************************/

#include "KOCQHISTOGRAM.h"

static KOCQHISTOGRAM *myPluginInstance = NULL;
static QString pluginName = "KOCQ Histogram";
static QString pluginDetail = "This plugin demonstrates OpenCV Histogram Calculation";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQHISTOGRAM::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQHISTOGRAM::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQHISTOGRAM(engine, rootObject, source, pluginManagerObject);
    }
    else
    {
        myPluginInstance->setupIconConnection();
    }
}

KOCQHISTOGRAM::KOCQHISTOGRAM(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQHISTOGRAM::addIconSlot(const QVariant &v, const QString &type)
{
    addIcon(v, "51d10313b94bf790c0a46129c3d0d6bf/images/icon.png", type, pluginDetail);
}

void KOCQHISTOGRAM::iConClicked()
{
    loadPlugin("qrc:/51d10313b94bf790c0a46129c3d0d6bf/qml/MainScreen.qml");
}

void KOCQHISTOGRAM::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqHistObject", this);
}

QImage KOCQHISTOGRAM::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

QImage KOCQHISTOGRAM::openImage(const QString& in_file)
{
    QByteArray byteArr = in_file.toLocal8Bit();
    m_srcImage = imread(byteArr.data(), IMREAD_COLOR);
    return convertMat2QImage(m_srcImage);
}

QImage KOCQHISTOGRAM::calcHist()
{
    //! [Separate the image in 3 places ( B, G and R )]
    vector<Mat> bgr_planes;
    split( m_srcImage, bgr_planes );
    //! [Separate the image in 3 places ( B, G and R )]

    //! [Establish the number of bins]
    int histSize = 256;
    //! [Establish the number of bins]

    //! [Set the ranges ( for B,G,R) )]
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    //! [Set the ranges ( for B,G,R) )]

    //! [Set histogram param]
    bool uniform = true, accumulate = false;
    //! [Set histogram param]

    //! [Compute the histograms]
    Mat b_hist, g_hist, r_hist;
    cv::calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
    //! [Compute the histograms]

    //! [Draw the histograms for B, G and R]
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    //! [Draw the histograms for B, G and R]

    //! [Normalize the result to ( 0, histImage.rows )]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    //! [Normalize the result to ( 0, histImage.rows )]

    //! [Draw for each channel]
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }
    //! [Draw for each channel]

    return convertMat2QImage(histImage);
}

QString KOCQHISTOGRAM::defaultInput() const
{
    QDir dir;
    QString defaultImage = dir.absolutePath() + "/data/baboon.jpg";
    return defaultImage;
}
