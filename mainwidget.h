#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "gstreamerplayer.h"
#include "gstopencv/goimage.h"

class MainWiget:public QWidget
{
    Q_OBJECT
public:
    MainWiget(QWidget *parent=nullptr);
    ~MainWiget();
    void setupUI();
signals:
    void homeSignal();
private slots:
    void showMImage();
    void showMVideo();
    void showHome();


private:
    QPushButton*   _btnimage;
    QPushButton*   _btnvideo;
    QVBoxLayout*   _vlayout;

    GstreamerPlayer *gplayer;
    OpencvImage     *cvimage;

};
#endif // MAINWIDGET_H
