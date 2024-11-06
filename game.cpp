#include "game.h"
#include <QDebug>
Game::Game()
{
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    setWindowTitle("Snake game");

    initGame();
}

void Game::timerEvent(QTimerEvent *)
{
    if(m_inGame){
        checkApple();
        move();
        checkField();
    }
    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *event)
{

    qDebug() << "press";
    int key = event->key();
    if(key == Qt::Key_A && m_dots[0].y()!=m_dots[1].y()){
        m_dir = Directions::left;
    }
    else if(key == Qt::Key_D && m_dots[0].y()!=m_dots[1].y()){
        m_dir = Directions::right;
    }
    else if(key == Qt::Key_W && m_dots[0].x()!=m_dots[1].x()){
        m_dir = Directions::up;
    }
    else if(key == Qt::Key_S && m_dots[0].x()!=m_dots[1].x()){
        m_dir = Directions::down;
    }
    else if(key == Qt::Key_Escape){
        this->close();
    }
}

void Game::move()
{
    for(int i = m_dots.size()-1; i>0;i--){
        m_dots[i] = m_dots[i-1];
    }
    switch (m_dir) {
        case left: {m_dots[0].rx() -= 1; break;}
        case right: {m_dots[0].rx() += 1; break;}
        case up: {m_dots[0].ry() -= 1; break;}
        case down: {m_dots[0].ry() += 1; break;}
    }
}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    doDrawing();
}

void Game::initGame() {
    m_inGame = true;
    localApple();
    m_eatenApples = 0;
    m_dir = right;

    m_dots.resize(SNAKE_LENGTH);

    for(int i=0; i < m_dots.size(); ++i) {
        m_dots[i].setX(m_dots.size() - i - 1);
        m_dots[i].setY(0);
    }


    m_timerId = startTimer(DELAY);
}

void Game::localApple()
{
    QPoint pos(QRandomGenerator::global()->generate()%FIELD_WIDTH,
               QRandomGenerator::global()->generate()%FIELD_HEIGHT);
    while(m_dots.contains(pos)){
        pos.rx() = QRandomGenerator::global()->generate()%FIELD_WIDTH;
        pos.rx() = QRandomGenerator::global()->generate()%FIELD_HEIGHT;
    }
    m_apple.setX(pos.x());
    m_apple.setY(pos.y());
    qDebug() << "posx: " << m_apple.x() << "\nposy: " << m_apple.y();
}

void Game::checkApple()
{
    if(m_apple == m_dots[0]){
        m_dots.push_back(QPoint(0,0));
        m_eatenApples++;
        localApple();
    }
}

void Game::doDrawing()
{
    QPainter qp(this);

    if(m_inGame){
        qp.setBrush(Qt::red);
        qp.drawEllipse(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        //qDebug() << "2 posx: " << m_apple.x() << "\nposy: " << m_apple.y();

        qp.setBrush(Qt::green);
        for(int i = 0; i < m_dots.size(); ++i){
            qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        }
    } else {
        gameOver();
    }
}

void Game::checkField()
{
    if(m_dots.size() > 3) {
        for(int i = 1; i < m_dots.size(); ++i){
            if(m_dots[0] == m_dots[i]){
                m_inGame = false;
            }
        }
    }
    if(m_dots[0].x() >= FIELD_WIDTH){
        m_inGame = false;
    }
    else if(m_dots[0].x() < 0){
        m_inGame = false;
    }
    else if(m_dots[0].y() >= FIELD_HEIGHT){
        m_inGame = false;
    }
    else if(m_dots[0].y() < 0){
        m_inGame = false;
    }

    if(!m_inGame){
        killTimer(m_timerId);
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
