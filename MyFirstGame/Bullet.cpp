#include "Bullet.h"
#include <QTimer>
#include <QList>
#include "Enemy.h"
#include <QGraphicsScene>
#include "Enemy.h"
#include "EnemyChild.h"
#include "EnemyChild.h"
#include "Game.h"

extern Game * game ;// there is an external global object called game


Bullet::Bullet(QGraphicsItem *parent , int gunIndex):QObject () ,QGraphicsPixmapItem(parent)
{
    this->gunIndex = gunIndex;

    qDebug() << "Gun" << gunIndex << "raised.";

    //draw the rect
    setPixmap(QPixmap(":image/images/bullet" + QString::number(gunIndex + 1) + ".png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this,SLOT(move()));

    timer -> start(50);

    QTimer * timer1 = new QTimer();
    connect(timer1,SIGNAL(timeout()), this,SLOT(move1()));

    timer1 -> start(50);
}



void Bullet :: move1(){

    QList<QGraphicsItem * > colliding_items = collidingItems();

    for(int i = 0 , n = colliding_items.size() ; i<n ; ++i){

        if(typeid(*(colliding_items[i])) == typeid(EnemyChild)){
            //increase score
            game->score->increase1();
            //remove them both
            scene() -> removeItem(colliding_items[i]);
            scene() -> removeItem(this);
            //delete them both
            delete colliding_items[i];
            delete this;
            return;
        }
    }
    //move bulletet up
    setPos(x(), y()-10);

    if(pos().y()  < 0 ){
        scene() -> removeItem(this);
        delete this;
    }

}

void Bullet::move()
{
    //if bullet collides with enemy, destrpy both

    QList<QGraphicsItem *> colliding_items = collidingItems() ;
    for(int i = 0 , n = colliding_items.size() ; i<n ; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Enemy)){
            //increase score
            game->score->increase();
                //remove them both
            scene() -> removeItem(colliding_items[i]);
            scene() -> removeItem(this);
            //delete them both
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    //move bulletet up
    setPos(x(), y()-10);
    if(pos().y()  < 0 ){
        scene() -> removeItem(this);
        delete this;
    }
}

bool Bullet::operator==(const Bullet& other) const
{
    return (pos() == other.pos());
}

