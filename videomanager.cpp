#include "videomanager.h"

#include <QUrl>
#include <QDirIterator>
#include <QDebug>

QMediaPlaylist *VideoManager::playlist()
{
    return &_playlist;
}

void VideoManager::setVideoDirectory(const QString &dir)
{
    if(dir.length() == 0)
    {
        return;
    }

    _playlist.clear();

    QDirIterator dirIterator(dir,
                             QDir::Files | QDir::Readable,
                             QDirIterator::FollowSymlinks | QDirIterator::Subdirectories);

    QStringList allowedExtensions;
    allowedExtensions.append(".mpg");
    allowedExtensions.append(".mpeg");
    allowedExtensions.append(".mp4");
    allowedExtensions.append(".avi");

    while(dirIterator.hasNext())
    {
        QString path = dirIterator.next();

        bool inList = false;
        for(QString extension : allowedExtensions)
        {
            if(path.endsWith(extension, Qt::CaseInsensitive))
            {
                inList = true;
                break;
            }
        }

        if(!inList)
        {
            break;
        }

        QUrl url = QUrl::fromLocalFile(path);
        bool result = _playlist.addMedia(QMediaContent(url));
        qDebug() << "addMedia(" << url << ") result: " << result;
    }
}

