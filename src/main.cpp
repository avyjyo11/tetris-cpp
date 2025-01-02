#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <iostream>

class TetrisWindow : public QWidget {
public:
    TetrisWindow() {
        setWindowTitle("Tetris");
        resize(800, 600);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setBrush(Qt::green);
        painter.drawRect(100, 100, 50, 50);  // Example of drawing a "Tetris block"
    }

    void keyPressEvent(QKeyEvent* event) override {
        if (event->key() == Qt::Key_Left) {
            std::cout << "Move left" << std::endl;
        } else if (event->key() == Qt::Key_Right) {
            std::cout << "Move right" << std::endl;
        }
        QWidget::keyPressEvent(event);
    }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  TetrisWindow window;
  window.show();

  return app.exec();
}