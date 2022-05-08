#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsScene>

class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit BirdItem(QPixmap);
    qreal y() const;
    void shootUp();
    void freezeInPlace();
    //void startFlying();
public slots:
    void setY(qreal newY);
    void fallToGroundIdNecessary();
private:
    void updatePixmap();
    enum class WingPosition {
            kUp,
            kMiddle,
            kDown
        };
    WingPosition wing_position;
    bool wing_direction;
    qreal m_y;
    QPropertyAnimation* y_animation;
    qreal ground_position;
};

#endif // BIRDITEM_H
