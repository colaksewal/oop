﻿#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Score.h"
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsVideoItem>
#include <QDebug>
#include "Player.h"
#include "Health.h"
#include "Enemy.h"

Game::Game(QWidget* parent) : QGraphicsView(parent),timer0(nullptr) {
    // we write code block to create a scene

    //GİRİŞ EKRANI
    scene = new QGraphicsScene();

    // Set the scene for the QGraphicsView
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);

    QPixmap backgroundImage(":image/images/8753.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(backgroundItem);

    // Create a start button for the Game screen
    startButton = new QPushButton("START", this);
                  startButton->setFixedSize(200, 50);
                  startButton->setStyleSheet("background: green;color:white;");
    startButton->setFont(QFont("Arial", 16));
    startButton->move((width() - startButton->width()) / 2, height() - startButton->height() - 20);

    connect(startButton, &QPushButton::clicked, this, &Game::startGame);
    startButton -> hide();


    //create add Character
    charachter = new QPushButton("Karakter Seç", this);
    charachter -> setFixedSize(200,100);
    charachter ->  setFont(QFont("Arial", 16));
    charachter ->move ((width() - charachter->width()) / 2, height() - charachter->height() - 160);
    connect(charachter, &QPushButton::clicked, this, &Game::CharForGame);
    charachter -> hide();

    //gun screen for add Character
    gun = new QPushButton("Silah Seç", this);
                 gun -> setFixedSize(200,100);
    gun ->  setFont(QFont("Arial", 16));
    gun ->move ((width() - gun->width()) / 2, height() - gun->height() - 280);
    connect(gun, &QPushButton::clicked, this, &Game::GunForGame);
    gun -> hide();

    //level button
    selectLevelButton = new QPushButton("Selection",this);
    selectLevelButton->setFixedSize(200,100);
    selectLevelButton->setFont(QFont("Arial",16));
    selectLevelButton->move((width()-selectLevelButton->width())/2,height()-selectLevelButton->height()-420);
    connect(selectLevelButton,&QPushButton::clicked,this,&Game::SelectLevel);

    PlayMusic();

    // Create countdown timer

}


void Game::SelectLevel(){

    startButton ->hide();
    selectLevelButton ->hide();
    charachter->hide();
    gun -> hide();
    int screenWidth = 1200;
    int screenHeight = 800;

    int sceneWidth = 1200;
    int sceneHeight = 800;

    float widthScale = static_cast<float>(screenWidth) / sceneWidth;
    float heightScale = static_cast<float>(screenHeight) / sceneHeight;
    float scale = std::min(widthScale, heightScale);
    sceneWidth *= scale;
    sceneHeight *= scale;

    int sceneX = (screenWidth - sceneWidth) / 2;
    int sceneY = (screenHeight - sceneHeight) / 2;

    scene->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);

    // background
    QPixmap backgroundImage(":image/images/5183000.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(backgroundItem);

    int selectWidth = 100;  // Adjust the width of the gun images
    int selectHeight = 100;  // Adjust the height of the gun images


    for (int i = 0; i < 3; ++i) {
        // Create a QPushButton for each level
        QPushButton* levelButton = new QPushButton();
        //levelButton->setGeometry(sceneWidth / 2 - (3 * selectWidth) / 2 + i * selectWidth, sceneHeight / 2 + selectHeight / 2, selectWidth, 30);
        int buttonX = sceneWidth / 2 - (3 * selectWidth) / 2 + i * (selectWidth + 20);  // Adjust the space (20) between buttons
        int buttonY = sceneHeight / 2 + selectHeight / 2;

        levelButton->setGeometry(buttonX, buttonY, selectWidth, 30);

        // Create a linear gradient for the button background
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(levelButton->width(), levelButton->height()));
        linearGrad.setColorAt(0, Qt::red);
        linearGrad.setColorAt(1, Qt::blue);

        // Set the linear gradient as the background for the button using a style sheet
        levelButton->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);color:white;");
        scene->addWidget(levelButton);

        // Connect the button clicked signal to the slot based on the level
        switch (i) {
        case 0:
            levelButton->setText("Easy");
            connect(levelButton, &QPushButton::clicked, this, &Game::startLevel1);
            break;
        case 1:
            levelButton->setText("Medium");
            connect(levelButton, &QPushButton::clicked, this, &Game::startLevel2);
            break;
        case 2:
            levelButton->setText("Hard");
            connect(levelButton, &QPushButton::clicked, this, &Game::startLevel3);
            break;
        default:
            // Handle an unexpected case, if necessary
            break;
        }
    }


    QPushButton* backButton = new QPushButton("Next");
                              backButton->setGeometry(sceneWidth / 2 - 100, sceneHeight - 200, 200, 30);
                              backButton->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 green, stop:1 blue);color:white;");
    scene->addWidget(backButton);

    // Connect the button clicked signal to the slot
    //connect(backButton, &QPushButton::clicked, this, &Game::goBack);
    connect(backButton, &QPushButton::clicked, this, &Game::CharForGame);
}


void Game::CharForGame(){
    startButton ->hide();
    selectLevelButton ->hide();
    charachter->hide();
    gun -> hide();
    int screenWidth = 1200;
    int screenHeight = 800;

    int sceneWidth = 1200;
    int sceneHeight = 800;

    float widthScale = static_cast<float>(screenWidth) / sceneWidth;
    float heightScale = static_cast<float>(screenHeight) / sceneHeight;
    float scale = std::min(widthScale, heightScale);
    sceneWidth *= scale;
    sceneHeight *= scale;

    int sceneX = (screenWidth - sceneWidth) / 2;
    int sceneY = (screenHeight - sceneHeight) / 2;

    scene->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);

    // background
    QPixmap backgroundImage(":image/images/2615988.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(backgroundItem);

    int playerWidth = 100;  // Adjust the width of the gun images
    int playerHeight = 70;  // Adjust the height of the gun images

    for (int i = 0; i < 5; ++i) {
        // Oyuncu görüntülerini oluştur
        QPixmap playerImage(":image/images/player" + QString::number(i + 1) + ".png");
        QGraphicsPixmapItem* playerItem = new QGraphicsPixmapItem(playerImage);

        // Adjust the position of player images
        int playerX = sceneWidth / 2 - (5 * playerWidth) / 2 + i * (playerWidth + 40);
        int playerY = sceneHeight / 2 - playerHeight - 20;
        playerItem->setPos(playerX, playerY);
        scene->addItem(playerItem);

        //Create character selection buttons
        QPushButton* gunButton = new QPushButton("Select character");

        // Set the position and size of character selection buttons
        int buttonX = sceneWidth / 2 - (5 * playerWidth) / 2 + i * (playerWidth + 40);
        int buttonY = sceneHeight / 2 + playerHeight / 2;
        gunButton->setGeometry(buttonX, buttonY, playerWidth, 30);

        // Set the background of character selection buttons
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(gunButton->width(), gunButton->height()));
        linearGrad.setColorAt(0, Qt::red);
        linearGrad.setColorAt(1, Qt::blue);
        gunButton->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);color:white;");

      // Establish signal-slot connection to synchronize
        connect(gunButton, &QPushButton::clicked, this, [this, i]() { onPlayerButtonClicked(i); });

        // Add character selection buttons to the scene
        scene->addWidget(gunButton);
    }



    QPushButton* nextButton = new QPushButton("Next");
                              nextButton->setGeometry(sceneWidth / 2 - 100, sceneHeight - 200, 200, 30);
                              nextButton->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 green, stop:1 blue);color:white;");
    scene->addWidget(nextButton);

    // Connect the button clicked signal to the slot
    //connect(backButton, &QPushButton::clicked, this, &Game::goBack);
    connect(nextButton, &QPushButton::clicked, this, &Game::GunForGame);
}


void Game::onPlayerButtonClicked(int playerIndex) {
    // Handle gun selection logic here
    selectedPlayerIndex = playerIndex;
    qDebug() << "Player" << playerIndex + 1 << "selected.";
}


void Game::startLevel1() {
    velocity = 500;
    //Start level 1
    qDebug() << "Starting Level 1";
}

void Game::startLevel2() {
    velocity = 200;
    //Start level 2
    qDebug() << "Starting Level 2";
}

void Game::startLevel3() {
    velocity = 50;
    //Start level 3
    qDebug() << "Starting Level 3";
}

void Game::spawnEnemies(int velocity)
{
    QTimer* timer = new QTimer();
    // Pass the velocity as an argument to the Enemy constructor
    Enemy* enemy = new Enemy();
    QObject::connect(timer, SIGNAL(timeout()), enemy, SLOT(move()));
    timer->start(velocity);
}
void Game::GunForGame() {
    startButton ->show();
    selectLevelButton ->hide();
    charachter->hide();  // Assuming charachter is a typo and should be character
    gun->hide();

    int screenWidth = 1200;
    int screenHeight = 800;

    int sceneWidth = 1200;
    int sceneHeight = 800;

    float widthScale = static_cast<float>(screenWidth) / sceneWidth;
    float heightScale = static_cast<float>(screenHeight) / sceneHeight;
    float scale = std::min(widthScale, heightScale);
    sceneWidth *= scale;
    sceneHeight *= scale;

    int sceneX = (screenWidth - sceneWidth) / 2;
    int sceneY = (screenHeight - sceneHeight) / 2;

    scene->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);

    // Background
    QPixmap backgroundImage(":image/images/5183000.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(backgroundItem);

    // Gun images
    int gunWidth = 100;  // Adjust the width of the gun images
    int gunHeight = 70;  // Adjust the height of the gun images

    for (int i = 0; i < 5; ++i) {
        // Silah resimlerini oluştur
        QPixmap gunImage(":image/images/bullet" + QString::number(i + 1) + ".png");
        QGraphicsPixmapItem* gunItem = new QGraphicsPixmapItem(gunImage);

        int spaceBetweenGuns = 55;  // İhtiyaca göre boşluğu ayarlayın
        gunItem->setPos(sceneWidth / 2 - (5 * gunWidth) + 200 + i * (gunWidth + spaceBetweenGuns), sceneHeight / 2 - gunHeight / 2 + 15);
        scene->addItem(gunItem);

        // Silah seçimi butonlarını oluştur
        QPushButton* gunButton = new QPushButton("Select gun");

        // Silah seçimi butonlarının pozisyonunu ve boyutunu ayarla
        int buttonX = sceneWidth / 2 - (5 * gunWidth) + 175 + i * (gunWidth + spaceBetweenGuns);
        int buttonY = sceneHeight / 2 + gunHeight / 2;

        gunButton->setGeometry(buttonX, buttonY, gunWidth, 30);

        // Silah seçimi butonlarının arkaplanını ayarla
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(gunButton->width(), gunButton->height()));
        linearGrad.setColorAt(0, Qt::red);
        linearGrad.setColorAt(1, Qt::blue);

        gunButton->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);color:white;");

        // Senkronize etmek için sinyal-slot bağlantısı kur
        connect(gunButton, &QPushButton::clicked, this, [this, i]() { onGunButtonClicked(i); });

        // Sahneye silah seçimi butonlarını ekle
        scene->addWidget(gunButton);
    }
}



void Game::onGunButtonClicked(int gunIndex) {
    // Handle gun selection logic here
    selectedGunIndex = gunIndex;
    qDebug() << "Gun" << selectedGunIndex + 1 << "selected.";
}

void Game::startGame() {
    // Implement the start game logic here
    qDebug() << "Oyun başladı!";

    startButton->hide();
    charachter->hide();
    gun -> hide();
    SetScene();
}

void Game::SetScene() {
    // create the scene
    scene->clear();  // Clear existing scene

    int screenWidth = 1200;
    int screenHeight = 800;

    int sceneWidth = 1200;
    int sceneHeight = 800;

    float widthScale = static_cast<float>(screenWidth) / sceneWidth;
    float heightScale = static_cast<float>(screenHeight) / sceneHeight;
    float scale = std::min(widthScale, heightScale);
    sceneWidth *= scale;
    sceneHeight *= scale;

    int sceneX = (screenWidth - sceneWidth) / 2;
    int sceneY = (screenHeight - sceneHeight) / 2;

    scene->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);

    // background
    QMediaPlayer *video = new QMediaPlayer;

    QGraphicsVideoItem *videoItem = new QGraphicsVideoItem;
    video->setVideoOutput(videoItem);

    video->setSource(QUrl("qrc:/musics/video.mp4"));
    video-> play();

    videoItem->setZValue(-1);

    // Set the video item to cover the entire scene
    videoItem->setSize(scene->sceneRect().size());

    // Video öğesini sahneye ekle (arka plan olarak)
    scene->addItem(videoItem);


    // create the player
    player = new Player(nullptr, selectedGunIndex);
    addPlayerToScreen(player);
    scene->addItem(player);

    // create the score
    score = new Score();
    scene->addItem(score);

    // create the health
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

     //create timer
    // Create countdown timer
    Timer* timer0 = new Timer();
    timer0->setPos(1000, 0);  // Position the timer at the top right corner
    scene->addItem(timer0);

    // Connect the countdown timer's timeExpired signal to the gameOver slot
    connect(timer0, &Timer::timeExpired, this, &Game::gameOver);

    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() { player->spawn(velocity); });
    timer->start(2000);

    QTimer* timer1 = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() { player->spawn1(velocity); });
    timer1->start(2200);
}

void Game::addPlayerToScreen(Player* player) {
    player->setPixmap(QPixmap(":image/images/player" +  QString::number(selectedPlayerIndex + 1) + ".png"));
    player->setPos(400, 500);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect();
    dropShadowEffect->setColor(Qt::yellow);
    dropShadowEffect->setOffset(0, -100);
    dropShadowEffect->setBlurRadius(400);

    player->setGraphicsEffect(dropShadowEffect);
}

void Game::PlayMusic() {
    // play background music
    QMediaPlayer* music = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/musics/sounds.mp3"));
    audioOutput->setVolume(5);
    music->play();
}

void Game::gameOver() {
    // Clear existing scene
    scene->clear();
    // Show Game Over message
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("Game Over");
    QFont gameOverFont("Arial", 50);
    gameOverText->setFont(gameOverFont);
    gameOverText->setDefaultTextColor(Qt::red);
    int xPos = width() / 2 - gameOverText->boundingRect().width() / 2;
    int yPos = height() / 2 - gameOverText->boundingRect().height() / 2;
    gameOverText->setPos(xPos, yPos);
    scene->addItem(gameOverText);
}

void Game::goBack() {
    // Clear the current scene
    scene->clear();

    // Show the start button and other UI elements
    startButton->show();
    charachter->show();
    gun->show();
    selectLevelButton ->show();

    QPixmap backgroundImage(":image/images/8753.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(backgroundItem);
}



