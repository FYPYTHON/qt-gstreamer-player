#ifndef GSTREAMERPLAYER_H
#define GSTREAMERPLAYER_H
#include <gst/gst.h>
#include <QWidget>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
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
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    GstElement *pipeline, *bin, *equalizer, *convert, *sink;
    GstPad *pad, *ghost_pad;
    GstBus *bus;
    GstMessage *msg;
    gboolean terminate = FALSE;
    gboolean state = FALSE;
    qint64 duration;
    qint64 position;
    gdouble rate;
    QString filename;
    QTimer _timer;
    QVideoWidget* _videoWidget;
    QVBoxLayout*  _vlayout;
    QHBoxLayout*  _hlayout;
    QHBoxLayout*  _file_layout;
    QHBoxLayout*  _filename_hlayout;
    QPushButton*  _btnPlay;
    QPushButton*  _btnPause;
    QPushButton*  _btnStop;
    QPushButton*  _btnQuick;
    QPushButton*  _openfile;
    QSlider*      _slider;
    QLabel*       _timeLabel;
    QLabel*       _filename_label;
    QLabel*       _rate_label;
    QWidget*      _myWidget;


};

#endif // GSTREAMERPLAYER_H
