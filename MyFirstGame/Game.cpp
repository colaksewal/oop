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
#include "Enemy.h"

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


    //level button
    selectLevelButton = new QPushButton("Select Level",this);
    selectLevelButton->setFixedSize(200,100);
    selectLevelButton->setFont(QFont("Arial",16));
    selectLevelButton->move((width()-selectLevelButton->width())/2,height()-selectLevelButton->height()-420);
    connect(selectLevelButton,&QPushButton::clicked,this,&Game::SelectLevel);

    PlayMusic();

    // Create countdown timer

}


void Game::SelectLevel(){

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
        QPushButton* levelButton = new QPushButton("Select Level " + QString::number(i + 1));
        levelButton->setGeometry(sceneWidth / 2 - (3 * selectWidth) / 2 + i * selectWidth, sceneHeight / 2 + selectHeight / 2, selectWidth, 30);
        scene->addWidget(levelButton);

        // Connect the button clicked signal to the slot based on the level
        switch (i) {
        case 0:
            connect(levelButton, &QPushButton::clicked, this, &Game::startLevel1);
            break;
        case 1:
            connect(levelButton, &QPushButton::clicked, this, &Game::startLevel2);
            break;
        case 2:
            connect(levelButton, &QPushButton::clicked, this, &Game::startLevel3);
            break;
        default:
            // Handle an unexpected case, if necessary
            break;
        }
    }


    QPushButton* backButton = new QPushButton("Geri Dön");
                              backButton->setGeometry(sceneWidth / 2 - 200, sceneHeight - 100, 200, 30);
    scene->addWidget(backButton);

    // Connect the button clicked signal to the slot
    connect(backButton, &QPushButton::clicked, this, &Game::goBack);
}


void Game::CharForGame(){
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
    int playerHeight = 100;  // Adjust the height of the gun images

    for (int i = 0; i < 3; ++i) {
        QPixmap playerImage(":image/images/player" + QString::number(i + 1) + ".png");  // Assuming gun images are named gun1.png, gun2.png, etc.
        QGraphicsPixmapItem* playerItem = new QGraphicsPixmapItem(playerImage);
        playerItem->setPos(sceneWidth / 2 - (3 * playerWidth) / 2 + i * playerWidth, sceneHeight / 2 - playerHeight / 2);
        scene->addItem(playerItem);

        // Create a QPushButton for each gun
        QPushButton* gunButton = new QPushButton("Select");
        gunButton->setGeometry(sceneWidth / 2 - (3 * playerWidth) / 2 + i * playerWidth, sceneHeight / 2 + playerHeight / 2, playerWidth, 30);
        scene->addWidget(gunButton);

        // Connect the button clicked signal to the slot
        connect(gunButton, &QPushButton::clicked, this, [this, i]() { onPlayerButtonClicked(i); });
    }

    QPushButton* backButton = new QPushButton("Geri Dön");
                              backButton->setGeometry(sceneWidth / 2 - 200, sceneHeight - 100, 200, 30);
    scene->addWidget(backButton);

    // Connect the button clicked signal to the slot
    connect(backButton, &QPushButton::clicked, this, &Game::goBack);
}


void Game::onPlayerButtonClicked(int playerIndex) {
    // Handle gun selection logic here
    selectedPlayerIndex = playerIndex;
    qDebug() << "Player" << playerIndex + 1 << "selected.";
}


void Game::startLevel1() {
    velocity = 500;
    qDebug() << "Starting Level 1";
    // You can add code here to initialize and set up your game for Level 1
}

void Game::startLevel2() {
    velocity = 200;
    // Implement logic to start level 2
    qDebug() << "Starting Level 2";
    // You can add code here to initialize and set up your game for Level 2
}

void Game::startLevel3() {
    velocity = 50;

    // Implement logic to start level 3
    qDebug() << "Starting Level 3";
    // You can add code here to initialize and set up your game for Level 3
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
    int gunHeight = 100;  // Adjust the height of the gun images

    for (int i = 0; i < 3; ++i) {
        QPixmap gunImage(":image/images/bullet" + QString::number(i + 1) + ".png");  // Assuming gun images are named gun1.png, gun2.png, etc.
        QGraphicsPixmapItem* gunItem = new QGraphicsPixmapItem(gunImage);
        gunItem->setPos(sceneWidth / 2 - (3 * gunWidth) / 2 + i * gunWidth, sceneHeight / 2 - gunHeight / 2);
        scene->addItem(gunItem);

        // Create a QPushButton for each gun
        QPushButton* gunButton = new QPushButton("Select");
        gunButton->setGeometry(sceneWidth / 2 - (3 * gunWidth) / 2 + i * gunWidth, sceneHeight / 2 + gunHeight / 2, gunWidth, 30);
        scene->addWidget(gunButton);

        // Connect the button clicked signal to the slot
        connect(gunButton, &QPushButton::clicked, this, [this, i]() { onGunButtonClicked(i); });
    }

    QPushButton* backButton = new QPushButton("Geri Dön");
                              backButton->setGeometry(sceneWidth / 2 - 100, sceneHeight - 200, 200, 30);
    scene->addWidget(backButton);

    // Connect the button clicked signal to the slot
    connect(backButton, &QPushButton::clicked, this, &Game::goBack);



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



