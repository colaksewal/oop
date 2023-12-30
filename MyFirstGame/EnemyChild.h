#ifndef ENEMYCHILD_H
#define ENEMYCHILD_H

#include "Enemy.h"

class EnemyChild : public Enemy
{
    Q_OBJECT
public:
    explicit EnemyChild(QGraphicsItem *parent = nullptr, int velocity = 100);
    int velocity;
    void move() override;

private:

};

#endif // ENEMYCHILD_H
