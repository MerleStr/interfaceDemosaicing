#include "mainform.h"
#include "ui_mainform.h"

#include <QProcess>


Mainform::Mainform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainform)
{
    ui->setupUi(this);

    connect(ui->btnOne, &QPushButton::clicked, this, &Mainform::onBtnOneClickedSlot);
    connect(ui->btnTwo, &QPushButton::clicked, this, &Mainform::onBtnTwoClickedSlot);
    connect(ui->btnFour, &QPushButton::clicked, this, &Mainform::onBtnFourClickedSlot);
    connect(ui->btnZoomIn, &QPushButton::clicked, this, &Mainform::zoomIn);
    connect(ui->btnZoomOut, &QPushButton::clicked, this, &Mainform::zoomOut);
    connect(ui->btnSafe, &QPushButton::clicked, this, &Mainform::safeSlot);
    connect(ui->btnImg, &QPushButton::clicked, this, &Mainform::loadImgSlot);
    connect(ui->btnDelete, &QPushButton::clicked, this, &Mainform::deleteSlot);
    //connect(ui->btnSafePath, &QPushButton::clicked, this, &Mainform::onBtnSafePathClickedSlot);
    connect(ui->btnDemo, &QPushButton::clicked, this, &Mainform::onBtnDemoSlot);

    QObject::connect(ui->imgDropdown, SIGNAL(activated(int)), this, SLOT(onImgDropDownSelectionSlot()));
    QObject::connect(ui->imgWindow1, SIGNAL(activated(int)), this, SLOT(onImgDropDownChange()));
    QObject::connect(ui->imgWindow2, SIGNAL(activated(int)), this, SLOT(onImgDropDownChange()));
    QObject::connect(ui->imgWindow3, SIGNAL(activated(int)), this, SLOT(onImgDropDownChange()));
    QObject::connect(ui->imgWindow4, SIGNAL(activated(int)), this, SLOT(onImgDropDownChange()));

    zoom = 1;
    mouseClick = false;
    setupWidget();
}

Mainform::~Mainform()
{
    delete ui;
}

void Mainform::setupWidget() {
    this->setStyleSheet("background-color: white;");

    ui->imgDropdown->setStyleSheet("background-color: #dae9f8; border: 2px");
    ui->imgWindow1->setStyleSheet("background-color: #e4ffdd; border: 2px; font: 18px");
    ui->imgWindow1->hide();
    ui->imgWindow2->setStyleSheet("background-color: #e4ffdd; border: 2px; font: 18px");
    ui->imgWindow2->hide();
    ui->imgWindow3->setStyleSheet("background-color: #e4ffdd; border: 2px; font: 18px");
    ui->imgWindow3->hide();
    ui->imgWindow4->setStyleSheet("background-color: #e4ffdd; border: 2px; font: 18px");
    ui->imgWindow4->hide();

    ui->selcFrame->setStyleSheet("background-color: #e4e4e4");
    ui->imgFrame->setLineWidth(1);
    ui->imgFrame->isVisible();

    ui->btnZoomIn->setStyleSheet("background-color: #d4e9f8; border: 2px; font: 30px");
    ui->btnZoomOut->setStyleSheet("background-color: #d4e9f8; border: 2px; font: 30px");

    ui->btnOne->setStyleSheet("background-color: white; border: 2px");
    ui->btnTwo->setStyleSheet("background-color: white; border: 2px");
    ui->btnFour->setStyleSheet("background-color: white; border: 2px");
    ui->btnSafe->setStyleSheet("background-color: #dae9f8; font: 18px; border: 2px");
    ui->btnImg->setStyleSheet("background-color: #dae9f8; font: 18px; border: 2px");
    ui->btnDelete->setStyleSheet("background-color: #dae9f8; font: 18px; border: 2px");

    ui->btnDemo->setStyleSheet("background-color: #dae9f8; font: 18px; border: 2px");

    ui->window1->setStyleSheet("background-color: white");
    ui->window21->setStyleSheet("background-color: white");
    ui->window22->setStyleSheet("background-color: white");
    ui->window41->setStyleSheet("background-color: white");
    ui->window42->setStyleSheet("background-color: white");
    ui->window43->setStyleSheet("background-color: white");
    ui->window44->setStyleSheet("background-color: white");
}

void Mainform::safeImg() {
    const QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString filename1 = dir + "\\" + ui->imgWindow1->currentText();
    QString filename2 = dir + "\\" + ui->imgWindow2->currentText();
    QString filename3 = dir + "\\" + ui->imgWindow3->currentText();
    QString filename4 = dir + "\\" + ui->imgWindow4->currentText();

    if(ui->imgFrameTwo_1->isVisible() && ui->imgFrameTwo_2->isVisible()) {
        ui->imgFrameTwo_1->safe(filename1);
        ui->imgFrameTwo_2->safe(filename2);
    } else if(ui->imgFrameFour_1->isVisible() && ui->imgFrameFour_2->isVisible() &&
              ui->imgFrameFour_3->isVisible() && ui->imgFrameFour_4->isVisible()) {
        ui->imgFrameFour_1->safe(filename1);
        ui->imgFrameFour_2->safe(filename2);
        ui->imgFrameFour_3->safe(filename3);
        ui->imgFrameFour_4->safe(filename4);
    } else if(ui->imgFrame->isVisible()) {
        ui->imgFrame->safe(filename1);
    }
}

void Mainform::setZoom(double change) {
    zoom += change;

    if(ui->imgFrameTwo_1->isVisible() && ui->imgFrameTwo_2->isVisible()) {
        ui->imgFrameTwo_1->setZoom(zoom);
        ui->imgFrameTwo_2->setZoom(zoom);
    } else if(ui->imgFrameFour_1->isVisible() && ui->imgFrameFour_2->isVisible() &&
              ui->imgFrameFour_3->isVisible() && ui->imgFrameFour_4->isVisible()) {
        ui->imgFrameFour_1->setZoom(zoom);
        ui->imgFrameFour_2->setZoom(zoom);
        ui->imgFrameFour_3->setZoom(zoom);
        ui->imgFrameFour_4->setZoom(zoom);
    } else if(ui->imgFrame->isVisible()) {
        ui->imgFrame->setZoom(zoom);
    }
}

void Mainform::loadImgSlot() {
    const QString filepath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QDir dir(filepath, " ", QDir::Name, QDir::Dirs);

    dirs.push_back(dir);


    QFile f(dir.path());
    QFileInfo info(f.fileName());

    if(info.exists()) {
        ui->imgDropdown->addItem(info.fileName());
    }
}

void Mainform::fillMenu() {
    ui->imgWindow1->clear();
    ui->imgWindow2->clear();
    ui->imgWindow3->clear();
    ui->imgWindow4->clear();

    int dropdownIndex = ui->imgDropdown->currentIndex();
    if(dropdownIndex >= 0 && dropdownIndex < dirs.length()) {
        QDir d = dirs.value(dropdownIndex).path();

        imgList = d.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);

        for(QString s : imgList) {
            ui->imgWindow1->addItem(s);
            ui->imgWindow2->addItem(s);
            ui->imgWindow3->addItem(s);
            ui->imgWindow4->addItem(s);
        }
    }
    showImg();
}

void Mainform::showImg() {
        QString path = dirs.value(ui->imgDropdown->currentIndex()).path();

        //scaleToOriginal(path);

        int imgIndex_1 = ui->imgWindow1->currentIndex();
        int imgIndex_2 = ui->imgWindow2->currentIndex();
        int imgIndex_3 = ui->imgWindow3->currentIndex();
        int imgIndex_4 = ui->imgWindow4->currentIndex();

        QString imgPath_1 = path + "//" + imgList.value(imgIndex_1);
        QPixmap pm_1(imgPath_1);

        QString imgPath_2 = path + "//" + imgList.value(imgIndex_2);
        QPixmap pm_2(imgPath_2);

        QString imgPath_3 = path + "//" + imgList.value(imgIndex_3);
        QPixmap pm_3(imgPath_3);

        QString imgPath_4 = path + "//" + imgList.value(imgIndex_4);
        QPixmap pm_4(imgPath_4);

        if(ui->imgFrameTwo_1->isVisible() && ui->imgFrameTwo_2->isVisible()) {
            ui->imgFrame->setPixmap("");
            ui->imgFrameTwo_1->setPixmap(imgPath_1);
            ui->imgFrameTwo_2->setPixmap(imgPath_2);

            if(zoom == 1) {
                zoom = (double) ui->imgFrameTwo_1->height() / pm_1.height();
            }

            ui->imgFrameTwo_1->setZoom(zoom);
            ui->imgFrameTwo_2->setZoom(zoom);

        } else if(ui->imgFrameFour_1->isVisible() && ui->imgFrameFour_2->isVisible() &&
                  ui->imgFrameFour_3->isVisible() && ui->imgFrameFour_4->isVisible()) {
            ui->imgFrame->setPixmap("");
            ui->imgFrameFour_1->setPixmap(imgPath_1);
            ui->imgFrameFour_2->setPixmap(imgPath_2);
            ui->imgFrameFour_3->setPixmap(imgPath_3);
            ui->imgFrameFour_4->setPixmap(imgPath_4);

            if(zoom == 1) {
                zoom = (double) ui->imgFrameFour_1->width() / pm_1.width();
            }

            ui->imgFrameFour_1->setZoom(zoom);
            ui->imgFrameFour_2->setZoom(zoom);
            ui->imgFrameFour_3->setZoom(zoom);
            ui->imgFrameFour_4->setZoom(zoom);

        } else if(ui->imgFrame->isVisible()) {
            ui->imgFrame->setPixmap(imgPath_1);

            if(zoom == 1) {
                zoom = (double) ui->imgFrame->width() / pm_1.width();
            }

            ui->imgFrame->setZoom(zoom);
        }
}

void Mainform::onBtnOneClickedSlot() {
    ui->imgFrame->show();
    ui->imgFrameTwo_1->hide();
    ui->imgFrameTwo_2->hide();
    ui->imgFrameFour_1->hide();
    ui->imgFrameFour_2->hide();
    ui->imgFrameFour_3->hide();
    ui->imgFrameFour_4->hide();

    ui->imgWindow1->show();
    ui->imgWindow2->hide();
    ui->imgWindow3->hide();
    ui->imgWindow4->hide();

    ui->btnOne->setStyleSheet("background-color: #e4ffdd; border: 2px");
    ui->btnTwo->setStyleSheet("background-color: #ffffff; border: 2px");
    ui->btnFour->setStyleSheet("background-color: #ffffff; border: 2px");

    ui->btnOne->update();

    if(imgList.isEmpty()) {
        fillMenu();
    } else {
        showImg();
    }
}

void Mainform::onBtnTwoClickedSlot() {
    ui->imgFrame->show();
    ui->imgFrameTwo_1->show();
    ui->imgFrameTwo_2->show();
    ui->imgFrameFour_1->hide();
    ui->imgFrameFour_2->hide();
    ui->imgFrameFour_3->hide();
    ui->imgFrameFour_4->hide();

    ui->imgWindow1->show();
    ui->imgWindow2->show();
    ui->imgWindow3->hide();
    ui->imgWindow4->hide();

    ui->btnTwo->setStyleSheet("background-color: #e4ffdd; border: 2px");
    ui->btnOne->setStyleSheet("background-color: #ffffff; border: 2px");
    ui->btnFour->setStyleSheet("background-color: #ffffff; border: 2px");
    ui->btnTwo->update();

    if(imgList.isEmpty()) {
        fillMenu();
    } else {
        showImg();
    }
}

void Mainform::onBtnFourClickedSlot() {
    ui->imgFrame->show();
    ui->imgFrameTwo_1->hide();
    ui->imgFrameTwo_2->hide();
    ui->imgFrameFour_1->show();
    ui->imgFrameFour_2->show();
    ui->imgFrameFour_3->show();
    ui->imgFrameFour_4->show();

    ui->imgWindow1->show();
    ui->imgWindow2->show();
    ui->imgWindow3->show();
    ui->imgWindow4->show();

    ui->btnFour->setStyleSheet("background-color: #e4ffdd; border: 2px");
    ui->btnOne->setStyleSheet("background-color: #ffffff; border: 2px");
    ui->btnTwo->setStyleSheet("background-color: #ffffff; border: 2px");
    ui->btnFour->update();

    if(imgList.isEmpty()) {
        fillMenu();
    } else {
        showImg();
    }
}

void Mainform::onBtnDemoSlot() {
    QProcess *process = new QProcess(this);
    QString file = "C:/Users/merle/Desktop/save/interfaceDemosaicing/demosaicing.exe";

    int index = ui->imgDropdown->currentIndex();
    QDir d = dirs.value(index).path();

    QStringList arguments;
    arguments << dirs.value(index).path() << imgList.at(0);
    process->startDetached(file, arguments);

    process->kill();

    //fillMenu();
    //update();
}

void Mainform::onBtnSafePathClickedSlot() {

}

void Mainform::onImgDropDownSelectionSlot() {
    fillMenu();
}

void Mainform::onImgDropDownChange() {
    showImg();
}

void Mainform::zoomIn() {
    setZoom(0.50);
}

void Mainform::zoomOut() {
    setZoom(-0.50);
}

void Mainform::safeSlot() {
    safeImg();
}

void Mainform::deleteSlot() {
    int dropdownIndex = ui->imgDropdown->currentIndex();

    if(dropdownIndex >= 0 && dropdownIndex < dirs.length()) {
        dirs.takeAt(dropdownIndex);

        ui->imgDropdown->setCurrentIndex(0);
        ui->imgDropdown->removeItem(dropdownIndex);
        showImg();
    }
}

void Mainform::wheelEvent(QWheelEvent *event) {
    if(event->delta() > 0) {
        setZoom(0.10);
    } else if(event->delta() < 0) {
        setZoom(-0.10);
    }
}

void Mainform::paintEvent(QPaintEvent *event) {

}

void Mainform::dragMoveEvent(QDragMoveEvent *event) {

}

void Mainform::mouseMoveEvent(QMouseEvent *event) {
    QPoint p = event->pos();

    if(ui->imgFrameTwo_1->isVisible() && ui->imgFrameTwo_2->isVisible()) {
        ui->imgFrameTwo_1->setMouse(event->pos());
        ui->imgFrameTwo_2->setMouse(event->pos());

    } else if(ui->imgFrameFour_1->isVisible() && ui->imgFrameFour_2->isVisible() &&
              ui->imgFrameFour_3->isVisible() && ui->imgFrameFour_4->isVisible()) {
        ui->imgFrameFour_1->setMouse(event->pos());
        ui->imgFrameFour_2->setMouse(event->pos());
        ui->imgFrameFour_3->setMouse(event->pos());
        ui->imgFrameFour_4->setMouse(event->pos());

    } else if(ui->imgFrame->isVisible()) {
        ui->imgFrame->setMouse(event->pos());
    }
}

void Mainform::mousePressEvent(QMouseEvent *event) {
    mouseClick = true;
    offset = event->pos();

    if(ui->imgFrameTwo_1->isVisible() && ui->imgFrameTwo_2->isVisible()) {
        ui->imgFrameTwo_1->setOffset(offset);
        ui->imgFrameTwo_2->setOffset(offset);

        ui->imgFrameTwo_1->setMousePress(mouseClick);
        ui->imgFrameTwo_2->setMousePress(mouseClick);

    } else if(ui->imgFrameFour_1->isVisible() && ui->imgFrameFour_2->isVisible() &&
              ui->imgFrameFour_3->isVisible() && ui->imgFrameFour_4->isVisible()) {
        ui->imgFrameFour_1->setOffset(offset);
        ui->imgFrameFour_2->setOffset(offset);
        ui->imgFrameFour_3->setOffset(offset);
        ui->imgFrameFour_4->setOffset(offset);

        ui->imgFrameFour_1->setMousePress(mouseClick);
        ui->imgFrameFour_2->setMousePress(mouseClick);
        ui->imgFrameFour_3->setMousePress(mouseClick);
        ui->imgFrameFour_4->setMousePress(mouseClick);

    } else if(ui->imgFrame->isVisible()) {
        ui->imgFrame->setOffset(offset);
        ui->imgFrame->setMousePress(mouseClick);
    }
}

void Mainform::mouseReleaseEvent(QMouseEvent *event) {
    mouseClick = false;
    ui->imgFrame->setMousePress(mouseClick);
    ui->imgFrameTwo_1->setMousePress(mouseClick);
    ui->imgFrameTwo_2->setMousePress(mouseClick);
    ui->imgFrameFour_1->setMousePress(mouseClick);
    ui->imgFrameFour_2->setMousePress(mouseClick);
    ui->imgFrameFour_3->setMousePress(mouseClick);
    ui->imgFrameFour_4->setMousePress(mouseClick);

    if(ui->imgFrameTwo_1->isVisible() && ui->imgFrameTwo_2->isVisible()) {
         if((ui->imgFrameTwo_1->x() + ui->imgFrame->x()) < offset.x() && offset.x() < (ui->imgFrameTwo_1->width() + ui->imgFrameTwo_1->x() + ui->imgFrame->x())) {
             ui->imgFrameTwo_2->setMoveWidth(ui->imgFrameTwo_1->getMoveWidth());
             ui->imgFrameTwo_2->setMoveHeight(ui->imgFrameTwo_1->getMoveHeight());
         } else if((ui->imgFrameTwo_2->x() + ui->imgFrame->x()) < offset.x() && offset.x() < (ui->imgFrameTwo_2->width() + ui->imgFrameTwo_2->x() + ui->imgFrame->x())) {
             ui->imgFrameTwo_1->setMoveWidth(ui->imgFrameTwo_2->getMoveWidth());
             ui->imgFrameTwo_1->setMoveHeight(ui->imgFrameTwo_2->getMoveHeight());
         }
    } else if(ui->imgFrameFour_1->isVisible() && ui->imgFrameFour_2->isVisible() &&
              ui->imgFrameFour_3->isVisible() && ui->imgFrameFour_4->isVisible()) {
        if((ui->imgFrameFour_1->x() + ui->imgFrame->x()) < offset.x() && offset.x() < (ui->imgFrameFour_1->x() + ui->imgFrameFour_1->width() + ui->imgFrame->x())) {
            if((ui->imgFrameFour_1->y() + ui->imgFrame->y()) < offset.y() && offset.y() < (ui->imgFrameFour_1->y() + ui->imgFrameFour_1->height() + ui->imgFrame->y())) {
                ui->imgFrameFour_2->setMoveWidth(ui->imgFrameFour_1->getMoveWidth());
                ui->imgFrameFour_2->setMoveHeight(ui->imgFrameFour_1->getMoveHeight());
                ui->imgFrameFour_3->setMoveWidth(ui->imgFrameFour_1->getMoveWidth());
                ui->imgFrameFour_3->setMoveHeight(ui->imgFrameFour_1->getMoveHeight());
                ui->imgFrameFour_4->setMoveWidth(ui->imgFrameFour_1->getMoveWidth());
                ui->imgFrameFour_4->setMoveHeight(ui->imgFrameFour_1->getMoveHeight());
            } else if((ui->imgFrameFour_3->y() + ui->imgFrame->y()) < offset.y() && offset.y() < (ui->imgFrameFour_3->y() + ui->imgFrameFour_3->height() + ui->imgFrame->y())) {
                ui->imgFrameFour_1->setMoveWidth(ui->imgFrameFour_3->getMoveWidth());
                ui->imgFrameFour_1->setMoveHeight(ui->imgFrameFour_3->getMoveHeight());
                ui->imgFrameFour_2->setMoveWidth(ui->imgFrameFour_3->getMoveWidth());
                ui->imgFrameFour_2->setMoveHeight(ui->imgFrameFour_3->getMoveHeight());
                ui->imgFrameFour_4->setMoveWidth(ui->imgFrameFour_3->getMoveWidth());
                ui->imgFrameFour_4->setMoveHeight(ui->imgFrameFour_3->getMoveHeight());
            }
        } else if((ui->imgFrameFour_2->x() + ui->imgFrame->x()) < offset.x() && offset.x() < (ui->imgFrameFour_2->x() + ui->imgFrameFour_2->width() + ui->imgFrame->x())) {
            if((ui->imgFrameFour_2->y() + ui->imgFrame->y()) < offset.y() && offset.y() < (ui->imgFrameFour_2->y() + ui->imgFrameFour_2->height() + ui->imgFrame->y())) {
                ui->imgFrameFour_1->setMoveWidth(ui->imgFrameFour_2->getMoveWidth());
                ui->imgFrameFour_1->setMoveHeight(ui->imgFrameFour_2->getMoveHeight());
                ui->imgFrameFour_3->setMoveWidth(ui->imgFrameFour_2->getMoveWidth());
                ui->imgFrameFour_3->setMoveHeight(ui->imgFrameFour_2->getMoveHeight());
                ui->imgFrameFour_4->setMoveWidth(ui->imgFrameFour_2->getMoveWidth());
                ui->imgFrameFour_4->setMoveHeight(ui->imgFrameFour_2->getMoveHeight());
            } else if((ui->imgFrameFour_4->y() + ui->imgFrame->y()) < offset.y() && offset.y() < (ui->imgFrameFour_4->y() + ui->imgFrameFour_4->height()) + ui->imgFrame->y()) {
                ui->imgFrameFour_1->setMoveWidth(ui->imgFrameFour_4->getMoveWidth());
                ui->imgFrameFour_1->setMoveHeight(ui->imgFrameFour_4->getMoveHeight());
                ui->imgFrameFour_2->setMoveWidth(ui->imgFrameFour_4->getMoveWidth());
                ui->imgFrameFour_2->setMoveHeight(ui->imgFrameFour_4->getMoveHeight());
                ui->imgFrameFour_3->setMoveWidth(ui->imgFrameFour_4->getMoveWidth());
                ui->imgFrameFour_3->setMoveHeight(ui->imgFrameFour_4->getMoveHeight());
            }
        }
    }
}



