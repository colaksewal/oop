#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyChild.h"
#include <QGraphicsOpacityEffect>


Player::Player(QGraphicsItem *parent, int gunIndex): QGraphicsPixmapItem(parent){

    this-> gunIndex = gunIndex;

    qDebug() << "Gun" << gunIndex << "player.";
}

Player::~Player()
{
    delete selectedCharacter;
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
        Bullet *bullet1 = new Bullet(nullptr, gunIndex);
        bullet1->setPos(x()+ randomX1, y());
        scene()->addItem(bullet1);
        bullets.push_back(bullet1);  // Vector'e bullet1 ekleme

        // Create the second bullet with a slight offset to the right
        Bullet *bullet2 = new Bullet(nullptr, gunIndex);
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

void Player::spawn(int velocity){
    // create an enemy
     qDebug() << "velocity";
    qDebug() << velocity;
    Enemy * enemy = new Enemy(this, velocity);
    scene()->addItem(enemy);
}


void Player::spawn1(int velocity)
{
    //create an enemy
    EnemyChild * enemy1 = new EnemyChild(this, velocity);
    scene() -> addItem(enemy1);

}

void Player::decreaseOpacity(double amount = 0.2)
{
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    opacityEffect->setOpacity(amount);
    setGraphicsEffect(opacityEffect);
}

void Player::characterSelected(const QString& characterName) {
    // Handle character selection
    // You can use characterName to identify the selected character
    qDebug() << "Selected Character:" << characterName;

    // Store the selected character or perform other actions
    // For example, you can create an instance of the selected character
    // and add it to the scene, or change the player's appearance based on the selection
    if (selectedCharacter) {
        scene()->removeItem(selectedCharacter);
        delete selectedCharacter;
    }

    selectedCharacter = new Character(":image/images/selected_character.png");
    scene()->addItem(selectedCharacter);
    selectedCharacter->setPos(x(), y());
}

