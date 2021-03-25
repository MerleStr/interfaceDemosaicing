#include "image.h"

Image::Image()
{

}

Image::Image(QWidget *w) {
    zoom = 1;
    mousePress = false;

    frameX = this->x();
    frameY = this->y();
    frameW = this->width();
    frameH = this->height();
}

void Image::setPixmap(QString path) {
    pm = path;
    repaint();
}

void Image::setZoom(double change) {
    zoom = change;
    repaint();
}

void Image::setOffset(QPoint point) {
    offset = point;
}

void Image::setMouse(QPoint point) {
    mouse = point;
}

void Image::setMousePress(bool press) {
    mousePress = press;
}

void Image::setMoveWidth(double w) {
    moveWidth = w;
    repaint();
}

double Image::getMoveWidth() {
    return moveWidth;
}

void Image::setMoveHeight(double h) {
    moveHeight = h;
    repaint();
}

double Image::getMoveHeight() {
    return moveHeight;
}

void Image::safe(QString filename) {
    QPixmap p = pm.transformed(m);
    QPixmap pix = p.copy(-moveWidth, -moveHeight, this->width(), this->height());

    pix.save(filename, "PNG");
}

void Image::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    m = QTransform();

    if(pm.isNull()) {
        p.eraseRect(this->rect());
    }

    m.translate(moveWidth, moveHeight);

    //m.translate(-mouse.x(), -mouse.y());
    m.scale(zoom, zoom);
    //m.translate(mouse.x(), mouse.y());

    p.setWorldTransform(m);

    p.drawPixmap(this->rect(), pm, this->rect());

    p.end();
}

void Image::wheelEvent(QWheelEvent *event) {

}

void Image::mouseMoveEvent(QMouseEvent *event) {
    if(mousePress) {
        QPoint mousePos = event->pos();

        moveWidth = (mousePos.x() - offset.x());
        moveHeight = (mousePos.y() - offset.y());

        repaint();
    }
}


