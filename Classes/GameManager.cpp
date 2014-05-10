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
    figures.resize(1);
    const CCPoint ORIGIN = ADScreen::getOrigin();
    figures[0] = Figure::create(Trapezium,ccp(200,100+ORIGIN.y));
    setSlot(figures[0],ccp(400,400+ORIGIN.y),45);
    //    _figures[1] = Figure::create(Trapezium,ccp(400,300+ORIGIN.y));
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
