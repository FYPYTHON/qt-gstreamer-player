#ifndef GOIMAGE_H
#define GOIMAGE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <gstconfig.h>
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
    void setupUI();
signals:
    void homeSignal();
private slots:
    void openImage();
private:
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QHBoxLayout *homelayout;
    QPushButton *btnOpen;
    QPushButton *_toHome;
    QLabel   *lfilename;
    QLabel   *limg;
    QString curImg;
};

#endif // GOIMAGE_H
