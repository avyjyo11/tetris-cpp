#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "../include/GameWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePlayButton();
    void handleRestartButton();
    void updateScoreDisplay(unsigned int newScore); 
    
private:
    QPushButton *playButton;
    QPushButton *restartButton;
    QLabel *scoreLabel;
    GameWindow *gameWindow;

    void setupUI();
};

#endif // MAINWINDOW_H