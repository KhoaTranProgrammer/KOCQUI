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

void KOCQPics::MyLine(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = LINE_8;

    line(img, start, end, Scalar( 0, 0, 255 ), thickness, lineType);
}

void KOCQPics::MyPolygon( Mat img )
{
    int lineType = LINE_8;

    /* Create some points */
    Point rook_points[1][20];
    rook_points[0][0]  = Point(    w/4,   7*w/8 );
    rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
    rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
    rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
    rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
    rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
    rook_points[0][6]  = Point(  3*w/4,     w/8 );
    rook_points[0][7]  = Point( 26*w/40,    w/8 );
    rook_points[0][8]  = Point( 26*w/40,    w/4 );
    rook_points[0][9]  = Point( 22*w/40,    w/4 );
    rook_points[0][10] = Point( 22*w/40,    w/8 );
    rook_points[0][11] = Point( 18*w/40,    w/8 );
    rook_points[0][12] = Point( 18*w/40,    w/4 );
    rook_points[0][13] = Point( 14*w/40,    w/4 );
    rook_points[0][14] = Point( 14*w/40,    w/8 );
    rook_points[0][15] = Point(    w/4,     w/8 );
    rook_points[0][16] = Point(    w/4,   3*w/8 );
    rook_points[0][17] = Point( 13*w/32,  3*w/8 );
    rook_points[0][18] = Point(  5*w/16, 13*w/16 );
    rook_points[0][19] = Point(    w/4,  13*w/16 );

    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 20 };

    fillPoly( img,
        ppt,
        npt,
        1,
        Scalar( 255, 255, 255 ),
        lineType );
}

void KOCQPics::MyEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;

    ellipse(img, Point( w/2, w/2 ), Size( w/4, w/16 ), angle,
        0, 360, Scalar( 255, 0, 0 ), thickness, lineType);
}

void KOCQPics::MyFilledCircle(Mat img, Point center)
{
    circle(img, center, w/32, Scalar( 0, 0, 255 ), FILLED, LINE_8);
}

QImage KOCQPics::simpleDrawing1()
{
    Mat rook_image = Mat::zeros( w, w, CV_8UC3 );

    // Create a convex polygon
    MyPolygon( rook_image );

    // Creating rectangles
    rectangle(rook_image, Point( 0, 7*w/8 ), Point( w, w), Scalar( 0, 255, 255 ), FILLED, LINE_8);

    // Create a few lines
    MyLine(rook_image, Point( 0, 15*w/16 ), Point( w, 15*w/16 ));
    MyLine(rook_image, Point( w/4, 7*w/8 ), Point( w/4, w ));
    MyLine(rook_image, Point( w/2, 7*w/8 ), Point( w/2, w ));
    MyLine(rook_image, Point( 3*w/4, 7*w/8 ), Point( 3*w/4, w ));

    return convertMat2QImage(rook_image);
}

QImage KOCQPics::simpleDrawing2()
{
    /// Create black empty images
    Mat atom_image = Mat::zeros( w, w, CV_8UC3 );

    //![draw_atom]
    /// 1.a. Creating ellipses
    MyEllipse( atom_image, 90 );
    MyEllipse( atom_image, 0 );
    MyEllipse( atom_image, 45 );
    MyEllipse( atom_image, -45 );

    /// 1.b. Creating circles
    MyFilledCircle( atom_image, Point( w/2, w/2) );
    //![draw_atom]

    return convertMat2QImage(atom_image);
}

QImage KOCQPics::homogeneousBlur(const QString &input, int kernel_length)
{
    Mat src = readImage(input);
    Mat dst;

    dst = src.clone();

    //![blur]
    blur( src, dst, Size( kernel_length, kernel_length ), Point( -1, -1));
    //![blur]

    return convertMat2QImage(dst);
}

QImage KOCQPics::gaussianBlur(const QString &input, int kernel_length)
{
    Mat src = readImage(input);
    Mat dst;

    dst = src.clone();

    //![gaussianblur]
    GaussianBlur( src, dst, Size( kernel_length, kernel_length ), 0, 0 );
    //![gaussianblur]

    return convertMat2QImage(dst);
}

QImage KOCQPics::medianFilterBlur(const QString &input, int kernel_length)
{
    Mat src = readImage(input);
    Mat dst;

    dst = src.clone();

    //![gaussianblur]
    medianBlur( src, dst, kernel_length );
    //![gaussianblur]

    return convertMat2QImage(dst);
}

QImage KOCQPics::bilateralFilterBlur(const QString &input, int kernel_length)
{
    Mat src = readImage(input);
    Mat dst;

    dst = src.clone();

    //![bilateralfilter]
    bilateralFilter ( src, dst, kernel_length, kernel_length*2, kernel_length/2 );
    //![bilateralfilter]

    return convertMat2QImage(dst);
}
