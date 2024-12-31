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
    static const int s_dotWidth = 30;
    static const int s_dotHeight = 30;
    static const int s_fieldWidth = 15;
    static const int s_fieldHeight = 15;
    static const int s_delay = 100;
    static const int s_snakeLength = 3;

    bool m_inGame;
    int m_timerId;
    int m_eatenApples;
    QVector<QPoint> m_dots;
    QPoint m_apple;
    enum Directions {
        left, right, up, down
    };
    Directions m_dir;

    void initGame();
    void localApple();
    void checkApple();
    void checkField();
    void doDrawing();
    void move();
    void gameOver();
};

#endif // GAME_H
