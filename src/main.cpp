#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>

class AnimatedWindow : public QWidget {
public:
    AnimatedWindow() : blockX(100), blockY(100) {
        setWindowTitle("Tetris Animation");
        resize(400, 600);

        // Create a timer to trigger updates
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &AnimatedWindow::updateAnimation);
        timer->start(30); // Trigger every 50ms (~20 FPS)
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        // Draw the moving block
        painter.setBrush(Qt::blue);
        painter.drawRect(blockX, blockY, 50, 50);
    }

private slots:
    void updateAnimation() {
        // Update block position
        blockY += 5;

        // Reset position if it moves out of the screen
        if (blockY > height()) {
            blockY = -50; // Reset above the top of the screen
        }

        // Trigger a repaint
        update();
    }

private:
    int blockX, blockY;
    QTimer* timer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AnimatedWindow window;
    window.show();

    return app.exec();
}