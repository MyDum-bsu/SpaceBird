#include "scene.h"
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent), game_on(true), score(0), best_score(0)
{
    background = new QGraphicsPixmapItem(QPixmap(":/images/space.jpg"));
    addItem(background);
    pillar_item = new PillarItem;
    addItem(pillar_item);
    setUpPillarTimer();
}

void Scene::addBird(int width, int height)
{
    bird = new BirdItem(QPixmap(":/images/redbird-upflap.png"));
    bird->setPos(width, height);
    addItem(bird);
}

bool Scene::getGame_on() const
{
    return game_on;
}

void Scene::setGame_on(bool newGame_on)
{
    game_on = newGame_on;
}

//void Scene::startGame()
//{
//    bird->startFlying();
//    if (!pillar_timer->isActive()) {
//          cleanPillars();
//          setScore(0);
//          setGame_on(true);
//        pillar_timer->start(5000);
//    }
//}

void Scene::keyPressEvent(QKeyEvent *event)
 {
    if (event->key() == Qt::Key_Space) {
        if(game_on) {
        bird->shootUp();
        }
    }
     QGraphicsScene::keyPressEvent(event);
}

void Scene::setUpPillarTimer() {
    pillar_timer = new QTimer(this);
    connect(pillar_timer, &QTimer::timeout, [=]() {
        PillarItem* pillar_item = new PillarItem();
        connect(pillar_item, &PillarItem::collideFail, [=](){
            pillar_timer->stop();
            freezeBirdAndPillars();
            setGame_on(false);
            showGameOverGraphics();
        });
        addItem(pillar_item);
    });
    pillar_timer->start(1000);
}

void Scene::freezeBirdAndPillars()
{
    bird->freezeInPlace();

    QList<QGraphicsItem*> scene_item = items();
    foreach(QGraphicsItem* item, scene_item) {
        PillarItem* pillar = dynamic_cast<PillarItem*>(item);
        if(pillar) {
            pillar->freezeInPlace();
        }
    }
}


void Scene::cleanPillars()
{
    QList<QGraphicsItem*> scene_item = items();
    foreach(QGraphicsItem* item, scene_item) {
        PillarItem* pillar = dynamic_cast<PillarItem*>(item);
        if(pillar) {
            removeItem(pillar);
            delete pillar;
        }
    }
}

void Scene::showGameOverGraphics()
{
    game_over_pix = new QGraphicsPixmapItem(QPixmap(":/images/gameover.png"));
    addItem(game_over_pix);
    game_over_pix->setPos(QPoint(570,330) - QPoint(game_over_pix->boundingRect().width() / 2,
                                               game_over_pix->boundingRect().height() / 2));
    score_text_item = new QGraphicsTextItem();
    QString htmlString = "<p> Score : " + QString::number(score) + "</p>"
            + "<p> Best Score : " + QString::number(best_score) + "</p>";
    QFont mFont("Consolas", 30, QFont::Bold);
    score_text_item->setHtml(htmlString);
    score_text_item->setFont(mFont);
    score_text_item->setDefaultTextColor(Qt::yellow);
    addItem(score_text_item);
    score_text_item->setPos(QPoint(300,400) + QPoint(score_text_item->boundingRect().width() / 2,
                                               -game_over_pix->boundingRect().height() / 2));
}

void Scene::hideGameOverGraphics()
{
    if(game_over_pix) {
        removeItem(game_over_pix);
        delete game_over_pix;
        game_over_pix = nullptr;
    }
    if(score_text_item) {
        removeItem(score_text_item);
        delete score_text_item;
        score_text_item = nullptr;
    }
}

void Scene::incScore()
{
    score++;
    if (score > best_score) {
        best_score = score;
    }
    qDebug() << "Score: " << score << " Best score: " << best_score;
}

void Scene::setScore(int newScore)
{
    score = newScore;
}
