#include "game.h"
//#include <QDebug>
Game::Game()
{
    resize(s_dotWidth * s_fieldWidth, s_dotHeight*s_fieldHeight);
    setWindowTitle("Snake game");

    initGame();
}

void Game::initGame()
{
    m_inGame = true;
    m_snake->setLength(s_snakeLength);
    m_snake->setPositionsBodyParts(0);
    m_snake->setDirectionMove(Snake::Directions::right);
    setApple();
    m_eatenApples = 0;
    m_timerId = startTimer(s_delay);
}

void Game::timerEvent(QTimerEvent *)
{
    if (m_inGame) {
        checkApple();
        m_snake->move();
        if (m_snake->isImpactWithSelf() || m_snake->isImpactWithEdge(s_fieldWidth, s_fieldHeight)) {
            m_inGame = false;
            killTimer(m_timerId);
        }
    }
    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    m_snake->handleKey(key);
}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    draw();
}

void Game::checkApple()
{
    if (m_apple->position() == m_snake->positionBodyPart(0)) {
        m_snake->grow();
        m_eatenApples++;
        setApple();
    }
}

void Game::setApple()
{
    QPoint pos;
    do {
        pos.rx() = QRandomGenerator::global()->generate() % s_fieldWidth;
        pos.ry() = QRandomGenerator::global()->generate() % s_fieldHeight;
    } while (m_snake->bodyContains(pos));
    m_apple->setPosition(pos);
    //qDebug() << "posx: " << m_apple.x() << "\nposy: " << m_apple.y();
}

void Game::draw()
{
    QPainter arena(this);

    if (m_inGame) {
        arena.setBrush(Qt::red);
        arena.drawEllipse(m_apple->position().x() * s_dotWidth,
                          m_apple->position().y() * s_dotHeight, s_dotWidth, s_dotHeight);
        //qDebug() << "2 posx: " << m_apple.x() << "\nposy: " << m_apple.y();

        arena.setBrush(Qt::green);
        for (int i = 0; i < m_snake->length(); ++i) {
            arena.drawEllipse(m_snake->positionBodyPart(i).x() * s_dotWidth,
                              m_snake->positionBodyPart(i).y() * s_dotHeight, s_dotWidth, s_dotHeight);
        }
    } else {
        gameOver();
    }
}

void Game::gameOver()
{
    QMessageBox msgb;
    QString text = "Game Over\nEaten apples: " + QString::number(m_eatenApples);
    msgb.setText(text);
    msgb.exec();

    initGame();
}
