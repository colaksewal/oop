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
    Player(QGraphicsItem * parent=0, int gunIndex = 0);
    ~Player();

    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn(int velocity);
    void spawn1(int velocity);
    void decreaseOpacity(double amount);
    void characterSelected(const QString& characterName);


private:
    std::vector<Bullet*> bullets;
    Character* selectedCharacter;
    int gunIndex;
    int velocity;
};


#endif // PLAYER_H
