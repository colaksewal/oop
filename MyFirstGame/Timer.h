#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>

class Timer : public QGraphicsTextItem {
    Q_OBJECT
public:
    Timer(QGraphicsItem *parent = nullptr);
    void decrease();
    int getTime();


protected:
    void timerEvent(QTimerEvent *event) override;

signals:
    void timeExpired();

private:
    int timeCount;
    int timerId;  // Added member variable to store the timer ID
};

#endif // TIMER_H

