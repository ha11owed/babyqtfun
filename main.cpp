#include <QtGui>
#include <QCommandLineParser>
#include <QtQml/QQmlApplicationEngine>
#include <QTimer>
#include <QQuickWindow>
#include <QQmlContext>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "effectmanager.h"
#include "videomanager.h"

int main(int argc, char **argv)
{
    int retCode = -1;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Must be set in order for the transparent window to work.
    // This operation must be done before creating the window.
    QQuickWindow::setDefaultAlphaBuffer(true);

    VideoManager videoManager;
    EffectManager effectManager;
    engine.load("qrc:///main.qml");

    for (;;)
    {
        int screenIndex = -1;

        QCommandLineParser parser;
        parser.setApplicationDescription("Baby QT keyboard basher for a fun time!");
        parser.addHelpOption();

        QCommandLineOption screenOption(QStringList() << "s" << "screen",
                                        QCoreApplication::translate("main", "The index of the screen to use for displaying the application (relevant for multi-displays)."),
                                        QCoreApplication::translate("main", "screen"));
        QCommandLineOption bubblesOption(QStringList() << "b" << "bubbles",
                                         QCoreApplication::translate("main", "The maximum number of bubbles to display."),
                                         QCoreApplication::translate("main", "bubbles"),
                                         QString::number(30));
        QCommandLineOption zoomOption(QStringList() << "z" << "zoom",
                                         QCoreApplication::translate("main", "The zoom for the bubbles (1.0 means normal zoom)."),
                                         QCoreApplication::translate("main", "zoom"),
                                         QString::number(1.0));
        QCommandLineOption videosOption("video_dir",
                                         QCoreApplication::translate("main", "A directory to load videos from."),
                                         QCoreApplication::translate("main", "video directory path"),
                                         QString(""));

        parser.addOption(screenOption);
        parser.addOption(bubblesOption);
        parser.addOption(zoomOption);
        parser.addOption(videosOption);

        parser.process(app);

        QStringList screenValues = parser.values(screenOption);
        if(screenValues.length() == 1)
        {
            bool ok = true;
            QString screenValue = screenValues.at(0);
            screenIndex = screenValue.toInt(&ok);
            if (!ok)
            {
                qCritical() << "The screen index must be an integer. The value " << screenValue << " is invalid.";
                break;
            }

            int nScreens = QGuiApplication::screens().size();
            if (screenIndex >= nScreens)
            {
                qCritical() << "The screen index is out of range. The available number of screens is" << nScreens;
                break;
            }
        }

        QString bubblesValue = parser.value(bubblesOption);
        {
            bool ok;
            int bubblesCount = bubblesValue.toInt(&ok);
            if (ok)
            {
                effectManager.context()->maxBubbles = bubblesCount;
            }
        }

        QString zoomValue = parser.value(zoomOption);
        {
            bool ok;
            float zoom = zoomValue.toFloat(&ok);
            if (ok)
            {
                effectManager.context()->zoom = zoom;
            }
        }

        QString videosValue = parser.value(videosOption);
        videoManager.setVideoDirectory(videosValue);

        // Init the window
        QQuickWindow* mainWindow = nullptr;
        if (engine.rootObjects().length() == 1)
        {
            QObject* rootObj = engine.rootObjects().at(0);
            mainWindow = qobject_cast<QQuickWindow*>(rootObj);

            if (screenIndex >= 0)
            {
                mainWindow->setScreen(QGuiApplication::screens().at(screenIndex));
                qInfo() << "Selecting screen" << screenIndex;
            }

            mainWindow->setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
            mainWindow->setColor(Qt::transparent);
            mainWindow->setVisible(true);
            mainWindow->setWindowState(Qt::WindowFullScreen);

            // Videos
            if (videoManager.playlist()->mediaCount() > 0)
            {
                QObject* qmlMediaPlayer = mainWindow->findChild<QObject*>("mp");
                QMediaPlayer* mediaPlayer = qvariant_cast<QMediaPlayer*>(qmlMediaPlayer->property("mediaObject"));
                mediaPlayer->setPlaylist(videoManager.playlist());
                mediaPlayer->play();
            }

            // Effects
            effectManager.context()->init(mainWindow, &engine);
            QObject::connect(mainWindow, SIGNAL(qmlSignal(QVariant)),
                             &effectManager, SLOT(cppSlot(QVariant)));

            QTimer *timer = new QTimer(&app);
            QObject::connect(timer, SIGNAL(timeout()),
                             &effectManager, SLOT(tick()));
            timer->start(50);
        }
        else
        {
            qCritical() << "Internal error! Unable to create the main window.";
            break;
        }

        // Everything is ok
        retCode = app.exec();
        break;
    }

    return retCode;
}
