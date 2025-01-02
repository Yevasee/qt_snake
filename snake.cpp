#include "snake.h"

Snake::Snake()
{
}

//phisique
int Snake::length() const
{
    return m_length;
}

int Snake::size() const
{
    return m_length;
}

void Snake::setLength(const int length)
{
    m_length = length;
    m_body.resize(length);
}

void Snake::setSize(const int size)
{
    m_length = size;
    m_body.resize(size);
}

void Snake::grow()
{
    m_length++;
    m_body.push_back(QPoint(0, 0));
}

//position
QPoint Snake::getPositionBodyPart(const int index)
{
    return m_body[index];
}

void Snake::setPositionsBodyParts(const int ypos)
{
    for (int i = 0; i < m_body.size(); ++i) {
        m_body[i].setX(m_body.size() - i - 1);
        m_body[i].setY(ypos);
    }
}

bool Snake::bodyContains(const QPoint pos)
{
    return m_body.contains(pos);
}

//direction
void Snake::setDirectionMove(const Directions dir)
{
    m_directionMove = dir;
}

void Snake::handleKey(int key)
{
    if (key == Qt::Key_A && m_body[0].y() != m_body[1].y()) {
        setDirectionMove(Directions::left);
    } else if (key == Qt::Key_D && m_body[0].y() != m_body[1].y()) {
        setDirectionMove(Directions::right);
    } else if (key == Qt::Key_W && m_body[0].x() != m_body[1].x()) {
        setDirectionMove(Directions::up);
    } else if (key == Qt::Key_S && m_body[0].x() != m_body[1].x()) {
        setDirectionMove(Directions::down);
    }
}

void Snake::move()
{
    for (int i = m_body.size() - 1; i > 0; i--)
        m_body[i] = m_body[i - 1];

    switch (m_directionMove) {
    case left:
        m_body[0].rx() -= 1;
        break;
    case right:
        m_body[0].rx() += 1;
        break;
    case up:
        m_body[0].ry() -= 1;
        break;
    case down:
        m_body[0].ry() += 1;
        break;
    }
}

//save move
bool Snake::isImpactWithSelf()
{
    bool impact = false;
    if (m_body.size() > 4) {
        for (int i = 1; i < m_body.size() && !impact; ++i) {
            if (m_body[0] == m_body[i]) {
                impact = true;
            }
        }
    }
    return impact;
}

bool Snake::isImpactWithEdge(const int widthArena, const int heightArena)
{
    bool impact = false;
    if (m_body[0].x() >= widthArena
        || m_body[0].x() < 0
        || m_body[0].y() >= heightArena
        || m_body[0].y() < 0)
    {
        impact = true;
    }
    return impact;
}
