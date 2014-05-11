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

GameManager::GameManager():
    _currentPuzzleNumber(0)
{
}

GameManager & GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

// NB: this method must be invoked after loadNextPuzzle()
void GameManager::loadFigures(vector<Figure *> & figures)
{
    // TODO: read positions from file
    figures.resize(4);
//    static const CCPoint ORIGIN = ADScreen::getOrigin();
    float dx = _puzzlePosition.x, dy = _puzzlePosition.y;
    figures[0] = Figure::create(Triangle,ccp(200,200));
    setSlot(figures[0],ccp(50+dx,51+dy),270);
    figures[1] = Figure::create(SmallTrapeziumR,ccp(200,800));
    setSlot(figures[1],ccp(15+dx,88+dy),315);
    figures[2] = Figure::create(KFigure,ccp(500,800));
    setSlot(figures[2],ccp(50+dx,246+dy),270);
    figures[3] = Figure::create(LargeTrapezium,ccp(500,200));
    setSlot(figures[3],ccp(50+dx,438+dy),90);
    for (int i = 0; i < figures.size(); ++i)
        figures[i]->setRotationStep(45);
}

void GameManager::loadNextPuzzle(Puzzle * & puzzle)
{
    static const CCPoint ORIGIN = ADScreen::getOrigin();
    _puzzlePosition = ccp(300+ORIGIN.x,100+ORIGIN.y);
    puzzle = Puzzle::create(++_currentPuzzleNumber,_puzzlePosition);
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
