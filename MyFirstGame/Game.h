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
    QPushButton* selectLevelButton;
    QPushButton* level1Button;
    QPushButton* level2Button;
    QPushButton* level3Button;

    int selectedGunIndex;
    int selectedPlayerIndex;
    int velocity;

    void EntrySceen(QGraphicsScene *scene);
    void SetScene();
    void startGame();
    void CharForGame();
    void GunForGame();
    void gameOver();
    void handleKeyPress();
    void addPlayerToScreen(Player *player);
    void PlayMusic();
    void SetScene(QGraphicsScene * scene);
    void onGunButtonClicked(int gunIndex);
    void onPlayerButtonClicked(int playerIndex);
    void goBack();
    void SelectLevel();
    void spawnEnemies(int velocity);
    void StartLevel();
    void startLevel1();
    void startLevel2();
    void startLevel3();



};

#endif // GAME_H
