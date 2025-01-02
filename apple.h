#ifndef APPLE_H
#define APPLE_H

#include <QPoint>

class Apple
{
private:
    QPoint m_position;
public:
    Apple();

    QPoint position() const;
    void setPosition(const QPoint newPosition);
};

#endif // APPLE_H
