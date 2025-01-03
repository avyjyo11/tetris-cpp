#include "../include/MainWindow.h"
#include "../include/GameWindow.h"

#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), playButton(nullptr), restartButton(nullptr), gameWindow(nullptr) {
    setWindowTitle("Tetris Game");
    // resize(400, 600); // Adjust to fit Tetris gameplay area
    setupUI();
}

MainWindow::~MainWindow() {
    // Cleanup handled automatically by Qt
    delete playButton;
    delete restartButton;
    delete gameWindow;
}

void MainWindow::setupUI() {
    // Central widget to hold layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create buttons
    playButton = new QPushButton("Play", this);
    restartButton = new QPushButton("Restart", this);

    // Create animation window
    gameWindow = new GameWindow(this);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::handlePlayButton);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(playButton);
    layout->addWidget(restartButton);
    layout->addWidget(gameWindow);

    gameWindow->setFocus();
    centralWidget->setLayout(layout);
}

void MainWindow::handlePlayButton() {
    gameWindow->startAnimation();
}