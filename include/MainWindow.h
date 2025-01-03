#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "../include/GameWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePlayButton();
    
private:
    QPushButton *playButton;
    QPushButton *restartButton;
    GameWindow *gameWindow;

    void setupUI();
};

#endif // MAINWINDOW_H