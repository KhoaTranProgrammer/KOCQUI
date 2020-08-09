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
 * This file implements methods to set and display QImage           *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version supports setting and display QImage       *
 * 1.0.1: Aug-09-2020                                               *
 *        Add method clearImage to draw transparent when input image*
 *        is not available                                          *
 *        Emit signal drawingChanged for drawing new input image    *
 *******************************************************************/

#include "KOCQMatImage.h"

KOCQMatImage::KOCQMatImage(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    isImage = false;
}

void KOCQMatImage::paint(QPainter *painter)
{
    if(isImage == true)
    {
        float scale = (this->width() / m_image.width()) < (this->height() / m_image.height()) ?
                    (this->width() / m_image.width()) : (this->height() / m_image.height());
        float startX, startY;
        startX = this->width() / 2 - (m_image.width() * scale) / 2;
        startY = this->height() / 2 - (m_image.height() * scale) / 2;
        QRectF r1(startX, startY, m_image.width() * scale, m_image.height() * scale);
        painter->drawImage(r1, m_image);
        emit drawingChanged();
    }
    else
    {
        QRectF r1(0, 0, this->width(), this->height());
        painter->fillRect(r1, QColor("transparent"));
    }
}

void KOCQMatImage::setImage(const QImage &image)
{
    this->isImage = true;
    this->m_image = image;
    update();
}

void KOCQMatImage::clearImage()
{
    this->isImage = false;
    update();
}
