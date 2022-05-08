#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include "birditem.h"
class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
   // ~PillarItem();
    qreal x() const;
    void setX(qreal newX);
    void freezeInPlace();

signals:
    void collideFail();
private:
    QGraphicsPixmapItem* top_pillar;
    QGraphicsPixmapItem* bottom_pillar;
    QPropertyAnimation* x_animation;
    qreal m_x;
    int y_pos;
    bool collidesWithBird();
    bool past_bird;
};


#endif // PILLARITEM_H
