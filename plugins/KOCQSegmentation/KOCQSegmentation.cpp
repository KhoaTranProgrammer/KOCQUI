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
 * This class demonstrates how to segment overlapping objects using *
 * Laplacian filtering, in addition to Watershed and Distance       *
 * Transformation                                                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-17-2020                                               *
 *        Initial version supports for Windows                      *
 *******************************************************************/

#include "KOCQSegmentation.h"

static KOCQSegmentation *myPluginInstance = NULL;
static QString pluginName = "KOCQ Segment";


void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQSegmentation::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQSegmentation::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQSegmentation(engine, rootObject, source, pluginManagerObject);
    }
}

KOCQSegmentation::KOCQSegmentation(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQSegmentation::addIconSlot(const QVariant &v)
{
    addIcon(v, "8bfe92de8d0582459ef196ce3938fc6b/images/icon.png");
}

void KOCQSegmentation::iConClicked()
{
    loadPlugin("qrc:/8bfe92de8d0582459ef196ce3938fc6b/qml/MainScreen.qml");
}

void KOCQSegmentation::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqSegObject", this);
}

QImage KOCQSegmentation::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

void KOCQSegmentation::imageSegmentation(const QString& in_file)
{
    qDebug() << Q_FUNC_INFO;
    QByteArray byteArr = in_file.toLocal8Bit();
    Mat src = imread(byteArr.data(), IMREAD_COLOR);

    // Set source image
    m_sourceImage = src;

    //! [black_bg]
    // Change the background from white to black, since that will help later to extract
    // better results during the use of Distance Transform
    for ( int i = 0; i < src.rows; i++ ) {
        for ( int j = 0; j < src.cols; j++ ) {
            if ( src.at<Vec3b>(i, j) == Vec3b(255,255,255) )
            {
                src.at<Vec3b>(i, j)[0] = 0;
                src.at<Vec3b>(i, j)[1] = 0;
                src.at<Vec3b>(i, j)[2] = 0;
            }
        }
    }

    // Set output image
    m_blackImage = src;

    //! [sharp]
    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3,3) <<
                  1,  1, 1,
                  1, -8, 1,
                  1,  1, 1); // an approximation of second derivative, a quite strong kernel

    // do the laplacian filtering as it is
    // well, we need to convert everything in something more deeper then CV_8U
    // because the kernel has some negative values,
    // and we can expect in general to have a Laplacian image with negative values
    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
    // so the possible negative number will be truncated
    Mat imgLaplacian;
    filter2D(src, imgLaplacian, CV_32F, kernel);
    Mat sharp;
    src.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;

    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    m_laplaceImage = imgLaplacian;
    m_sharpedImage = imgResult;

    //! [bin]
    // Create binary image from source image
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    m_binaryImage = bw;
    //! [bin]

    //! [dist]
    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
    m_distanceImage = dist;
    //! [dist]

    //! [peaks]
    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);

    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    m_peaksImage = dist;
    //! [peaks]

    //! [seeds]
    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);

    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i)+1), -1);
    }

    // Draw the background marker
    circle(markers, Point(5,5), 3, Scalar(255), -1);
    //! [seeds]

    //! [watershed]
    // Perform the watershed algorithm
    watershed(imgResult, markers);

    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);
    // image looks like at that point

    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);

        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
            {
                dst.at<Vec3b>(i,j) = colors[index-1];
            }
        }
    }

    m_resultImage = dst;
}

QImage KOCQSegmentation::getSourceImage()
{
    return convertMat2QImage(m_sourceImage);
}

QImage KOCQSegmentation::getBlackImage()
{
    return convertMat2QImage(m_blackImage);
}

QImage KOCQSegmentation::getLaplaceImage()
{
    return convertMat2QImage(m_laplaceImage);
}

QImage KOCQSegmentation::getSharpedImage()
{
    return convertMat2QImage(m_sharpedImage);
}

QImage KOCQSegmentation::getBinaryImage()
{
    return convertMat2QImage(m_binaryImage);
}

QImage KOCQSegmentation::getDistanceImage()
{
    return convertMat2QImage(m_distanceImage);
}

QImage KOCQSegmentation::getPeaksImage()
{
    return convertMat2QImage(m_peaksImage);
}

QImage KOCQSegmentation::getResultImage()
{
    return convertMat2QImage(m_resultImage);
}

QString KOCQSegmentation::defaultInput() const
{
    QDir dir;
    QString defaultImage = dir.absolutePath() + "/data/cards.png";
    return defaultImage;
}
