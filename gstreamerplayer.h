#ifndef GSTREAMERPLAYER_H
#define GSTREAMERPLAYER_H
#include <gst/gst.h>
#include <gstconfig.h>
#include <QWidget>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QBitmap>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfoList>
#include <Filter.h>
class GstreamerPlayer:public QWidget
{
    Q_OBJECT
public:
    GstreamerPlayer(QWidget *parent=nullptr);
    ~GstreamerPlayer();
    void openfile();
    int ready();
    void setupUI();
    void send_seek_event(gdouble rate);
signals:
    void timeTextChanged();
    void filenameChanged(QString);
    void homeSignal();
private slots:
    void play();
    void pause();
    void stop();
    void sliderRange(int);
    void seek();
    void seek(int);
    void onOpenfile();
    void onFilenameChanged(QString);
    void setTimeLabel();
    void timeout();
    void quick();
    void showFileWidget();
    void dirListClear();
    void dirListGet();
    void fillListFromDir(QFileInfoList);
    void singleclicked(QListWidgetItem*);
    void doubleclicked(QListWidgetItem*);
    void grapImage();
    void gstImage();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    GstElement *pipeline, *bin, *equalizer, *convert, *sink;
    GstBuffer *pixbuf;
    GstPad *pad, *ghost_pad;
    GstBus *bus;
    GstMessage *msg;
    gboolean terminate = FALSE;
    gboolean state = FALSE;
    qint64 duration;
    qint64 position;
    gdouble rate;
    QString filename;
    QString curFileDir;
    QTimer _timer;
    QVideoWidget* _videoWidget;
    QVBoxLayout*  _vlayout;
    QHBoxLayout*  _hlayout;
    QHBoxLayout*  _file_layout;
    QHBoxLayout*  _filename_hlayout;
    QHBoxLayout*  _all_lay_out;
    QPixmap*       _allico;
    QPushButton*  _btnPlay;
    QPushButton*  _btnPause;
    QPushButton*  _btnStop;
    QPushButton*  _btnQuick;
    QPushButton*  _openfile;
    QPushButton*  _btnOpen;
    QPushButton*  _btnScreenShot;
    QPushButton*  _home;
    QSlider*      _slider;
    QLabel*       _timeLabel;
    QLabel*       _filename_label;
    QLabel*       _rate_label;
    QWidget*      _myWidget;
    QWidget*      _fileListWidget;
    QLineEdit*    _inputPath;
    QPushButton*  _btnDir;
    QPushButton*  _btnClearDir;
    QListWidget*  _fileListW;


};

#endif // GSTREAMERPLAYER_H
