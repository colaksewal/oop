#include "Timer.h"
#include <QTimer>
#include <QFont>
#include "Game.h"
#include <QMessageBox>


extern Game *game;

Timer::Timer(QGraphicsItem *parent) : QGraphicsTextItem(parent) {
    timeCount = 60;
    setPlainText(QString("Countdown: ") + QString::number(timeCount));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 20));
    timerId = startTimer(1000);  // Store the timer ID
}


void Timer::timerEvent(QTimerEvent *event) {
    decrease();
}


void Timer::decrease() {
    if (timeCount > 0) {
        timeCount--;
        setPlainText(QString("Countdown: ") + QString::number(timeCount));
        if(timeCount == 0){
            QMessageBox::information(nullptr, "Game Over", "Congrulations.You win");
            game->gameOver();
            emit timeExpired();
            killTimer(timerId);
        }
    }
}


int Timer::getTime() {
    return timeCount;
}
