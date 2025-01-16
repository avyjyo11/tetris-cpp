#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <QThread>
#include <QMediaPlayer>
#include <QString>
#include <QMutex>

class AudioProcessor : public QThread {
    Q_OBJECT

public:
    explicit AudioProcessor(QObject *parent = nullptr);
    void loadAudio(const QString &filePath);
    void stopProcessing();
    
signals:
    void frequencyDetected(double frequency); // Signal to notify detected frequency

protected:
    void run() override;

private:
    QString audioFilePath;
    bool running;
    QMutex mutex;

    double analyzeFrequency(); // Method to analyze frequency from audio
};

#endif // AUDIOPROCESSOR_H
