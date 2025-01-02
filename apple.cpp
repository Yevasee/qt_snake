#include "apple.h"

Apple::Apple()
{

}

QPoint Apple::position() const
{
    return m_position;
}

void Apple::setPosition(const QPoint newPosition)
{
    m_position = newPosition;
}
