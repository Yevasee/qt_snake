#ifndef SNAKE_H
#define SNAKE_H

#include <QKeyEvent>
#include <QVector>
#include <QPoint>

class Snake
{
public:
    enum Directions {
        left, right, up, down
    };

private:
    int m_length {3};
    QVector<QPoint> m_body;
    Directions m_directionMove;

public:
    Snake();

    //phisique
    int length() const;
    int size() const;
    void setLength(const int length);
    void setSize(const int size);
    void grow();

    //positon
    QPoint positionBodyPart(const int index);
    void setPositionsBodyParts(const int ypos);
    bool bodyContains(const QPoint pos);

    //direction
    void setDirectionMove(const Directions dir);
    void handleKey(int key);
    void move();

    //save move
    bool isImpactWithSelf();
    bool isImpactWithEdge(const int widthArena, const int heightArena);
};

#endif // SNAKE_H
