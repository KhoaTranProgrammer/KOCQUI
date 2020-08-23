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
 * This class demonstrates how to use AKAZE [5] local features to   *
 * detect and match keypoints on two images                         *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-22-2020                                               *
 *        Initial version supports for Windows                      *
 *******************************************************************/

#include "KOCQAKAZE.h"

const float inlier_threshold = 2.5f; // Distance threshold to identify inliers with homography check
const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio

static KOCQAKAZE *myPluginInstance = NULL;
static QString pluginName = "KOCQ AKAZE";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQAKAZE::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQAKAZE::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQAKAZE(engine, rootObject, source, pluginManagerObject);
    }
}

KOCQAKAZE::KOCQAKAZE(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{
    m_matchingResults = "";
}

void KOCQAKAZE::addIconSlot(const QVariant &v)
{
    addIcon(v, "0eae55bd85a730b806f6d05778f434dc/images/icon.png");
}

void KOCQAKAZE::iConClicked()
{
    loadPlugin("qrc:/0eae55bd85a730b806f6d05778f434dc/qml/MainScreen.qml");
}

void KOCQAKAZE::onPluginLoad()
{
    getPluginContext()->setContextProperty("kocqAkazeObject", this);
}

QString KOCQAKAZE::defaultInputImage_1() const
{
    QDir dir;
    QString defaultData = dir.absolutePath() + "/data/graf1.png";
    return defaultData;
}

QString KOCQAKAZE::defaultInputImage_2() const
{
    QDir dir;
    QString defaultData = dir.absolutePath() + "/data/graf3.png";
    return defaultData;
}

QString KOCQAKAZE::defaultHomography() const
{
    QDir dir;
    QString defaultData = dir.absolutePath() + "/data/H1to3p.xml";
    return defaultData;
}

QImage KOCQAKAZE::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

QImage KOCQAKAZE::AKAZE_match(QString str_img1, QString str_img2, QString str_homography)
{
    //! [load]
    QByteArray byteArr1 = str_img1.toLocal8Bit();
    Mat img1 = imread(byteArr1.data(), IMREAD_COLOR);

    QByteArray byteArr2 = str_img2.toLocal8Bit();
    Mat img2 = imread(byteArr2.data(), IMREAD_COLOR);

    QByteArray byteArr_homography = str_homography.toLocal8Bit();
    Mat homography;
    FileStorage fs(byteArr_homography.data(), FileStorage::READ);
    fs.getFirstTopLevelNode() >> homography;
    //! [load]

    //! [AKAZE]
    vector<KeyPoint> kpts1, kpts2;
    Mat desc1, desc2;

    Ptr<AKAZE> akaze = AKAZE::create();
    akaze->detectAndCompute(img1, noArray(), kpts1, desc1);
    akaze->detectAndCompute(img2, noArray(), kpts2, desc2);
    //! [AKAZE]

    //! [2-nn matching]
    BFMatcher matcher(NORM_HAMMING);
    vector< vector<DMatch> > nn_matches;
    matcher.knnMatch(desc1, desc2, nn_matches, 2);
    //! [2-nn matching]

    //! [ratio test filtering]
    vector<KeyPoint> matched1, matched2;
    for(size_t i = 0; i < nn_matches.size(); i++) {
        DMatch first = nn_matches[i][0];
        float dist1 = nn_matches[i][0].distance;
        float dist2 = nn_matches[i][1].distance;

        if(dist1 < nn_match_ratio * dist2) {
            matched1.push_back(kpts1[first.queryIdx]);
            matched2.push_back(kpts2[first.trainIdx]);
        }
    }
    //! [ratio test filtering]

    //! [homography check]
    vector<DMatch> good_matches;
    vector<KeyPoint> inliers1, inliers2;
    for(size_t i = 0; i < matched1.size(); i++) {
        Mat col = Mat::ones(3, 1, CV_64F);
        col.at<double>(0) = matched1[i].pt.x;
        col.at<double>(1) = matched1[i].pt.y;

        col = homography * col;
        col /= col.at<double>(2);
        double dist = sqrt( pow(col.at<double>(0) - matched2[i].pt.x, 2) +
                            pow(col.at<double>(1) - matched2[i].pt.y, 2));

        if(dist < inlier_threshold) {
            int new_i = static_cast<int>(inliers1.size());
            inliers1.push_back(matched1[i]);
            inliers2.push_back(matched2[i]);
            good_matches.push_back(DMatch(new_i, new_i, 0));
        }
    }
    //! [homography check]

    //! [draw final matches]
    Mat res;
    drawMatches(img1, inliers1, img2, inliers2, good_matches, res);

    double inlier_ratio = inliers1.size() / (double) matched1.size();
    m_matchingResults = "A-KAZE Matching Results\n";
    m_matchingResults += "*******************************\n";
    m_matchingResults += "# Keypoints 1: "; m_matchingResults += QString::number(kpts1.size()); m_matchingResults += "\n";
    m_matchingResults += "# Keypoints 2: "; m_matchingResults += QString::number(kpts2.size()); m_matchingResults += "\n";
    m_matchingResults += "# Matches: "; m_matchingResults += QString::number(matched1.size()); m_matchingResults += "\n";
    m_matchingResults += "# Inliers: "; m_matchingResults += QString::number(inliers1.size()); m_matchingResults += "\n";
    m_matchingResults += "# Inliers Ratio: "; m_matchingResults += QString::number(inlier_ratio); m_matchingResults += "\n";

    return convertMat2QImage(res);
}

QString KOCQAKAZE::getMatchingResults()
{
    return m_matchingResults;
}
