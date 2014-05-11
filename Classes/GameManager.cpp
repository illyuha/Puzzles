#include "GameManager.h"


bool operator==(const GameManager::Slot & a, const GameManager::Slot & b)
{
    return (a.angle == b.angle && a.position.equals(b.position) && a.filled == b.filled);
}

bool operator!=(const GameManager::Slot & a, const GameManager::Slot & b)
{
    return !(a == b);
}

const GameManager::Slot GameManager::NON_SLOT = Slot(21,ccp(-13,-13),false);
const float GameManager::ALLOWED_DISTANCE_TO_SLOT = 10;

GameManager::GameManager()
{
}

GameManager & GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

void GameManager::loadFigures(vector<Figure *> & figures)
{
    figures.resize(4);
    const CCPoint ORIGIN = ADScreen::getOrigin();
    figures[0] = Figure::create(Triangle,ccp(200,200+ORIGIN.y));
    setSlot(figures[0],ccp(300,300+ORIGIN.y),270);
    figures[1] = Figure::create(SmallTrapeziumR,ccp(200,800+ORIGIN.y));
    setSlot(figures[1],ccp(265,337+ORIGIN.y),315);
    figures[2] = Figure::create(KFigure,ccp(500,800+ORIGIN.y));
    setSlot(figures[2],ccp(300,495+ORIGIN.y),270);
    figures[3] = Figure::create(LargeTrapezium,ccp(500,200+ORIGIN.y));
    setSlot(figures[3],ccp(300,688+ORIGIN.y),90);
    for (int i = 0; i < figures.size(); ++i)
        figures[i]->setRotationStep(45);
}

void GameManager::setSlot(const Figure * const figure, const CCPoint & point, int angle)
{
    _slots[figure] = Slot(angle,point,false);
}

bool GameManager::figureMatchesSlot(const Figure & figure)
{
    Slot * slot = &_slots[&figure];
    return (*slot != NON_SLOT &&
            figure.getAngle() == slot->angle &&
            const_cast<Figure &>(figure).getPosition().getDistanceSq(slot->position)
                < ALLOWED_DISTANCE_TO_SLOT * ALLOWED_DISTANCE_TO_SLOT);
}
