#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Bullet : public QObject,  public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = 0, int gunIndex = 0);
    bool operator==(const Bullet& other) const;
    int gunIndex;


public slots:
    void move();
    void move1();



};


#endif // BULLET_H
