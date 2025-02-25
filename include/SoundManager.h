#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SoundProcessor.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class SoundManager: public QObject {
    Q_OBJECT
public:
    SoundManager(QMainWindow *parent = nullptr);

    void playMusic();
    void pauseMusic();
    void stopMusic();
    void loadMusic(const QString &filePah);
    
private:
    // Member to hold the audio
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString audioFilePath;
    QMainWindow *parent;
    SoundProcessor *soundProcessor;
};

#endif // SOUNDMANAGER_H
