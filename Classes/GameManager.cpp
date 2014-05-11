#include "GameManager.h"
#include <string>
#include <fstream>


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
const int GameManager::LEVELS_NUMBER = 2;

GameManager::GameManager():
    _currentPuzzleNumber(0), _movingFiguresLeft(4)
{
}

GameManager & GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

bool GameManager::prepareNextLevel(Puzzle * & puzzle, vector<Figure *> & figures)
{
    CCLog("Level #%d",_currentPuzzleNumber);
    ++_currentPuzzleNumber;
    _movingFiguresLeft = 4;
    _slots.clear();

    if (_currentPuzzleNumber > LEVELS_NUMBER)
        return false;

    // loading puzzle
    static const CCPoint ORIGIN = ADScreen::getOrigin();
    CCPoint puzzlePosition = ccp(300+ORIGIN.x,100+ORIGIN.y);
    puzzle = Puzzle::create(_currentPuzzleNumber,puzzlePosition);

    // Compiler bug  with to_string()  =(
//    string filename = "game/text/level" + ntos(_currentPuzzleNumber) + ".txt";
    // TODO: avoid hard-coding
    string filename = "D:/Cocos/cocos2d-x/projects/Puzzles/Resources_storage/images-normal/game/text/level"
            + ntos(_currentPuzzleNumber) + ".txt";
    ifstream fin(filename);
    int figNum = 4;

    figures.resize(figNum);
    float dx = puzzlePosition.x, dy = puzzlePosition.y;
    CCPoint positions[] = {ccp(150,200), ccp(150,850), ccp(600,850), ccp(600,200), ccp(200,500), ccp(500,500)};
    for (int i = 0; i < 6; ++i)
    {
        positions[i].x += ORIGIN.x;
        positions[i].y += ORIGIN.y;
    }

    for (int i = 0; i < figNum; ++i)
    {
        string shape;
        int x, y, angle;
        fin >> shape >> x >> y >> angle;
        if (shape == "Triangle")
            figures[i] = Figure::create(Triangle,positions[i]);
        else if (shape == "SmallTrapeziumR")
            figures[i] = Figure::create(SmallTrapeziumR,positions[i]);
        else if (shape == "KFigure")
            figures[i] = Figure::create(KFigure,positions[i]);
        else if (shape == "LargeTrapezium")
            figures[i] = Figure::create(LargeTrapezium,positions[i]);
        // TODO: complete this list...
        setSlot(figures[i],ccp(x+dx,y+dy),angle);
    }

    for (int i = 0; i < figures.size(); ++i)
        figures[i]->setRotationStep(45);

    return true;
}

void GameManager::setSlot(const Figure * const figure, const CCPoint & point, int angle)
{
    _slots[figure] = Slot(angle,point,false);
}

bool GameManager::figureMatchesSlot(const Figure & figure)
{
    Slot * slot = &_slots[&figure];
    bool hit = ((*slot != NON_SLOT &&
            figure.getAngle() == slot->angle &&
            const_cast<Figure &>(figure).getPosition().getDistanceSq(slot->position)
                < ALLOWED_DISTANCE_TO_SLOT * ALLOWED_DISTANCE_TO_SLOT));
    if (hit)
        --_movingFiguresLeft;
    return hit;
}
