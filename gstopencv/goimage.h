#ifndef GOIMAGE_H
#define GOIMAGE_H
#include <QWidget>
#include <QLabel>
// :/images/img
// E:\opencv4.1.1\opencv\sources\doc\tutorials\images
//#pragma comment( lib, "E:/opencv4.1.1/opencvlib/install/x86/vc15/lib/opencv_world411.lib")
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

class OpencvImage:public QWidget
{
    Q_OBJECT
public:
    OpencvImage(QWidget *parent=nullptr);
    ~OpencvImage();
    int testop();
private:
    QLabel * limg;
};

#endif // GOIMAGE_H
