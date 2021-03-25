#ifndef MAINFORM_H
#define MAINFORM_H

#include "image.h"
#include <QWidget>
#include <QMouseEvent>
#include <QDir>
#include <QPushButton>
#include <QPixmap>
#include <QTransform>
#include <QPainter>
#include <QPaintDevice>
#include <QFileDialog>
#include <QDirIterator>
#include <QVariant>
#include <QBuffer>
#include <QScrollArea>
#include <QMouseEvent>
#include <QWheelEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainform; }
QT_END_NAMESPACE

class Image;

class Mainform : public QWidget
{
    Q_OBJECT

public:
    Mainform(QWidget *parent = nullptr);
    ~Mainform();

    void showImg();
    void fillMenu();
    void setZoom(double change);
    void safeImg();
    void setupWidget();
    //void scaleToOriginal(QString path);

    bool mouseClick;
    QList<QDir> dirs;
    QList <QPushButton *> imgBtnList;
    QList <QPushButton *> deleteBtnList;
    QList<QString> imgList;
    QList<QPixmap> pix;

    double zoom;
    QPoint offset;

protected:
    void paintEvent(QPaintEvent *event) override;


public slots:
    void onBtnOneClickedSlot();
    void onBtnTwoClickedSlot();
    void onBtnFourClickedSlot();
    void onBtnSafePathClickedSlot();
    void onImgDropDownSelectionSlot();
    void onImgDropDownChange();
    void onBtnDemoSlot();
    void zoomIn();
    void zoomOut();
    void safeSlot();
    void deleteSlot();
    void loadImgSlot();

    void wheelEvent(QWheelEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::Mainform *ui;

friend class Image;
};
#endif // MAINFORM_H
