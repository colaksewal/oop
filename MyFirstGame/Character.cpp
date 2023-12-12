#include "Character.h"

Character::Character(const QString& imagePath, QGraphicsItem *parent) 
    : QObject(), QGraphicsPixmapItem(parent), characterName("") {
    setPixmap(QPixmap(imagePath));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

Character::~Character() {
    // Cleanup, if needed
}

void Character::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // Emit signal when the character is selected
    emit characterSelected(characterName);
    QGraphicsPixmapItem::mousePressEvent(event);
}
