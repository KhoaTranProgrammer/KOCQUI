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
 *        Add option to get icon view type for addIconSlot.         *
 *        setupIconConnection in case of plugin is created.         *
 *        Add plugin detail description.                            *
 *******************************************************************/

#include "KOCQAffine.h"

static KOCQAffine *myPluginInstance = NULL;
static QString pluginName = "KOCQ Affine";
static QString pluginDetail = "This plugin demonstrates OpenCV Affine Transform";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQAffine::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQAffine::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQAffine(engine, rootObject, source, pluginManagerObject);
    }
    else
    {
        myPluginInstance->setupIconConnection();
    }
}

KOCQAffine::KOCQAffine(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQAffine::addIconSlot(const QVariant &v, const QString &type)
{
    addIcon(v, "aa17a8646814c323f69cbf4cb54f3065/images/icon.png", type, pluginDetail);
}

void KOCQAffine::iConClicked()
{
    loadPlugin("qrc:/aa17a8646814c323f69cbf4cb54f3065/qml/MainScreen.qml");
}

void KOCQAffine::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqAffineObject", this);
}

QImage KOCQAffine::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

QString KOCQAffine::defaultInput() const
{
    QDir dir;
    QString defaultImage = dir.absolutePath() + "/data/lena.jpg";
    return defaultImage;
}

void KOCQAffine::affineTransforms(const QString& in_file, double point1, double point2, double point3)
{
    //! [Load the image]
    QByteArray byteArr = in_file.toLocal8Bit();
    Mat src = imread(byteArr.data());
    //! [Load the image]

    //! [Set your 3 points to calculate the  Affine Transform]
    Point2f srcTri[3];
    srcTri[0] = Point2f( 0.f, 0.f );
    srcTri[1] = Point2f( src.cols - 1.f, 0.f );
    srcTri[2] = Point2f( 0.f, src.rows - 1.f );

    Point2f dstTri[3];
    dstTri[0] = Point2f( 0.f, src.rows * point1 );
    dstTri[1] = Point2f( src.cols * point2, src.rows * (1.10f - point2) );
    dstTri[2] = Point2f( src.cols * point3, src.rows * (0.85f - point3) );
    //! [Set your 3 points to calculate the  Affine Transform]

    //! [Get the Affine Transform]
    Mat warp_mat = getAffineTransform( srcTri, dstTri );
    //! [Get the Affine Transform]

    //! [Apply the Affine Transform just found to the src image]
    /// Set the dst image the same type and size as src
    m_warpDst = Mat::zeros( src.rows, src.cols, src.type() );

    warpAffine( src, m_warpDst, warp_mat, m_warpDst.size() );
    //! [Apply the Affine Transform just found to the src image]

    /** Rotating the image after Warp */

    //! [Compute a rotation matrix with respect to the center of the image]
    Point center = Point( m_warpDst.cols/2, m_warpDst.rows/2 );
    double angle = -50.0;
    double scale = 0.6;
    //! [Compute a rotation matrix with respect to the center of the image]

    //! [Get the rotation matrix with the specifications above]
    Mat rot_mat = getRotationMatrix2D( center, angle, scale );
    //! [Get the rotation matrix with the specifications above]

    //! [Rotate the warped image]
    warpAffine( m_warpDst, m_warpRotateDst, rot_mat, m_warpDst.size() );
    //! [Rotate the warped image]
}

QImage KOCQAffine::getWarpDst()
{
    return convertMat2QImage(m_warpDst);
}

QImage KOCQAffine::getWarpRotateDst()
{
    return convertMat2QImage(m_warpRotateDst);
}
