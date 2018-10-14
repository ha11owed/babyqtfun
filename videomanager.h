#pragma once

#include <QObject>
#include <QMediaPlaylist>

class VideoManager : public QObject
{
    Q_OBJECT

public:
    QMediaPlaylist* playlist();

    void setVideoDirectory(const QString &dir);

private:
    QMediaPlaylist _playlist;
};
