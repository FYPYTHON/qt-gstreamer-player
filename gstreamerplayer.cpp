#include "gstreamerplayer.h"
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
const int DURATION_UNIT = 1000000000;
const int XINI = 35;
const int YINI = 20;
const int XSTEP = 80;
const int YSTEP = 84;
const int XWIDTH = 50;
const int YHEIGHT = 50;

static QPixmap get_copy(int x,int y, QPixmap *pix)
{
//    return pix->copy(XINI + XSTEP * x,
//                         YINI + YSTEP * y,
//                         XWIDTH, YHEIGHT).scaled(
//                         btn->width(),
//                         btn->height()).scaled(
//                btn->width(), btn->height());
    return pix->copy(XINI + XSTEP * x,
                         YINI + YSTEP * y,
                         XWIDTH, YHEIGHT);

}

GstreamerPlayer::GstreamerPlayer(QWidget *parent):QWidget(parent)
{
    _fileListWidget = nullptr;

    _allico = new QPixmap(":/images/img/allico.jpg");
    this->setWindowIcon(QIcon(":/images/img/logo0.png"));
    setupUI();
    position = -1;
    duration = -1;  // GST_CLOCK_TIME_NONE;
    rate = 1.0;
    this->setWindowTitle(tr("My Gstream Player"));
    this->resize(WIN_WIDTH,WIN_HEIGTH);

    connect(&_timer,&QTimer::timeout,this,&GstreamerPlayer::timeout);

}
GstreamerPlayer::~GstreamerPlayer()
{
    if (_videoWidget){
        delete _videoWidget;
        _videoWidget = nullptr;
    }
}
void GstreamerPlayer::setupUI()
{
    _all_lay_out = new QHBoxLayout();
    _hlayout = new QHBoxLayout();
    _file_layout = new QHBoxLayout();
    _vlayout = new QVBoxLayout();
    _videoWidget = new QVideoWidget(this);
    _videoWidget->setBackgroundRole(QPalette::Dark);

    this->setWindowTitle(tr("My Gstream Player"));

    _openfile = new QPushButton();
    _openfile->setText(tr("Open File To Play"));
    connect(_openfile,SIGNAL(clicked()),this,SLOT(onOpenfile()));
    _file_layout->addWidget(_openfile);
    _file_layout->addSpacing(500);

    _btnPlay = new QPushButton();
//    _btnPlay->setText(tr("play"));
    _btnPlay->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 101 105 269 445;}");
//    _btnPlay->resize(50,50);
//    QIcon icon_play = QIcon(get_copy(5,1,_allico));

    _btnPause = new QPushButton();
//    _btnPause->setText(tr("pause"));
    _btnPause->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 182 105 188 445;}");

    _btnStop = new QPushButton();
//    _btnStop->setText(tr("stop"));
    _btnStop->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 263 105 107 445;}");

    _btnQuick = new QPushButton();
//    _btnQuick->setText(tr("quick"));
    _btnQuick->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 344 188 26 362;}");

    _rate_label = new QLabel(tr("x1"));
    _btnOpen = new QPushButton(tr("open"));
    QIcon icon_open = QIcon(":/images/img/logo0.png");
    _btnOpen->setIcon(icon_open);
    connect(_btnOpen,SIGNAL(clicked()),this,SLOT(showFileWidget()));
    _hlayout->addSpacing(150);
    _hlayout->addWidget(_btnPlay);
    _hlayout->addWidget(_btnPause);
    _hlayout->addWidget(_btnStop);
    _hlayout->addWidget(_btnQuick);
    _hlayout->addWidget(_rate_label);
    _hlayout->addSpacing(150);
    _hlayout->addWidget(_btnOpen);
//    _hlayout->setStretchFactor(_btnPlay,2);
//    _hlayout->setStretchFactor(_btnPause,2);
//    _hlayout->setStretchFactor(_btnStop,2);
//    _hlayout->setStretchFactor(_btnQuick,2);
//    _hlayout->setStretchFactor(_rate_label,1);
//    _hlayout->setStretch(0,5);
//    _hlayout->setStretch(1,10);
//    _hlayout->setStretch(5,100);
//    _hlayout->setStretchFactor(_btnOpen,2);
    connect(_btnPlay,SIGNAL(clicked()),this,SLOT(play()));
    connect(_btnPause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(_btnStop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(_btnQuick,SIGNAL(clicked()),this,SLOT(quick()));


    _slider = new QSlider(Qt::Horizontal);

//    connect(_slider,SIGNAL(valueChanged(int)),this,SLOT(sliderRange(int)));
    connect(_slider,SIGNAL(sliderPressed()),this,SLOT(seek()));
    connect(_slider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));

    _filename_label = new QLabel("未选择");
    _filename_hlayout = new QHBoxLayout();
    _filename_hlayout->addStretch(50);
    _filename_hlayout->addWidget(_filename_label);
    _filename_hlayout->addStretch(50);
    _filename_label->setGeometry(_videoWidget->pos().x()-(_videoWidget->width()/2),_videoWidget->pos().y(),100,50);

    connect(this,SIGNAL(filenameChanged(QString)),this,SLOT(onFilenameChanged(QString)));
    _timeLabel = new QLabel("00:00:00");


    _vlayout->addLayout(_file_layout);
//    _vlayout->addWidget(_filename_label, 300);
    _vlayout->addLayout(_filename_hlayout);
    _vlayout->addWidget(_videoWidget);
    _vlayout->addWidget(_timeLabel);
    _vlayout->addWidget(_slider);
    _vlayout->addLayout(_hlayout);
    _vlayout->setStretchFactor(_videoWidget,6);
    _vlayout->setStretchFactor(_openfile,1);
    _vlayout->setStretchFactor(_filename_label,1);
    _vlayout->setStretchFactor(_timeLabel,1);
    _vlayout->setStretchFactor(_slider,1);
    _vlayout->setStretchFactor(_hlayout,2);

    _all_lay_out->addLayout(_vlayout);
    _fileListWidget = new QWidget();
    _fileListWidget->hide();
    _inputPath = new QLineEdit(_fileListWidget);
    _inputPath->setGeometry(0,10,200, 30);
    _btnDir = new QPushButton(_fileListWidget);
//    _btnDir->setText(tr("file list"));
    _btnDir->setGeometry(0,50,30,30);
    _btnDir->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 182 520 188 30;}");

    _btnClearDir = new QPushButton(_fileListWidget);
    _btnClearDir->setGeometry(40,50,30,30);
    _btnClearDir->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 101 520 269 30;}");

    _fileListW = new QListWidget(_fileListWidget);
    _fileListW->setGeometry(0, 100, 200, 400);
    _fileListW->addItem("1");
    _fileListW->addItem("2");
    _fileListW->addItem("3");
    _fileListW->addItem("4");

//    QLabel *lbl = new QLabel(_fileListWidget);
//    lbl->setPixmap(get_copy(1,1,_allico));
//    QPushButton *qbn = new QPushButton(_fileListWidget);
//    qbn->setGeometry(0, 0, 50, 50);
//    qbn->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 101 437 269 113;}");
//    qbn->resize(100,100);

//    QPushButton *qbn2 = new QPushButton(_fileListWidget);
//    qbn2->setText("test");
//    qbn2->setGeometry(0, 110, 50, 50);
//    qbn2->setStyleSheet("QPushButton{border-image:url(:/images/img/allico.jpg) 344 188 26 362;}");
//    qbn2->resize(30,30);

    _fileListWidget->resize(this->width()/4, this->height());
    _all_lay_out->addWidget(_fileListWidget);

//    this->setLayout(_vlayout);
    _all_lay_out->setStretchFactor(_vlayout, 1);
    _all_lay_out->setStretchFactor(_fileListWidget, 1);
    this->setLayout(_all_lay_out);
}
void GstreamerPlayer::showFileWidget()
{
    if(nullptr == _fileListWidget){
        _fileListWidget = new QWidget(this);
    }
//    _fileListWidget->setGeometry(0,0,50,50);
    if (_fileListWidget->isHidden())
    {
       _fileListWidget->show();
       this->resize(WIN_WIDTH + _fileListW->width(), WIN_HEIGTH);

    }
    else {
       _fileListWidget->hide();
       this->resize(WIN_WIDTH,WIN_HEIGTH);
    }

}
void GstreamerPlayer::onOpenfile()
{
//    ready();
    duration = -1;

    // open file to play
    filename = QFileDialog::getOpenFileName(this,tr("open a video file"),"E:/",
                                            "*.mp4 *.mov *.mkv");
    if(filename.length()==0){
        qWarning("filename:%s",filename.toStdString().c_str());
        QMessageBox::warning(this, tr("File open error"), tr("You selected none ") + filename);
    }else{
        qWarning("filename is :%s",filename.toStdString().c_str());
        int ret=0;
        ret = this->ready();
        emit filenameChanged(filename);
        if(ret<0){
            QMessageBox::warning(this, tr("File play error"), tr("You selected ") + filename);
        }
    }
}
void GstreamerPlayer::onFilenameChanged(QString filename)
{
    qDebug()<<"filename changed send is :"<<sender();
    _filename_label->setText(filename);

}
int GstreamerPlayer::ready()
{
      /* Build the pipeline */
//      sink = gst_element_factory_make ("qtquick2videosink", "audio_sink");
//      sink = gst_element_factory_make ("autovideosink", "sink");
//      g_object_set(pipeline,"video-sink",sink,NULL);
      pipeline = gst_element_factory_make ("playbin", "playbin");
      QString uri = "file:///" + filename;
      qDebug()<<"uri is :"<<uri;
      g_object_set (pipeline, "uri", uri.toStdString().c_str(), NULL);
      guintptr hint = _videoWidget->winId();
      qDebug()<<hint<<endl;
      gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(pipeline), hint);

      /* Create the elements inside the sink bin */
//      equalizer = gst_element_factory_make ("equalizer-3bands", "equalizer");
//      convert = gst_element_factory_make ("audioconvert", "convert");
//      sink = gst_element_factory_make ("qtquick2videosink", "audio_sink");
//      if (!equalizer || !convert || !sink) {
//        g_printerr ("Not all elements could be created.\n");
//        return -1;
//      }

      /* Create the sink bin, add the elements and link them */
//      bin = gst_bin_new ("audio_sink_bin");
//      gst_bin_add_many (GST_BIN (bin), equalizer, convert, sink, NULL);
//      if(!gst_element_link_many (equalizer, convert, sink, NULL))
//      {
//          qDebug()<<"link error!"<<endl;

//      }
//      pad = gst_element_get_static_pad (equalizer, "sink");
//      ghost_pad = gst_ghost_pad_new ("sink", pad);
//      gst_pad_set_active (ghost_pad, TRUE);
//      gst_element_add_pad (bin, ghost_pad);
//      gst_object_unref (pad);

      /* Configure the equalizer */
//      g_object_set (G_OBJECT (equalizer), "band1", (gdouble)-24.0, NULL);
//      g_object_set (G_OBJECT (equalizer), "band2", (gdouble)-24.0, NULL);

      /* Set playbin's audio sink to be our sink bin */
//      g_object_set (GST_OBJECT (pipeline), "audio-sink", bin, NULL);

      /* Start playing */
      if(!gst_element_set_state (pipeline, GST_STATE_PLAYING))
      {
          qDebug()<<"set state playing error"<<endl;

      }

      /* Wait until error or EOS */
      bus = gst_element_get_bus (pipeline);

//      gst_object_unref (bus);
//      gst_element_set_state (pipeline, GST_STATE_NULL);
//      gst_object_unref (pipeline);
      setTimeLabel();
      _timer.start(1000);
      return 0;
}
void GstreamerPlayer::play()
{
    if(pipeline)
    {
//        ready();
        qDebug()<<"play clicked.";
        if(!_timer.isActive()){
            _timer.start(1000);
        }

        gst_element_set_state(pipeline,GST_STATE_PLAYING);
    }

}
void GstreamerPlayer::pause()
{
    if(pipeline)
    {
        qDebug()<<"pause clicked."<<position/DURATION_UNIT;
//        _slider->setValue(1);
        _timer.stop();
        gst_element_set_state(pipeline,GST_STATE_PAUSED);
    }

}
void GstreamerPlayer::stop()
{
    if(pipeline)
    {
        qDebug()<<"stop clicked."<<position/DURATION_UNIT;
        gst_element_set_state(pipeline,GST_STATE_NULL);
        state = FALSE;
        position = -1;
        duration = -1;
        _timer.stop();
    }

}
void GstreamerPlayer::seek()
{
    _timer.stop();
    pause();
    int pos = _slider->value();
    qDebug()<<"pressed seek "<<pos<<endl;
//    gst_element_seek_simple (pipeline, GST_FORMAT_TIME, static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT),
//          (gint64)(pos * GST_SECOND));
//    position = qint64(pos);
//    _timer.start();

}
void GstreamerPlayer::seek(int pos)
{
    _timer.stop();
//    int pos = _slider->value();
    qDebug()<<"move seek "<<pos<<endl;
    if(filename.length()>0){
        gst_element_seek_simple (pipeline, GST_FORMAT_TIME, static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT),
              (gint64)(pos * GST_SECOND));
    }
    position = qint64(pos);
    _timer.start();

}
void GstreamerPlayer::sliderRange(int value)
{
    qWarning("value:%d",value);
//    _slider->setValue(value);


//    if(!gst_element_query_position(pipeline,GST_FORMAT_TIME,&position))
//    {
//        qDebug()<<"Could not query position.\n";
//    }

    if (!GST_CLOCK_TIME_IS_VALID (duration))
    {
          if (!gst_element_query_duration (pipeline, GST_FORMAT_TIME, &duration)) {
            qDebug()<< ("Could not query current duration.\n");
          }
          else {
              _slider->setRange(0,int(duration/DURATION_UNIT));
//              _slider->setSingleStep(1);
              qDebug()<< "set slider range"<<endl;
          }
    }
    qDebug()<<"positon"<<position<<","
            <<"duration"<<duration<<endl;
//    gst_element_seek_simple (pipeline, GST_FORMAT_TIME, static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT),
//          (gint64)(value * GST_SECOND));
//    setTimeLabel();


}
void GstreamerPlayer::setTimeLabel()
{
    QString time;
    if(position){

        double times = position/1000000000;
        int hour = times/3600;
        int mintus = (times-hour*3600) / 60;
        double second = times - hour*3600 - mintus*60;
        time = QString("%1:%2:%3").arg(hour).arg(mintus).arg(second);
        _timeLabel->setText(time);
        _slider->setValue(times);

//        qDebug()<<"label:"<<time<<"curtime:"<<times<<endl;
    }
    else {
        time = tr("00:00:00");
        _timeLabel->setText(time);
    }

}
void GstreamerPlayer::timeout()
{
    // get current position when playing state
    if(!gst_element_query_position(pipeline,GST_FORMAT_TIME,&position))
    {
        qDebug()<<"Could not query position.\n";
    }
    if (!GST_CLOCK_TIME_IS_VALID (duration))
    {
          if (!gst_element_query_duration (pipeline, GST_FORMAT_TIME, &duration)) {
            qDebug()<< ("Could not query current duration.\n");
          }
          else {
              _slider->setRange(0,int(duration/1000000000));
//              _slider->setSingleStep(1);
              qDebug()<< "set slider range: 0"<<duration/1000000000<<endl;
          }
    }
    // if play is over set state disable
    if(fabs(duration-position)<0.01){
        state = FALSE;
        position = -1;
        duration = -1;
        _timer.stop();

    }
    else{
        state = TRUE;
    }
//    qDebug()<<"times going"<<position/1000000000<<endl;
    setTimeLabel();

}
bool GstreamerPlayer::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_slider)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
               int dur = _slider->maximum() - _slider->minimum();
               int pos = _slider->minimum() + dur * static_cast<int>((double)mouseEvent->x() / _slider->width());
               if(pos != _slider->sliderPosition())
                {
                   qDebug()<<"event filter:"<<pos<<endl;
                  _slider->setValue(pos);
                }
            }
        }
    }
    return QObject::eventFilter(obj,event);
}
void GstreamerPlayer::send_seek_event(gdouble rate)
{
    GstFormat format = GST_FORMAT_TIME;
    GstEvent *seek_event;

      /* Obtain the current position, needed for the seek event */
    if (!gst_element_query_position (pipeline, format, &position)) {
        g_printerr ("Unable to retrieve current position.\n");
        return;
    }

      /* Create the seek event */
    if (rate > 0) {
       seek_event = gst_event_new_seek (rate, GST_FORMAT_TIME, static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE),
           GST_SEEK_TYPE_SET, position, GST_SEEK_TYPE_NONE, 0);
    } else {
        seek_event = gst_event_new_seek (rate, GST_FORMAT_TIME, static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE),
            GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_SET, position);
      }

      if (sink == nullptr) {
        /* If we have not done so, obtain the sink through which we will send the seek events */
        g_object_get (pipeline, "video-sink", sink, NULL);
      }

      /* Send the event */
      gst_element_send_event (pipeline, seek_event);

      g_print ("Current rate: %g\n", rate);
}
void GstreamerPlayer::quick()
{
    if(rate >=31.99)
    {
        rate = 1.0;
    }else{
        rate *= 2;
    }

//    qDebug()<<"quick clicked;"<<rate;
    _rate_label->setText(QString("x%1").arg(int(rate)));
    send_seek_event(rate);
}
