#include "../include/SoundManager.h"
#include <QUrl>

SoundManager::SoundManager() {
    player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);
}

void SoundManager::loadMusic(const QString &filePath) {
    qDebug() << "Loading music from:" << filePath; // Debug output
    player->setSource(QUrl::fromLocalFile(filePath));
    audioOutput->setVolume(50);
}

void SoundManager::playMusic() {
    player->play();
}

void SoundManager::stopMusic() {
    player->stop();
}

void SoundManager::pauseMusic() {
    player->pause();
}
