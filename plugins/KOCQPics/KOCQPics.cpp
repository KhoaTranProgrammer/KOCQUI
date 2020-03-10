#include "KOCQPics.h"

static KOCQPics *myPluginInstance = NULL;
static QString pluginName = "KOCQ Pics";

void createNewPlugin(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    KOCQPics::createInstance(engine, rootObject, source, pluginManagerObject);
}

void KOCQPics::createInstance(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject)
{
    if (myPluginInstance == NULL)
    {
        myPluginInstance = new KOCQPics(engine, rootObject, source, pluginManagerObject);
    }
}

KOCQPics::KOCQPics(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject) :
    KOCQPluginBase{ engine, rootObject, source, pluginName, DEFAULT_PATH, pluginManagerObject }
{

}

void KOCQPics::addIconSlot(const QVariant &v)
{
    addIcon(v, "image/icon.png");
}

void KOCQPics::iConClicked()
{
    loadPlugin("qml/MainScreen.qml");
}

void KOCQPics::onPluginLoad()
{
    getPluginContext()->setContextProperty("dipObject", this);
    getPluginContext()->setContextProperty("defaultinput", DEFAULT_PATH);
}

Mat KOCQPics::readImage(const QString &input)
{
    QByteArray byteArr = input.toLocal8Bit();
    return imread(byteArr.data(), IMREAD_COLOR);
}

QImage KOCQPics::convertMat2QImage(const QString &input)
{
    Mat image;
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    QByteArray byteArr = input.toLocal8Bit();

    image = imread(byteArr.data(), IMREAD_COLOR);
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need

    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

QImage KOCQPics::convertMat2QImage(Mat image)
{
    cv::Mat temp(image.cols, image.rows, image.type()); // make the same cv::Mat
    cvtColor(image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}

QImage KOCQPics::basicLinearTransforms(const QString &input, double alpha, int beta)
{
    Mat image = readImage(input);

    Mat new_image = Mat::zeros( image.size(), image.type() );

    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }

    return convertMat2QImage(new_image);
}

QImage KOCQPics::imageNegatives(const QString &input)
{
    Mat src = readImage(input);
    Mat dst = Mat::zeros(src.size(), src.type());
    bitwise_not(src, dst);
    return convertMat2QImage(dst);
}

QImage KOCQPics::gammaCorrection(const QString &input, int gamma_cor)
{
    Mat src = readImage(input);
    double gamma_ = gamma_cor / 100.0;

    //! [changing-contrast-brightness-gamma-correction]
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);

    Mat res = src.clone();
    LUT(src, lookUpTable, res);
    //! [changing-contrast-brightness-gamma-correction]

    return convertMat2QImage(res);
}
