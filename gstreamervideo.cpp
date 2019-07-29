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