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
    GstreamerPlayer(QWidget *parent=NULL);
    ~GstreamerPlayer();
    void openfile();
    int ready();
    void setupUI();
signals:
    void timeTextChanged();
private slots:
    void play();
    void pause();
    void stop();
    void sliderRange(int);
    void seek();
    void seek(int);
    void onOpenfile();
    void setTimeLabel();
    void timeout();
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
    QString filename;
    QTimer _timer;
    QVideoWidget* _videoWidget;
    QVBoxLayout*  _vlayout;
    QHBoxLayout*  _hlayout;
    QPushButton*  _btnPlay;
    QPushButton*  _btnPause;
    QPushButton*  _btnStop;
    QPushButton*  _openfile;
    QSlider*      _slider;
    QLabel*       _timeLabel;
    QWidget*      _myWidget;


};

#endif // GSTREAMERPLAYER_H
