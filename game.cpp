#include "game.h"
#include <QDebug>
Game::Game()
{
    resize(s_dotWidth * s_fieldWidth, s_dotHeight*s_fieldHeight);
    setWindowTitle("Snake game");

    initGame();
}

void Game::initGame()
{
    m_inGame = true;
    localApple();
    m_eatenApples = 0;

    m_dots.resize(s_snakeLength);
    for (int i = 0; i < m_dots.size(); ++i) {
        m_dots[i].setX(m_dots.size() - i - 1);
        m_dots[i].setY(0);
    }

    m_dir = right;
    m_timerId = startTimer(s_delay);
}

void Game::timerEvent(QTimerEvent *)
{
    if (m_inGame) {
        checkApple();
        move();
        checkField();
    }
    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "press";
    int key = event->key();
    if (key == Qt::Key_A && m_dots[0].y() != m_dots[1].y()) {
        m_dir = Directions::left;
    } else if (key == Qt::Key_D && m_dots[0].y() != m_dots[1].y()) {
        m_dir = Directions::right;
    } else if (key == Qt::Key_W && m_dots[0].x() != m_dots[1].x()) {
        m_dir = Directions::up;
    } else if (key == Qt::Key_S && m_dots[0].x() != m_dots[1].x()) {
        m_dir = Directions::down;
    } else if (key == Qt::Key_Escape) {
        this->close();
    }
}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    doDrawing();
}

void Game::move()
{
    // start direction = right

    for (int i = m_dots.size() - 1; i > 0; i--)
        m_dots[i] = m_dots[i - 1];

    switch (m_dir) {
    case left:
        m_dots[0].rx() -= 1;
        break;
    case right:
        m_dots[0].rx() += 1;
        break;
    case up:
        m_dots[0].ry() -= 1;
        break;
    case down:
        m_dots[0].ry() += 1;
        break;
    }
}

void Game::checkField()
{
    if (m_dots.size() > 3) {
        for (int i = 1; i < m_dots.size(); ++i) {
            if (m_dots[0] == m_dots[i]) {
                m_inGame = false;
            }
        }
    }
    if (m_dots[0].x() >= s_fieldWidth
        || m_dots[0].x() < 0
        || m_dots[0].y() >= s_fieldHeight
        || m_dots[0].y() < 0)
    {
        m_inGame = false;
    }

    if(!m_inGame)
        killTimer(m_timerId);
}

void Game::checkApple()
{
    if (m_apple == m_dots[0]) {
        m_dots.push_back(QPoint(0, 0));
        m_eatenApples++;
        localApple();
    }
}

void Game::localApple()
{
    QPoint pos(QRandomGenerator::global()->generate() % s_fieldWidth,
               QRandomGenerator::global()->generate() % s_fieldHeight);
    while (m_dots.contains(pos)) {
        pos.rx() = QRandomGenerator::global()->generate() % s_fieldWidth;
        pos.rx() = QRandomGenerator::global()->generate() % s_fieldHeight;
    }
    m_apple.setX(pos.x());
    m_apple.setY(pos.y());
    //qDebug() << "posx: " << m_apple.x() << "\nposy: " << m_apple.y();
}

void Game::doDrawing()
{
    QPainter arena(this);

    if (m_inGame) {
        arena.setBrush(Qt::red);
        arena.drawEllipse(m_apple.x() * s_dotWidth, m_apple.y() * s_dotHeight, s_dotWidth, s_dotHeight);
        //qDebug() << "2 posx: " << m_apple.x() << "\nposy: " << m_apple.y();

        arena.setBrush(Qt::green);
        for (int i = 0; i < m_dots.size(); ++i) {
            arena.drawEllipse(m_dots[i].x() * s_dotWidth, m_dots[i].y() * s_dotHeight, s_dotWidth, s_dotHeight);
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
