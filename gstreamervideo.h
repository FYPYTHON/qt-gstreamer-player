#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
#include <QtDebug>
namespace Ui {
		class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();
		long    counter;

	protected:
		void changeEvent(QEvent *e);

	private:
		Ui::MainWindow *ui;
		QTimer *timer;
		QPixmap pixmap;

	private slots:
		void on_saveButton_clicked();
		void on_screenShotButton_clicked();
		void shotScreen();
};

#endif // MAINWINDOW_H