#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameWindow.h"
#include "NextWindow.h"
#include "SoundManager.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadMusic();
    void handlePlayButton();
    void handleRestartButton();
    void updateScoreDisplay(unsigned int newScore); 
    
private:
    QPushButton *playButton;
    QPushButton *restartButton;
    QLabel *scoreLabel;
    
    GameWindow *gameWindow;
    NextWindow *nextWindow;
    SoundManager *soundManager;

    void setupUI();
};

#endif // MAINWINDOW_H