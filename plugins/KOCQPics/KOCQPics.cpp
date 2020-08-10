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
 * This class implements digital image processing algorithm by using*
 * OpenCV                                                           *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version supports some algorithms:                 *
 *        LinearTransforms, Negatives, GammaCorrection, Erosion,    *
 *        Dilation, Morphology, Drawing, Smoothing, Threshold,      *
 *        Transforms, Hough                                         *
 * 1.0.1: May-28-2020                                               *
 *        Copy resource into hash folder                            *
 * 1.0.2: Aug-10-2020                                               *
 *        Support get default input image data/lena.jpg             *
 *******************************************************************/

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
    addIcon(v, "e36c5bd2d754aa0013628ef3f63ae7a4/image/icon.png");
}

void KOCQPics::iConClicked()
{
    loadPlugin("qrc:/e36c5bd2d754aa0013628ef3f63ae7a4/qml/MainScreen.qml");
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

QString KOCQPics::defaultInput() const
{
    QDir dir;
    QString defaultImage = dir.absolutePath() + "/data/lena.jpg";
    return defaultImage;
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

QImage KOCQPics::threshold_Demo(const QString &input, int threshold_value, int threshold_type)
{
    Mat src = readImage(input);
    Mat src_gray, dst;

    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray

    threshold( src_gray, dst, threshold_value, 255, threshold_type );

    return convertMat2QImage(dst);
}

QImage KOCQPics::copyMakeBorder_Demo(const QString &input, int borderType)
{
    Mat src = readImage(input);
    Mat dst;
    int top, bottom, left, right;
    RNG rng(12345);
    int borderTypeMacro = BORDER_CONSTANT;

    switch (borderType)
    {
        case 0: borderTypeMacro = BORDER_CONSTANT; break;
        case 1: borderTypeMacro = BORDER_REPLICATE; break;
        case 2: borderTypeMacro = BORDER_REFLECT; break;
        case 3: borderTypeMacro = BORDER_WRAP; break;
        default: break;
    }

    //![init_arguments]
    // Initialize arguments for the filter
    top = (int) (0.05*src.rows); bottom = top;
    left = (int) (0.05*src.cols); right = left;
    //![init_arguments]

    //![update_value]
    Scalar value( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
    //![update_value]

    //![copymakeborder]
    copyMakeBorder( src, dst, top, bottom, left, right, borderTypeMacro, value );
    //![copymakeborder]

    return convertMat2QImage(dst);
}

QImage KOCQPics::sobel_Demo(const QString &input, int ksize, int scale, int delta)
{
    //![variables]
    // First we declare the variables we are going to use
    Mat src, src_gray, grad;
    int ddepth = CV_16S;
    //![variables]

    //![load]
    Mat image = readImage(input);
    //![load]

    //![reduce_noise]
    // Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    //![reduce_noise]

    //![convert_to_gray]
    // Convert the image to grayscale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![sobel]
    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);

    /// Gradient Y
    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
    //![sobel]

    //![convert]
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    //![convert]

    //![blend]
    /// Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    //![blend]

    return convertMat2QImage(grad);
}

QImage KOCQPics::laplacian_Demo(const QString &input, int kernel_size, int scale, int delta)
{
    //![variables]
    // First we declare the variables we are going to use
    Mat src_gray, dst;
    int ddepth = CV_16S;
    //![variables]

    //![load]
    Mat src = readImage(input);
    //![load]

    //![reduce_noise]
    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur( src, src, Size(3, 3), 0, 0, BORDER_DEFAULT );
    //![reduce_noise]

    //![convert_to_gray]
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to grayscale
    //![convert_to_gray]

    /// Apply Laplace function
    Mat abs_dst;
    //![laplacian]
    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    //![laplacian]

    //![convert]
    // converting back to CV_8U
    convertScaleAbs( dst, abs_dst );
    //![convert]

    return convertMat2QImage(abs_dst);
}

QImage KOCQPics::canny_Demo(const QString &input, int threshold_value)
{
    Mat src_gray, dst, detected_edges;
    const int ratio = 3;
    const int kernel_size = 3;

    Mat src = readImage(input);

    //![create_mat]
    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );
    //![create_mat]

    //![convert_to_gray]
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    //![convert_to_gray]

    //![reduce_noise]
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    //![reduce_noise]

    //![canny]
    /// Canny detector
    Canny( detected_edges, detected_edges, threshold_value,  threshold_value * ratio, kernel_size );
    //![canny]

    /// Using Canny's output as a mask, we display our result
    //![fill]
    dst = Scalar::all(0);
    //![fill]

    //![copyto]
    src.copyTo( dst, detected_edges);
    //![copyto]

    return convertMat2QImage(dst);
}

QImage KOCQPics::standardHoughLines(const QString &input, int s_trackbar, int min_threshold)
{
    Mat src_gray, edges, standard_hough;
    Mat src = readImage(input);

    /// Pass the image to gray
    cvtColor( src, src_gray, COLOR_RGB2GRAY );

    /// Apply Canny edge detector
    Canny( src_gray, edges, 50, 200, 3 );

    vector<Vec2f> s_lines;
    cvtColor( edges, standard_hough, COLOR_GRAY2BGR );

    /// 1. Use Standard Hough Transform
    HoughLines( edges, s_lines, 1, CV_PI/180, min_threshold + s_trackbar, 0, 0 );

    /// Show the result
    for( size_t i = 0; i < s_lines.size(); i++ )
    {
        float r = s_lines[i][0];
        float t = s_lines[i][1];
        double cos_t = cos(t);
        double sin_t = sin(t);
        double x0 = r*cos_t;
        double y0 = r*sin_t;
        double alpha = 1000;

        Point pt1( cvRound(x0 + alpha*(-sin_t)), cvRound(y0 + alpha*cos_t) );
        Point pt2( cvRound(x0 - alpha*(-sin_t)), cvRound(y0 - alpha*cos_t) );
        line( standard_hough, pt1, pt2, Scalar(255,0,0), 3, LINE_AA);
    }

    return convertMat2QImage(standard_hough);
}

QImage KOCQPics::probabilisticHoughLines(const QString &input, int p_trackbar, int min_threshold)
{
    Mat src_gray, edges, probabilistic_hough;
    Mat src = readImage(input);

    /// Pass the image to gray
    cvtColor( src, src_gray, COLOR_RGB2GRAY );

    /// Apply Canny edge detector
    Canny( src_gray, edges, 50, 200, 3 );

    vector<Vec4i> p_lines;
    cvtColor( edges, probabilistic_hough, COLOR_GRAY2BGR );

    /// 2. Use Probabilistic Hough Transform
    HoughLinesP( edges, p_lines, 1, CV_PI/180, min_threshold + p_trackbar, 30, 10 );

    /// Show the result
    for( size_t i = 0; i < p_lines.size(); i++ )
    {
        Vec4i l = p_lines[i];
        line( probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
    }

    return convertMat2QImage(probabilistic_hough);
}

QImage KOCQPics::houghCirclesDetection(const QString &input, int cannyThreshold, int accumulatorThreshold)
{
    Mat src_gray;
    Mat src = readImage(input);
    int cannyThres = cannyThreshold;
    int accumulatorThres = accumulatorThreshold;

    // Convert it to gray
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    // Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    cannyThres = std::max(cannyThreshold, 1);
    accumulatorThres = std::max(accumulatorThreshold, 1);

    // will hold the results of the detection
    std::vector<Vec3f> circles;

    // runs the actual detection
    HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThres, accumulatorThres, 0, 0 );

    // clone the colour, input image for displaying purposes
    Mat display = src.clone();
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }

    return convertMat2QImage(display);
}

QImage KOCQPics::remapping(const QString &input, int types)
{
    Mat src = readImage(input);

    //! [Create]
    /// Create dst, map_x and map_y with the same size as src:
    Mat dst(src.size(), src.type());
    Mat map_x(src.size(), CV_32FC1);
    Mat map_y(src.size(), CV_32FC1);
    //! [Create]

    // Fill the map_x and map_y matrices with 4 types of mappings
    for( int i = 0; i < map_x.rows; i++ )
    {
        for( int j = 0; j < map_x.cols; j++ )
        {
            switch( types )
            {
            case 0:
                if( j > map_x.cols*0.25 && j < map_x.cols*0.75 && i > map_x.rows*0.25 && i < map_x.rows*0.75 )
                {
                    map_x.at<float>(i, j) = 2*( j - map_x.cols*0.25f ) + 0.5f;
                    map_y.at<float>(i, j) = 2*( i - map_x.rows*0.25f ) + 0.5f;
                }
                else
                {
                    map_x.at<float>(i, j) = 0;
                    map_y.at<float>(i, j) = 0;
                }
                break;
            case 1:
                map_x.at<float>(i, j) = (float)j;
                map_y.at<float>(i, j) = (float)(map_x.rows - i);
                break;
            case 2:
                map_x.at<float>(i, j) = (float)(map_x.cols - j);
                map_y.at<float>(i, j) = (float)i;
                break;
            case 3:
                map_x.at<float>(i, j) = (float)(map_x.cols - j);
                map_y.at<float>(i, j) = (float)(map_x.rows - i);
                break;
            default:
                break;
            } // end of switch
        }
    }

    remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

    return convertMat2QImage(dst);
}
