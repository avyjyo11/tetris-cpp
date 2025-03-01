#include "../include/MainWindow.h"
#include "../include/GameWindow.h"
#include "../include/SoundManager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), playButton(nullptr), restartButton(nullptr), gameWindow(nullptr) {
    setWindowTitle("Tetris Game");
    // resize(400, 600); // Adjust to fit Tetris gameplay area
    setupUI();
    soundManager = new SoundManager(this);
}

MainWindow::~MainWindow() {
    // Cleanup handled automatically by Qt
    delete gameWindow;
    delete nextWindow;
}

void MainWindow::setupUI() {
    // Central widget to hold layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    // Create game window
    nextWindow = new NextWindow(this);
    gameWindow = new GameWindow(this, nextWindow);
    splitter->addWidget(gameWindow);

    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    // Create score display widget
    QWidget *scoreWidget = new QWidget(this);
    QVBoxLayout *scoreLayout = new QVBoxLayout(scoreWidget);

    QLabel *levelLabel = new QLabel("Level: 1", this);
    scoreLabel = new QLabel("Score: 0", this);
    
    scoreLayout->addWidget(levelLabel);
    scoreLayout->addWidget(scoreLabel);
    
    scoreWidget->setFixedWidth(200);
    scoreWidget->setFixedHeight(100);
    
    rightLayout->addWidget(scoreWidget);
    rightLayout->addWidget(nextWindow);

    playButton = new QPushButton("Play", this);
    restartButton = new QPushButton("Restart", this);
    QPushButton *loadMusicButton = new QPushButton("Load Music", this);

    QVBoxLayout *nextLayout = new QVBoxLayout(nextWindow);
    scoreLayout->addLayout(nextLayout);

    // Layout for buttons
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addStretch(); // Push buttons to the bottom
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(restartButton);
    buttonLayout->addWidget(loadMusicButton);

    // Add button layout to score widget
    rightLayout->addLayout(buttonLayout);
    splitter->addWidget(rightPanel);
    
    // Set the splitter as the central widget's layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(splitter);

    // Connect signals
    connect(playButton, &QPushButton::clicked, this, &MainWindow::handlePlayButton);
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::handleRestartButton);
    connect(gameWindow, &GameWindow::scoreUpdated, this, &MainWindow::updateScoreDisplay); 
    connect(loadMusicButton, &QPushButton::clicked, this, &MainWindow::loadMusic);

    gameWindow->setFocus();
}

void MainWindow::handlePlayButton() {
    if (gameWindow->isRunning()) {
        gameWindow->pauseGame();
        soundManager->pauseMusic();
        playButton->setText("Resume"); // Change button text to "Resume"
    } else {
        gameWindow->startGame();
        soundManager->playMusic();
        playButton->setText("Pause"); // Change button text to "Pause"
    }
}

void MainWindow::handleRestartButton() {
    gameWindow->restartGame();
    playButton->setText("Play");
}

void MainWindow::updateScoreDisplay(unsigned int newScore) { // Change parameter type to unsigned int
   scoreLabel->setText(QString("Score: %1").arg(newScore));
}

void MainWindow::loadMusic() {
    QString filePath = QFileDialog::getOpenFileName(this, "Load Music", "", "Audio Files (*.mp3 *.wav *.aac)");
    if (!filePath.isEmpty()) {
        soundManager->loadMusic(filePath);
    } else {
        QMessageBox::warning(nullptr, "No File Selected", "No audio file selected.");
    }
}