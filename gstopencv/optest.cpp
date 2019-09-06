#include <QDebug>
#include <gstopencv/goimage.h>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QDebug>

OpencvImage::OpencvImage(QWidget *parent):QWidget(parent)
{
    resize(200,200);
    limg = new QLabel(this);
    testop();
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
