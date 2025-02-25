
#include "../include/SoundManager.h"

#include <QMediaPlayer>
#include <QMainWindow>
#include <QAudioOutput>
#include <QString>
#include <QUrl>
#include <sndfile.h>
#include <vector>
#include <iostream>

SoundManager::SoundManager(QMainWindow *parent) : parent(parent), player(new QMediaPlayer(this)), audioOutput(new QAudioOutput(this)) {
    player->setAudioOutput(audioOutput);
    soundProcessor = new SoundProcessor();
};

void SoundManager::loadMusic(const QString &filePath) {
    audioFilePath = filePath;
    player->setSource(QUrl::fromLocalFile(audioFilePath));
    playMusic();

    soundProcessor->extractAudioData(audioFilePath);
    double tempo = soundProcessor->detectTempo();
    std::cout << "Detected tempo: " << tempo << " BPM" << std::endl;
}

void SoundManager::playMusic() {
    if (!audioFilePath.isEmpty()) {
        qDebug() << "Playing audio from file:" << audioFilePath;
        player->play();
    } else {
        qDebug() << "No audio file loaded.";
    }
}

void SoundManager::pauseMusic() {
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        qDebug() << "Audio paused.";
    }
}

void SoundManager::stopMusic() {
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->stop();
        qDebug() << "Audio stopped.";
    }
}

