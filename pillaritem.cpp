#include "pillaritem.h"
#include "qdebug.h"
#include "qgraphicsscene.h"
#include "scene.h"
PillarItem::PillarItem() :
          top_pillar(new QGraphicsPixmapItem(QPixmap(":/images/full pipe top.png"))),
          bottom_pillar(new QGraphicsPixmapItem(QPixmap(":/images/full pipe bottom.png"))),
          past_bird(0)
{
    top_pillar->setPos(QPointF(1114,0) - QPointF(top_pillar->boundingRect().width()/2, top_pillar->boundingRect().height()/2 + 285));

    bottom_pillar->setPos(QPointF(1114,0) + QPointF(-bottom_pillar->boundingRect().width()/2, 285));
    addToGroup(top_pillar);
    addToGroup(bottom_pillar);

    y_pos = QRandomGenerator::global()->bounded(350);
    int x_randomizer = QRandomGenerator::global()->bounded(300);
    setPos(QPoint(0,0) + QPoint(560 + x_randomizer, y_pos));

    x_animation = new QPropertyAnimation(this, "x", this);
    x_animation->setStartValue(600);
    x_animation->setEndValue(-1154);
    x_animation->setEasingCurve(QEasingCurve::Linear);
    x_animation->setDuration(5000);
    connect(x_animation, &QPropertyAnimation::finished,[=](){
         scene()->removeItem(this);
         delete this;
    });
    x_animation->start();

}

//PillarItem::~PillarItem()
//{
//    delete top_pillar;
//    delete bottom_pillar;
//}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal newX)
{
    m_x = newX;

    if(newX < 0 && !past_bird) {
        past_bird = true;
        QGraphicsScene* mScene = scene();
        Scene* myScene = dynamic_cast<Scene*>(mScene);
        if(myScene) {
            myScene->incScore();
        }
    }

    if(collidesWithBird()) {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPoint(newX, y_pos));
}

void PillarItem::freezeInPlace()
{
    x_animation->stop();
}



bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem*> colliding_items = top_pillar->collidingItems();
    colliding_items.append(bottom_pillar->collidingItems());
    foreach (QGraphicsItem* item, colliding_items) {
        BirdItem* bird_item = dynamic_cast<BirdItem*>(item);
        if(bird_item) {
            return true;
        }
    }
    return false;
}
