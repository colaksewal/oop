#ifndef SCORE_H
#define SCORE_H

#include<QGraphicsTextItem>

class Score : public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent = 0);
    void increase();
    void increase1();
    int getScore();
private:
    int score;

};

#endif // SCORE_H
