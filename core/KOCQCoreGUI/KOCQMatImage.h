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
 * This file defines methods/properties to set and display QImage   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version supports setting and display QImage       *
 * 1.0.1: Aug-09-2020                                               *
 *        Add method clearImage to draw transparent when input image*
 *        is not available                                          *
 *        Add signal drawingChanged for drawing new input image     *
 *******************************************************************/

#ifndef KOCQMATIMAGE_H
#define KOCQMATIMAGE_H

#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>

class KOCQMatImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image WRITE setImage)
public:
    KOCQMatImage(QQuickItem *parent = 0);

    void paint(QPainter *painter);

public slots:
    void setImage(const QImage &image);
    void clearImage();

signals:
    void drawingChanged();

private:
    bool isImage;   // Image is available or not
    QImage m_image; // QImage image content
};

#endif // KOCQMATIMAGE_H
