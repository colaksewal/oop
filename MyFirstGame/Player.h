#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <vector>  // vector için header dosyasını dahil edin

#include "Bullet.h"
#include "Character.h"
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
    void characterSelected(const QString& characterName);
private:
    std::vector<Bullet*> bullets;
    Character* selectedCharacter;
};

#endif // PLAYER_H
