#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                QMainWindow(parent),ui(new Ui::MainWindow)
{
		ui->setupUi(this);
}

MainWindow::~MainWindow()
{
		delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
	default:
			break;
	}
}

void MainWindow::on_screenShotButton_clicked()
{
	if(ui->hideCheckBox->isChecked()) //判断当前的复选框是否被选中， 如果选中
	{
		//this->hide(); //窗口隐藏
		this->counter=0;
		this->timer=new QTimer; //设置定时器
		QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(shotScreen()));
		this->timer->start(150);
		//使用spinbox 获得当前延时的时间
	}
	else
	{
		qApp->beep(); //如果没有选择复选框， 那么发出蜂鸣声
	}
}

void MainWindow::shotScreen()
{

	this->pixmap=QPixmap::grabWindow(QApplication::desktop()->winId(),0,0,1000,600);
        //通过使用grapWindow 来获得整个屏幕的图片， 并赋给pixmap

	ui->screenLabel->setPixmap(this->pixmap.scaled(ui->screenLabel->size()));
	QString format =".png";
	//QString fileName=QFileDialog::getSaveFileName(this,"Save Picture",QDir::currentPath());
	//通过文件对话框来获得保存的路径与名称。
	// QString fileName=QDateTime::currentDateTime().toString("hh:mm:ss");
	this->counter++;
	QString fileName = QString::number(this->counter);
	qDebug()<<fileName;
	fileName.append(format); //fileName=fileName+format;
	qDebug()<<fileName;
	bool ok= this->pixmap.save(fileName);
	if(ok)
		qDebug()<<"save success";
	//使用label 的setPixmap 来设置图片， 大小是使用scaled 缩放到当前label 标签的大小
	//this->timer->stop(); //结束定时器
	//this->show(); //主窗口显示出来

}

void MainWindow::on_saveButton_clicked()
{
		QString format =".jpg";
		//QString fileName=QFileDialog::getSaveFileName(this,"Save Picture",QDir::currentPath());
		//通过文件对话框来获得保存的路径与名称。
		QString fileName=QDateTime::currentDateTime().toString();
		//fileName.append(format); //fileName=fileName+format;
		this->pixmap.save(fileName,format.toAscii());
		//调用 save 方法保存当前图片到指定路径
}

QMediaPlayer *mPlayer;

QVideoProbe *mVideoProbe;

 

void Test::slotGrabMediaScreenFFMPEG()

{

    connect(mVideoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(slotProcessFrameFFMPEG(QVideoFrame)));    

}

 

void Test::slotProcessFrameFFMPEG(const QVideoFrame & buffer)

{

    disconnect(mVideoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(slotProcessFrameFFMPEG(QVideoFrame)));

    if(!buffer.isValid()) // 数据是否有效

    {

        cout<<"frame is invalid"<<endl;

        connect(mVideoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(slotProcessFrame(QVideoFrame)));

        return;

    }

 

    QImage img;

    QVideoFrame frame(buffer); // 拷贝数据

    frame.map(QAbstractVideoBuffer::ReadOnly); // 将视频缓存映射到内存中

 

    int totalBytes = frame.width() * frame.height() * 3;

    uchar *imageBuffer = (uchar*)malloc(totalBytes);

    if(!YV12ToARGB24_FFmpeg(frame.bits(), imageBuffer, frame.width(), frame.height()))

    {

        cout<<"convert YUV to RGB failed"<<endl;

        return;

    }

 

    img = QImage(imageBuffer, frame.width(), frame.height(), //frame.bytesPerLine(),

        //imageFormat);

        QImage::Format_RGB888);

 

    QString filePathName = "convert-vedio-";

    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");

    filePathName += ".png";

    if(!img.save(filePathName,"png"))

    {

        cout<<"save convert vedio screen failed"<<endl;

    }

}

 

 

bool Test::YV12ToARGB24_FFmpeg(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)

{    

    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)

        return false;

    AVPicture pFrameYUV, pFrameBGR;

    avpicture_fill(&pFrameYUV, pYUV, PIX_FMT_NV12, width, height);

    avpicture_fill(&pFrameBGR, pBGR24, AV_PIX_FMT_RGB24, width,height);

 

    struct SwsContext* imgCtx = NULL;

    imgCtx = sws_getContext(width, height, PIX_FMT_NV12, width, height, AV_PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);

    if (imgCtx != NULL){

        sws_scale(imgCtx, pFrameYUV.data, pFrameYUV.linesize, 0, height, pFrameBGR.data, pFrameBGR.linesize);

        if(imgCtx){

            sws_freeContext(imgCtx);

            imgCtx = NULL;

        }

        return true;

    }

    else{

        sws_freeContext(imgCtx);

        imgCtx = NULL;

        return false;

    }

}