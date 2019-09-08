#include <QDebug>
#include <gstopencv/goimage.h>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

OpencvImage::OpencvImage(QWidget *parent):QWidget(parent)
{
    resize(WIN_WIDTH, WIN_HEIGTH);
    setupUI();
//    testop();
//    this->setLayout(limg);
}
OpencvImage::~OpencvImage()
{

}
int OpencvImage::testop() {


    Mat img = imread(("E:/qtproject/qt-gstreamer-player/img/photo.png"));
    qDebug()<<"opencv:"<<img.rows<<","<<img.cols<<"\n"<<endl;

//    cv::imshow("test", img);
    cvtColor(img, img, COLOR_BGR2RGB);
    QImage disImage = QImage((const unsigned char*)(img.data), img.cols, img.rows, QImage::Format_RGB888);

    limg->resize(this->width(), this->height());
    limg->setPixmap(QPixmap::fromImage(disImage.scaled(limg->size(), Qt::KeepAspectRatio)));


//    waitKey(10000);
    return 0;
}
void OpencvImage::setupUI()
{
    vlayout = new QVBoxLayout();
    hlayout = new QHBoxLayout();
    lfilename = new QLabel(this);
    lfilename->setText(tr("未选择"));
    limg = new QLabel(this);
    limg->resize(WIN_WIDTH,WIN_HEIGTH - 100);
    btnOpen = new QPushButton(this);
    btnOpen->setText(tr("Open"));
    connect(btnOpen, SIGNAL(clicked()), this, SLOT(openImage()));


    hlayout->addStretch(10);
    hlayout->addWidget(btnOpen);
    hlayout->addStretch(2);


    vlayout->addWidget(lfilename,1);
    vlayout->addStretch(10);
    vlayout->addWidget(limg, 8);
    vlayout->addStretch(10);
    vlayout->addLayout(hlayout,1);

    this->setLayout(vlayout);
}
void OpencvImage::openImage()
{
    curImg = QFileDialog::getOpenFileName(this, tr("open a image file"), "E:/project", IMG_FILTER);

    if(curImg.length()==0){
        qWarning("open imgage file: %s",curImg.toStdString().c_str());
        QMessageBox::warning(this, tr("File open error"), tr("You selected none ") + curImg);
    }
    else{
        qWarning("open imgage file: %s",curImg.toStdString().c_str());
//        imread(curImg.toStdString());
//        "E:/project/GitProject/qt-gstreamer-player/img/photo.png"
        lfilename->setText(curImg);
        Mat c_img = imread(curImg.toStdString());
        qDebug()<<"opencv:"<<c_img.rows<<","<<c_img.cols<<"\n"<<endl;

    //    cv::imshow("test", img);
        cvtColor(c_img, c_img, COLOR_BGR2RGB);
        QImage disImage = QImage((const unsigned char*)(c_img.data), c_img.cols, c_img.rows, QImage::Format_RGB888);
        disImage.scaled(WIN_WIDTH - 50, WIN_HEIGTH - 100);
        limg->resize(WIN_WIDTH - 50, WIN_HEIGTH - 100);
//        limg->move(this->width()/2 - limg->width()/2, this->height());
        qDebug()<<limg->x()<<","<<limg->y()<<endl<<this->width()<<","<<this->height();
        limg->setPixmap(QPixmap::fromImage(disImage.scaled(limg->size(), Qt::KeepAspectRatio)));

    }
}
