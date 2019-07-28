#ifndef GSTCONFIG_H
#define GSTCONFIG_H
#include <QString>
const int WIN_WIDTH = 600;
const int WIN_HEIGTH = 500;

const int STRETCH_50 = 50;
const int STRETCH_100 = 100;
const QString PLAY_FILTER = "*.mp4 *.mov *.mkv *.avi *.rmvb *.rm *.flv";
//rmvb、rm、FLV、mp4、3GP
#endif // GSTCONFIG_H
/*
 * https://www.cnblogs.com/huty/p/8517018.html
 * v4l2src -> ffmpegcolorspace ->tee -> queue1 -> ximagesink

                                  |--->queue2->videorate->video_filter->x264enc-> avimux -> filesink
gst_element_factory_make（）创建
g_object_set(G_OBJECT(v4l2src),"device", device_filename, NULL);
g_object_set(G_OBJECT(filesink),"location", video_filename, NULL);
GstPad *tee_pad =gst_element_get_request_pad (tee, "src%d");
GstPad *sink_pad =gst_element_get_static_pad (queue1, "sink");
gst_pad_link (tee_pad, sink_pad);

g_object_set(G_OBJECT (queue1),"max-size-buffers", 0, NULL);
g_object_set(G_OBJECT(queue1), "max-size-time", 0, NULL);
g_object_set(G_OBJECT(queue1), "max-size-bytes", 512000000, NULL);
gst_element_set_state(pipeline,GST_STATE_PLAYING);
gst_x_overlay_set_xwindow_id(GST_X_OVERLAY(videosink), m_winID);

 */
