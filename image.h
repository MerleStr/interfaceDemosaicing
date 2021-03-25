#ifndef IMAGE_H
#define IMAGE_H

#include "mainform.h"
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <QDir>
#include <QMouseEvent>

class Image : public QFrame
{
    Q_OBJECT

public:
    Image();
    Image(QWidget *w = nullptr);

    double zoom;
    bool mousePress;
    QPoint offset;
    QPoint mouse;
    double moveWidth;
    double moveHeight;

    int frameX;
    int frameY;
    int frameW;
    int frameH;

    void setZoom(double change);
    void setZoom(double changeWidth, double changeHeight);
    void setPixmap(QString path);
    void setMousePress(bool press);
    void setOffset(QPoint point);
    void setMouse(QPoint point);
    void setMoveWidth(double w);
    void setMoveHeight(double h);
    double getMoveWidth();
    double getMoveHeight();
    void safe(QString filename);

    QPixmap pm;
    QTransform m;

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

friend class Mainform;
};

#endif // IMAGE_H
