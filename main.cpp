#include <QApplication>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include "gstreamerplayer.h"
#include <QDebug>

GST_PLUGIN_STATIC_DECLARE(QGC_VIDEOSINK_PLUGIN);

static void gstputenv(const QString& key, const QString& root, const QString& path)
{
    QString value = root + path;
    qputenv(key.toStdString().c_str(), QByteArray(value.toStdString().c_str()));
}


int main(int argc, char *argv[]) {

    QApplication app(argc,argv);
    QString currentDir = QCoreApplication::applicationDirPath();
    gstputenv("GST_PLUGIN_PATH", currentDir, "/gstreamer-plugins");  // register gstreamer-plugins
    qDebug()<<"currentDir:"<<currentDir<<endl;
    gst_init (&argc, &argv);
    GstreamerPlayer *gplayer = new GstreamerPlayer();
    gplayer->show();
    return app.exec();
}
