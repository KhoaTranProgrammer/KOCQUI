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
        QRectF r1(0, 0, m_image.width(), m_image.height());
        painter->drawImage(r1, m_image);
    }
    else
    {

    }
}

void KOCQMatImage::setImage(const QImage &image)
{
    this->isImage = true;
    this->m_image = image;
    update();
}
