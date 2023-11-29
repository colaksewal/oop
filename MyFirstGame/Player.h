#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <vector>  // vector için header dosyasını dahil edin

#include "Bullet.h"
class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    ~Player();

    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
    void spawn1();
    void decreaseOpacity(double amount);
private:
    std::vector<Bullet*> bullets;
};

#endif // PLAYER_H
