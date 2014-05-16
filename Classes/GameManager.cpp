#include "GameManager.h"
#include <fstream>
#include <algorithm>
#define SQRT2 sqrt(2)


bool operator==(const GameManager::Slot & a, const GameManager::Slot & b)
{
    return (a.angle == b.angle && a.position.equals(b.position)/* && a.filled == b.filled*/);
}

bool operator!=(const GameManager::Slot & a, const GameManager::Slot & b)
{
    return !(a == b);
}

const GameManager::Slot GameManager::NON_SLOT = Slot(21,ccp(-13,-13)/*,false*/);
const float GameManager::ALLOWED_DISTANCE_TO_SLOT = 10;
const int GameManager::LEVELS_NUMBER = 2;

GameManager::GameManager():
    _movingFiguresLeft(4)
{
}

GameManager & GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

vector<CCPoint> GameManager::getShapeVertices(const FigureShape & shape) const
{
    vector<CCPoint> vertices;
    switch (shape)
    {
    case SmallTrapezium:
    {
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(100*SQRT2-100,100), ccp(100*SQRT2,0)};
        vertices = vector<CCPoint>(v,v+4);
    }
        break;
    case Triangle:
    {
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(100,0)};
        vertices = vector<CCPoint>(v,v+3);
    }
        break;
    case LargeTrapezium:
    {
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(200,100), ccp(300,0)};
        vertices = vector<CCPoint>(v,v+4);
    }
        break;
    case KFigure:
    {
        CCPoint v[] = {ccp(0,0), ccp(50*SQRT2,50*SQRT2), ccp(100-50*SQRT2,100), ccp(100+50*SQRT2,100), ccp(200+50*SQRT2,0)};
        vertices = vector<CCPoint>(v,v+5);
    }
        break;
    case SmallTrapeziumR:
    {
        CCPoint v[] = {ccp(0,0), ccp(100,100), ccp(100*SQRT2,100), ccp(100*SQRT2,0)};
        vertices = vector<CCPoint>(v,v+4);
    }
    case KFigureR:
    {
        CCPoint v[] = {ccp(0,0), ccp(100,100), ccp(100+100*SQRT2,100), ccp(150*SQRT2,50*SQRT2), ccp(200*SQRT2,0)};
        vertices = vector<CCPoint>(v,v+5);
    }
        break;
    case LargeTrapeziumR:
    {
        CCPoint v[] = {ccp(0,0), ccp(100,100), ccp(300,100), ccp(300,0)};
        vertices = vector<CCPoint>(v,v+4);
    }
        break;
    }
    return vertices;
}

void GameManager::setSlot(const Figure * const figure, const CCPoint & point, int angle)
{
    _slots[figure] = Slot(angle,point/*,false*/);
}

bool GameManager::figureMatchesSlot(const Figure * const figure)
{
    Slot * slot = &_slots[figure];
    bool hit = ((*slot != NON_SLOT &&
            figure->getAngle() == slot->angle &&
            const_cast<Figure *>(figure)->getPosition().getDistanceSq(slot->position)
                < ALLOWED_DISTANCE_TO_SLOT * ALLOWED_DISTANCE_TO_SLOT));
    if (hit)
        --_movingFiguresLeft;
    return hit;
}

void GameManager::clearGameData()
{
    _slots.clear();
    _movingFiguresLeft = 4;
}
