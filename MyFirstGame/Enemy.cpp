#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QDebug>
#include "Game.h"

extern Game *game;
extern Player *player;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem()
{   //set random position
    int random_number = rand() % 1200;
    setPos(random_number,0);

    //drew the rect
    setPixmap(QPixmap(":image/images/enemy1.png"));
    //Alaşağı ediyor fotoğrafı
    /*setTransformOriginPoint(50,50);
    setRotation(180);*/

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout() ) , this,SLOT(move()));

    timer -> start(110);
}


void Enemy::move()

{
    try {
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for (QGraphicsItem* item : colliding_items) {
            if (typeid(*item) == typeid(Player)) {
                // Player ile çarpışma oldu
                // Sağlık azaltılabilir veya diğer işlemler yapılabilir
                game->player->decreaseOpacity(0.2);
                game->health->decrease();

                // Enemy'yi sahneden kaldırma
                scene()->removeItem(this);
                delete this;
                return; // Çarpışma durumunda fonksiyondan çık
            }
        }

        //move enemy down
        setPos(x(), y() + 5);

        if (pos().y() < 0) {
            //decrease the health
            game->player->decreaseOpacity(0.2);
            game->health->decrease();

            scene()->removeItem(this);
            delete this;
        }
    } catch (std::exception& e) {
        // Hata durumunda yapılacak işlemler
        qDebug() << "Exception handled: " << e.what();
    } catch (...) {
        // Diğer tüm hata durumları için yapılacak işlemler
        qDebug() << "An unknown error has occurred";
    }
}








