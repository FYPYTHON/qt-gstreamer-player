#include <QDebug>
#include <gstopencv/goimage.h>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QDebug>

int testop() {

    Mat img = imread((":/images/img/photo.png"));
    qDebug()<<"opencv:"<<img.rows<<","<<img.cols<<"\n"<<endl;

//    cv::imshow("test", img);
    cvtColor(img, img, COLOR_BGR2RGB);
    QImage disImage = QImage((const unsigned char*)(img.data), img.cols, img.rows, QImage::Format_RGB888);
    QLabel * limg = new QLabel();
    limg->resize(100,100);
    limg->setPixmap(QPixmap::fromImage(disImage.scaled(limg->size(), Qt::KeepAspectRatio)));


//    waitKey(10000);
    return 0;

}
