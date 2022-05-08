#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include "birditem.h"
#include "pillaritem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addBird(int weightm, int height);
    //void startGame();

    bool getGame_on() const;
    void setGame_on(bool newGame_on);
    void incScore();
    void setScore(int newScore);

private:
    QGraphicsItem* background;
    BirdItem* bird;
    PillarItem* pillar_item;
    QTimer* pillar_timer;
    bool game_on;
    int score;
    int best_score;
    QGraphicsPixmapItem* game_over_pix;
    QGraphicsTextItem* score_text_item;
    void setUpPillarTimer();
    void freezeBirdAndPillars();
    void cleanPillars();
    void showGameOverGraphics();
    void hideGameOverGraphics();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
