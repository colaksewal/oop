#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Score.h"
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "Player.h"
#include "Health.h"

Game::Game(QWidget* parent) : QGraphicsView(parent) {
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
    startButton = new QPushButton("Oyuna Başla", this);
                  startButton->setFixedSize(200, 50);
    startButton->setFont(QFont("Arial", 16));
    startButton->move((width() - startButton->width()) / 2, height() - startButton->height() - 20);

    connect(startButton, &QPushButton::clicked, this, &Game::startGame);

    //create add Character
    charachter = new QPushButton("Karakter Seç", this);
    charachter -> setFixedSize(200,100);
    charachter ->  setFont(QFont("Arial", 16));
    charachter ->move ((width() - charachter->width()) / 2, height() - charachter->height() - 160);
    connect(charachter, &QPushButton::clicked, this, &Game::CharForGame);

    //gun screen for add Character
    gun = new QPushButton("Silah Seç", this);
                 gun -> setFixedSize(200,100);
    gun ->  setFont(QFont("Arial", 16));
    gun ->move ((width() - gun->width()) / 2, height() - gun->height() - 280);
    connect(gun, &QPushButton::clicked, this, &Game::GunForGame);



    PlayMusic();

    // Create countdown timer

}

void Game::CharForGame(){


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


}


void Game::GunForGame(){

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


}

void Game::startGame() {
    // Implement the start game logic here
    qDebug() << "Oyun başladı!";

    startButton->hide();
    charachter->hide();

    SetScene();

    // addPlayerToScreen(player);
    // ... (diğer oyun başlatma işlemleri)
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
    QPixmap backgroundImage(":image/images/background.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(backgroundItem);

    // create the player
    player = new Player();
    addPlayerToScreen(player);
    scene->addItem(player);

    // create the score
    score = new Score();
    scene->addItem(score);

    // create the health
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);

    QTimer* timer1 = new QTimer();
    QObject::connect(timer1, SIGNAL(timeout()), player, SLOT(spawn1()));
    timer1->start(2200);
}

void Game::addPlayerToScreen(Player* player) {
    player->setPixmap(QPixmap(":image/images/pika.png"));
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

