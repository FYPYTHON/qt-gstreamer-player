#include "gstreamerplayer.h"
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

GstreamerPlayer::GstreamerPlayer(QWidget *parent):QWidget(parent)
{
    setupUI();
    position = -1;
    duration = GST_CLOCK_TIME_NONE;
    this->setWindowTitle(tr("My Gstream Player"));
    this->resize(800,600);

    connect(&_timer,&QTimer::timeout,this,&GstreamerPlayer::timeout);






}
GstreamerPlayer::~GstreamerPlayer()
{
    if (_videoWidget){
        delete _videoWidget;
        _videoWidget = NULL;
    }
}
void GstreamerPlayer::setupUI()
{
    _hlayout = new QHBoxLayout();
    _vlayout = new QVBoxLayout();
    _videoWidget = new QVideoWidget(this);
    _videoWidget->setBackgroundRole(QPalette::Dark);

    this->setWindowTitle(tr("My Gstream Player"));
    _openfile = new QPushButton();
    _openfile->setText(tr("Open File To Play"));
    connect(_openfile,SIGNAL(clicked()),this,SLOT(onOpenfile()));

    _btnPlay = new QPushButton();
    _btnPlay->setText(tr("play"));
    _btnPause = new QPushButton();
    _btnPause->setText(tr("pause"));
    _btnStop = new QPushButton();
    _btnStop->setText(tr("stop"));
    _hlayout->addWidget(_btnPlay);
    _hlayout->addWidget(_btnPause);
    _hlayout->addWidget(_btnStop);
    _hlayout->addSpacing(500);
    connect(_btnPlay,SIGNAL(clicked()),this,SLOT(play()));
    connect(_btnPause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(_btnStop,SIGNAL(clicked()),this,SLOT(stop()));

    _slider = new QSlider(Qt::Horizontal);
//    _slider->setRange(0,100);

//    connect(_slider,SIGNAL(valueChanged(int)),this,SLOT(sliderRange(int)));
    connect(_slider,SIGNAL(sliderPressed()),this,SLOT(seek()));
    connect(_slider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));


    _timeLabel = new QLabel("00:00:00");


//    _videoWidget->setGeometry(0,100,600,500);


    _vlayout->addWidget(_openfile);
    _vlayout->addWidget(_videoWidget);
    _vlayout->addWidget(_timeLabel);
    _vlayout->addWidget(_slider);
    _vlayout->addLayout(_hlayout);
    _vlayout->setStretchFactor(_videoWidget,6);
    _vlayout->setStretchFactor(_openfile,1);
    _vlayout->setStretchFactor(_timeLabel,1);
    _vlayout->setStretchFactor(_slider,1);
    _vlayout->setStretchFactor(_hlayout,1);




    this->setLayout(_vlayout);
}
void GstreamerPlayer::onOpenfile()
{
    ready();
    duration = GST_CLOCK_TIME_NONE;
//    filename = QFileDialog::getOpenFileName(this,tr("open a video file"),".",
//                                            "*.mp4 *.mov *.mkv");
//    if(filename.length()==0){
//        qWarning("filename:%s",filename.toStdString().c_str());
//        QMessageBox::warning(this, tr("File open error"), tr("You selected ") + filename);
//    }else{
//        qWarning("filename is :%s",filename.toStdString().c_str());
//        int ret=0;
//        ret = this->ready();
//        if(ret<0){
//            QMessageBox::warning(this, tr("File play error"), tr("You selected ") + filename);
//        }
//    }
}
int GstreamerPlayer::ready()
{
      /* Build the pipeline */
      filename = "C:/workspace/Qt/testcode/gstreamtest/Video/2018-07-31_13.50.46.mov";
      pipeline = gst_element_factory_make ("playbin", "playbin");
      QString uri = "file:///" + filename;
      qDebug()<<"uri is :"<<uri;
      g_object_set (pipeline, "uri", uri.toStdString().c_str(), NULL);
      guintptr hint = _videoWidget->winId();
      qDebug()<<hint<<endl;
      gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY (pipeline), hint);

      /* Create the elements inside the sink bin */
//      equalizer = gst_element_factory_make ("equalizer-3bands", "equalizer");
//      convert = gst_element_factory_make ("audioconvert", "convert");
//      sink = gst_element_factory_make ("autoaudiosink", "audio_sink");
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
//      msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

//      do {
//          msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

//          /* Parse message */
//          if (msg != NULL) {
//            GError *err;
//            gchar *debug_info;

//            switch (GST_MESSAGE_TYPE (msg)) {
//              case GST_MESSAGE_ERROR:
//                gst_message_parse_error (msg, &err, &debug_info);
//                g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
//                g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
//                g_clear_error (&err);
//                g_free (debug_info);
//                terminate = TRUE;
//                break;
//              case GST_MESSAGE_EOS:
//                g_print ("End-Of-Stream reached.\n");
//                terminate = TRUE;
//                break;
//              case GST_MESSAGE_STATE_CHANGED:
//                /* We are only interested in state-changed messages from the pipeline */
//                if (GST_MESSAGE_SRC (msg) == GST_OBJECT (pipeline)) {
//                  GstState old_state, new_state, pending_state;
//                  gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
//                  g_print ("Pipeline state changed from %s to %s:\n",
//                      gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
//                }
//                break;
//              default:
//                /* We should not reach here */
//                g_printerr ("Unexpected message received.\n");
//                break;
//            }
//            gst_message_unref (msg);
//          }
//        } while (!terminate);
      /* Free resources */

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
        gst_element_set_state(pipeline,GST_STATE_PLAYING);
    }

}
void GstreamerPlayer::pause()
{
    if(pipeline)
    {
        qDebug()<<"pause clicked.";
        _slider->setValue(1);
        gst_element_set_state(pipeline,GST_STATE_PAUSED);
    }

}
void GstreamerPlayer::stop()
{
    if(pipeline)
    {
        qDebug()<<"stop clicked.";
        gst_element_set_state(pipeline,GST_STATE_NULL);
        state = FALSE;
        position = -1;
        duration = GST_CLOCK_TIME_NONE;
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
              _slider->setRange(0,duration/1000000000);
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

        qDebug()<<"label:"<<time<<"curtime:"<<times<<endl;
    }
    else {
        time = tr("00:00:00");
        _timeLabel->setText(time);
    }

}
void GstreamerPlayer::timeout()
{
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
              _slider->setRange(0,duration/1000000000);
//              _slider->setSingleStep(1);
              qDebug()<< "set slider range: 0"<<duration/1000000000<<endl;
          }
    }
    if(fabs(duration-position)<0.01){
        state = FALSE;
        position = -1;
        duration = GST_CLOCK_TIME_NONE;
        _timer.stop();

    }
    else{
        state = TRUE;
    }
    qDebug()<<"times going"<<position/1000000000<<endl;
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
               int pos = _slider->minimum() + dur * ((double)mouseEvent->x() / _slider->width());
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
