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

QImage KOCQPics::erosion(const QString &input, int erosion_elem, int erosion_size)
{
    Mat src = readImage(input);
    Mat erosion_dst;

    int erosion_type = 0;
    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    //![kernel]
    Mat element = getStructuringElement( erosion_type,
                  Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                  Point( erosion_size, erosion_size ) );
    //![kernel]

    // Apply the erosion operation
    erode(src, erosion_dst, element);

    return convertMat2QImage(erosion_dst);
}

QImage KOCQPics::dilation(const QString &input, int dilation_elem, int dilation_size)
{
    Mat src = readImage(input);
    Mat dilation_dst;

    int dilation_type = 0;
    if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( dilation_type,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );

    // Apply the dilation operation
    dilate( src, dilation_dst, element );

    return convertMat2QImage(dilation_dst);
}

QImage KOCQPics::morphologyOperations(const QString &input, int morph_elem, int morph_size, int morph_operator)
{
    Mat src = readImage(input);
    Mat dst;

    // Since MORPH_X : 2,3,4,5 and 6
    //![operation]
    int operation = morph_operator + 2;
    //![operation]

    Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

    /// Apply the specified morphology operation
    morphologyEx( src, dst, operation, element );

    return convertMat2QImage(dst);
}
