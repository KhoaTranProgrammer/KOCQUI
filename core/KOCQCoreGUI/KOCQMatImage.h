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

private:
    bool isImage;   // Image is available or not
    QImage m_image; // QImage image content
};

#endif // KOCQMATIMAGE_H
