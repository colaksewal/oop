#include "EnemyChild.h"
#include "Player.h"
#include "Game.h"
#include <QTimer>

extern Game *game;

EnemyChild::EnemyChild(QGraphicsItem *parent) : Enemy(parent)
{
    // Farklı bir görsel atanabilir
    setPixmap(QPixmap(":image/images/enemy2.png"));

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout() ) , this,SLOT(move()));

    timer -> start(100);
}

void EnemyChild::move()
{
    // Çaprazdan hareket etmek için x ve y pozisyonlarını güncelle
    setPos(x() + 5, y()+5);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items) {
        if (typeid(*item) == typeid(Player)) {
            // Player ile çarpışma oldu
            // Sağlık azaltılabilir veya diğer işlemler yapılabilir
            game->health->decrease();
            game->player->decreaseOpacity(0.2);
            // Enemy'yi sahneden kaldırma
            scene()->removeItem(this);
            delete this;
            return; // Çarpışma durumunda fonksiyondan çık
        }
    }
}
