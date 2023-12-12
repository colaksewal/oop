#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class Character : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Character(const QString& imagePath, QGraphicsItem *parent = nullptr);
    ~Character();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void characterSelected(const QString& characterName);

private:
    QString characterName;
};

#endif // CHARACTER_H
