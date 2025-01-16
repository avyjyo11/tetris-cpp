#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class SoundManager {
    Q_SLOTS
public:
    SoundManager();
    void loadMusic(const QString &filePath);
    void playMusic();
    void stopMusic();
    void pauseMusic();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // SOUNDMANAGER_H
