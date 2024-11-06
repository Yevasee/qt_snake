#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>

class Game : public QWidget
{
public:
    Game();

protected:
    void timerEvent(QTimerEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    static const int DOT_WIDTH = 30;
    static const int DOT_HEIGHT = 30;
    static const int FIELD_WIDTH = 15;
    static const int FIELD_HEIGHT = 15;
    static const int DELAY = 100;
    static const int SNAKE_LENGTH = 3;

    QVector<QPoint> m_dots;
    QPoint m_apple;
    enum Directions {
        left, right, up, down
    };
    Directions m_dir;
    int m_timerId;
    bool m_inGame;
    int m_eatenApples;

    void initGame();
    void localApple();
    void checkApple();
    void doDrawing();
    void move();
    void checkField();
    void gameOver();
};

#endif // GAME_H
