#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "QPushButton"
#include <QGraphicsProxyWidget>
#include <QVector>

class Game: public QGraphicsView
{


public:
    Game(QWidget * parent= 0 );


    QGraphicsScene * scene;
    Player * player;
    Score *score;
    Health *health;
    QPushButton* startButton;
    QPushButton* charachter;
    QPushButton* gun;

    void SetScene();
    void startGame();
    void CharForGame();
    void GunForGame();
    void gameOver();
    void handleKeyPress();
    void addPlayerToScreen(Player *player);
    void PlayMusic();
    void SetScene(QGraphicsScene * scene);




};

#endif // GAME_H
