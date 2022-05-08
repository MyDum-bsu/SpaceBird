#include "birditem.h"
#include <QDebug>
BirdItem::BirdItem(QPixmap pixmap) : wing_position(WingPosition::kMiddle), wing_direction(0)
{
    setPixmap(pixmap);
    QTimer* bird_wing_timer = new QTimer;
    connect(bird_wing_timer, &QTimer::timeout, [=]() {
            this->updatePixmap();
        });
    bird_wing_timer->start(100);
    ground_position = scenePos().y() + 290;

    y_animation = new QPropertyAnimation(this, "y", this);
    y_animation->setStartValue(scenePos().y());
    y_animation->setEndValue(ground_position);
    y_animation->setEasingCurve(QEasingCurve::InQuad);
    y_animation->setDuration(800);
    y_animation->start();
}

void BirdItem::updatePixmap()
{
    if (wing_position == WingPosition::kMiddle) {
        if (wing_direction) {
            setPixmap(QPixmap(":/images/redbird-upflap.png"));
            wing_position = WingPosition::kUp;
            wing_direction = 0;
        } else {
            setPixmap(QPixmap(":/images/redbird-downflap.png"));
            wing_position = WingPosition::kDown;
            wing_direction = 1;
        }
    } else {
        setPixmap(QPixmap(":/images/redbird-midflap.png"));
        wing_position = WingPosition::kMiddle;
    }

}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::shootUp()
{
    y_animation->stop();
    qreal cur_pos_y = y();
    y_animation->setStartValue(cur_pos_y);
    y_animation->setEndValue(cur_pos_y - scene()->sceneRect().height() / 8);
    y_animation->setEasingCurve(QEasingCurve::OutQuad);
    y_animation->setDuration(285);
    connect(y_animation, &QPropertyAnimation::finished,[=](){
        fallToGroundIdNecessary();
    });
    y_animation->start();
}

void BirdItem::freezeInPlace()
{
    y_animation->stop();
}

//void BirdItem::startFlying()
//{
//    y_animation->start();
//}

void BirdItem::setY(qreal newY)
{
    moveBy(0,newY - m_y);
    m_y = newY;
}
void BirdItem::fallToGroundIdNecessary()
{
        if (y() < ground_position) {
            y_animation->stop();
            y_animation->setStartValue(y());
            y_animation->setEasingCurve(QEasingCurve::InQuad);
            y_animation->setEndValue(ground_position);
            y_animation->setDuration(1000);
            y_animation->start();
        }

}


