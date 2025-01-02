#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>

#include "snake.h"
#include "apple.h"

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
    static const int s_snakeLength = 3;
    static const int s_delay = 100;

    Snake *m_snake = new Snake;
    Apple *m_apple = new Apple;

    bool m_inGame;
    int m_timerId;
    int m_eatenApples;

    void initGame();
    void draw();
    void setApple();
    void checkApple();
    void gameOver();
};

#endif // GAME_H
