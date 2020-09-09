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
 * This class demonstrates OpenCV drawing and text output functions *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-18-2020                                               *
 *        Initial version supports 8 drawing types                  *
 * 1.0.1: May-26-2020                                               *
 *        Copy resource into hash folder                            *
 * 1.0.2: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot.         *
 *        setupIconConnection in case of plugin is created.         *
 *        Add plugin detail description.                            *
 *******************************************************************/

#include "KOCQDraw.h"

static KOCQDraw *myPluginInstance = NULL;
static QString pluginName = "KOCQ Draw";
static QString pluginDetail = "This plugin demonstrates OpenCV drawing and text output functions";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQDraw::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQDraw::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQDraw(engine, rootObject, source, pluginManagerObject);
    }
    else
    {
        myPluginInstance->setupIconConnection();
    }
}

KOCQDraw::KOCQDraw(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQDraw::addIconSlot(const QVariant &v, const QString &type)
{
    addIcon(v, "2bee89770f1ba487fc737a11ac02d0d4/images/icon.png", type, pluginDetail);
}

void KOCQDraw::iConClicked()
{
    loadPlugin("qrc:/2bee89770f1ba487fc737a11ac02d0d4/qml/MainScreen.qml");
}

void KOCQDraw::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqDrawObject", this);
}

QImage KOCQDraw::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

static Scalar randomColor(RNG& rng)
{
    int icolor = (unsigned)rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

QImage KOCQDraw::drawingType001(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 0; i < NUMBER * 2; i++)
    {
        Point pt1, pt2;
        pt1.x = rng.uniform(x1, x2);
        pt1.y = rng.uniform(y1, y2);
        pt2.x = rng.uniform(x1, x2);
        pt2.y = rng.uniform(y1, y2);

        int arrowed = rng.uniform(0, 6);

        if( arrowed < 3 )
            line( image, pt1, pt2, randomColor(rng), rng.uniform(1,10), lineType );
        else
            arrowedLine(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), lineType);
    }

    return convertMat2QImage(image);
}

QImage KOCQDraw::drawingType002(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 0; i < NUMBER * 2; i++)
    {
        Point pt1, pt2;
        pt1.x = rng.uniform(x1, x2);
        pt1.y = rng.uniform(y1, y2);
        pt2.x = rng.uniform(x1, x2);
        pt2.y = rng.uniform(y1, y2);
        int thickness = rng.uniform(-3, 10);
        int marker = rng.uniform(0, 10);
        int marker_size = rng.uniform(30, 80);

        if (marker > 5)
            rectangle(image, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType);
        else
            drawMarker(image, pt1, randomColor(rng), marker, marker_size );
    }

    return convertMat2QImage(image);
}

QImage KOCQDraw::drawingType003(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 0; i < NUMBER; i++)
    {
        Point center;
        center.x = rng.uniform(x1, x2);
        center.y = rng.uniform(y1, y2);
        Size axes;
        axes.width = rng.uniform(0, 200);
        axes.height = rng.uniform(0, 200);
        double angle = rng.uniform(0, 180);

        ellipse( image, center, axes, angle, angle - 100, angle + 200,
                 randomColor(rng), rng.uniform(-1,9), lineType );
    }

    return convertMat2QImage(image);
}

QImage KOCQDraw::drawingType004(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 0; i< NUMBER; i++)
    {
        Point pt[2][3];
        pt[0][0].x = rng.uniform(x1, x2);
        pt[0][0].y = rng.uniform(y1, y2);
        pt[0][1].x = rng.uniform(x1, x2);
        pt[0][1].y = rng.uniform(y1, y2);
        pt[0][2].x = rng.uniform(x1, x2);
        pt[0][2].y = rng.uniform(y1, y2);
        pt[1][0].x = rng.uniform(x1, x2);
        pt[1][0].y = rng.uniform(y1, y2);
        pt[1][1].x = rng.uniform(x1, x2);
        pt[1][1].y = rng.uniform(y1, y2);
        pt[1][2].x = rng.uniform(x1, x2);
        pt[1][2].y = rng.uniform(y1, y2);
        const Point* ppt[2] = {pt[0], pt[1]};
        int npt[] = {3, 3};

        polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1,10), lineType);
    }

    return convertMat2QImage(image);
}

QImage KOCQDraw::drawingType005(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 0; i< NUMBER; i++)
    {
        Point pt[2][3];
        pt[0][0].x = rng.uniform(x1, x2);
        pt[0][0].y = rng.uniform(y1, y2);
        pt[0][1].x = rng.uniform(x1, x2);
        pt[0][1].y = rng.uniform(y1, y2);
        pt[0][2].x = rng.uniform(x1, x2);
        pt[0][2].y = rng.uniform(y1, y2);
        pt[1][0].x = rng.uniform(x1, x2);
        pt[1][0].y = rng.uniform(y1, y2);
        pt[1][1].x = rng.uniform(x1, x2);
        pt[1][1].y = rng.uniform(y1, y2);
        pt[1][2].x = rng.uniform(x1, x2);
        pt[1][2].y = rng.uniform(y1, y2);
        const Point* ppt[2] = {pt[0], pt[1]};
        int npt[] = {3, 3};

        fillPoly(image, ppt, npt, 2, randomColor(rng), lineType);
    }

    return convertMat2QImage(image);
}

QImage KOCQDraw::drawingType006(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 0; i < NUMBER; i++)
    {
        Point center;
        center.x = rng.uniform(x1, x2);
        center.y = rng.uniform(y1, y2);

        circle(image, center, rng.uniform(0, 300), randomColor(rng),
               rng.uniform(-1, 9), lineType);
    }

    return convertMat2QImage(image);
}

QImage KOCQDraw::drawingType007(int NUMBER)
{
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(height, width, CV_8UC3);

    for (i = 1; i < NUMBER; i++)
    {
        Point org;
        org.x = rng.uniform(x1, x2);
        org.y = rng.uniform(y1, y2);

        putText(image, "Testing text rendering", org, rng.uniform(0,8),
                rng.uniform(0,100)*0.05+0.1, randomColor(rng), rng.uniform(1, 10), lineType);
    }

    return convertMat2QImage(image);
}
