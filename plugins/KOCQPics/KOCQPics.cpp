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

QImage KOCQPics::basicLinearTransforms(const QString &input, double alpha, int beta)
{
    Mat image;
    QByteArray byteArr = input.toLocal8Bit();

    image = imread(byteArr.data(), IMREAD_COLOR);

    Mat new_image = Mat::zeros( image.size(), image.type() );

    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }

    Mat temp(new_image.cols, new_image.rows, new_image.type()); // make the same cv::Mat
    cvtColor(new_image, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage result((uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    return result.copy();
}
