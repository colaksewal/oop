#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyChild.h"
#include <QGraphicsOpacityEffect>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

}

Player::~Player()
{
    // bullets vectoründeki tüm mermileri temizleme
    for (Bullet* bullet : bullets) {
        scene()->removeItem(bullet);
        delete bullet;
    }
    bullets.clear();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    int step = 15; // Hareket adımı

    // Yön tuşları ile hareket
    if (event->key() == Qt::Key_Up) {
        setPos(x(), y() - step);
    } else if (event->key() == Qt::Key_Down) {
        setPos(x(), y() + step);
    } else if (event->key() == Qt::Key_Left) {
        setPos(x() - step, y());
    } else if (event->key() == Qt::Key_Right) {
        setPos(x() + step, y());
    } else if (event->key() == Qt::Key_Space) {
        //create a bulletwith a vector
        int randomX = rand() % 100; // 100, player genişliğine göre
        int randomX1 = rand() % 100 ;
        // Create the first bullet
        Bullet *bullet1 = new Bullet();
        bullet1->setPos(x()+ randomX1, y());
        scene()->addItem(bullet1);
        bullets.push_back(bullet1);  // Vector'e bullet1 ekleme

        // Create the second bullet with a slight offset to the right
        Bullet *bullet2 = new Bullet();
        bullet2->setPos(x() + randomX, y()); // Örnek olarak, 70 birim sağa kaydırıldı
        scene()->addItem(bullet2);
        bullets.push_back(bullet2);

        // Mermilerin çakışmasını kontrol etme
        if (*bullet1 == *bullet2) {
            // İki mermi aynı pozisyonda, her ikisini de listeden çıkart
            bullets.pop_back();
            scene()->removeItem(bullet1);
            delete bullet1;
            bullets.pop_back();
            scene()->removeItem(bullet2);
            delete bullet2;
        }
    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}


void Player::spawn1()
{
    //create an enemy
    EnemyChild * enemy1 = new EnemyChild();
    scene() -> addItem(enemy1);

}

void Player::decreaseOpacity(double amount = 0.2)
{
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    opacityEffect->setOpacity(amount);
    setGraphicsEffect(opacityEffect);
}


