#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "QPushButton"
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

    void SetScene();
    void startGame();
    void CharForGame();
    void gameOver();
    void startSecondPlayer();
    void handleKeyPress();
    void addPlayerToScreen(Player *player);
    void PlayMusic();
    void SetScene(QGraphicsScene * scene);
    void selectPlayer();

private slots:
    void handleTimerExpired();
};

#endif // GAME_H
