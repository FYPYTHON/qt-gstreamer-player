#include "mainwidget.h"


MainWiget::MainWiget(QWidget *parent):QWidget(parent)
{
    gplayer = nullptr;
    cvimage = nullptr;
    this->resize(200,200);
    setupUI();
}
MainWiget::~MainWiget()
{
    if(gplayer){
        delete gplayer;
    }
    if(cvimage){
        delete cvimage;
    }

}
void MainWiget::setupUI()
{
    _vlayout = new QVBoxLayout(this);
    _btnimage = new QPushButton(this);
    _btnimage->setText(tr("Image"));
    connect(_btnimage,SIGNAL(clicked()), this, SLOT(showMImage()));
    _btnvideo = new QPushButton(this);
    _btnvideo->setText(tr("Video"));
    connect(_btnvideo,SIGNAL(clicked()), this, SLOT(showMVideo()));
    _vlayout->addStretch(100);
    _vlayout->addWidget(_btnimage);
    _vlayout->addStretch(20);
    _vlayout->addWidget(_btnvideo);
    _vlayout->addStretch(100);
    this->setLayout(_vlayout);
}
void MainWiget::showMImage()
{
    this->hide();
    if(nullptr == cvimage)
    {
        cvimage = new OpencvImage();
        connect(cvimage, &OpencvImage::homeSignal, this, &MainWiget::showHome);
    }
    cvimage->show();

}
void MainWiget::showMVideo()
{
    this->hide();
    if (nullptr == gplayer)
    {
        gplayer = new GstreamerPlayer();
        connect(gplayer, &GstreamerPlayer::homeSignal, this, &MainWiget::showHome);
    }
    gplayer->show();

}
void MainWiget::showHome()
{
    if (nullptr != gplayer)
        gplayer->hide();
    if (nullptr != cvimage)
        cvimage->hide();
    this->show();


}
