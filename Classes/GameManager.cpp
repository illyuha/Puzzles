#include "GameManager.h"
#include <string>
#include <fstream>
#include <algorithm>


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
    int figNum = 6;

    figures.resize(figNum);
    float dx = puzzlePosition.x, dy = puzzlePosition.y;
    CCPoint positions[] = {ccp(150,200), ccp(150,850), ccp(600,850), ccp(600,200), ccp(150,500), ccp(600,500)};
    for (int i = 0; i < figNum; ++i)
    {
        positions[i].x += ORIGIN.x;
        positions[i].y += ORIGIN.y;
    }

    srand(time(NULL));
    int indices[] = {0,1,2,3,4,5};
    random_shuffle(indices,indices+figNum);
    FigureShape ar[] = {Triangle, SmallTrapezium, SmallTrapeziumR, LargeTrapezium, LargeTrapeziumR, KFigure, KFigureR};
    set<FigureShape> shapes(ar,ar+7);

    for (int i = 0; i < 4; ++i)
    {
        string sshape;
        int x, y, angle;
        fin >> sshape >> x >> y >> angle;
        FigureShape shape;
        if (sshape == "Triangle")
            shape = Triangle;
        else if (sshape == "SmallTrapeziumR")
            shape = SmallTrapeziumR;
        else if (sshape == "KFigure")
            shape = KFigure;
        else if (sshape == "LargeTrapezium")
            shape = LargeTrapezium;
        else if (sshape == "SmallTrapezium")
            shape = SmallTrapezium;
        else if (sshape == "KFigureR")
            shape = KFigureR;
        else if (sshape == "LargeTrapeziumR")
            shape = LargeTrapeziumR;
        figures[i] = Figure::create(shape,positions[indices[i]]);
        shapes.erase(shape);
        setSlot(figures[i],ccp(x+dx,y+dy),angle);
    }

    auto it = shapes.begin();
    FigureShape remaining[] = {*it++, *it++, *it};
    random_shuffle(remaining,remaining+shapes.size());
    figures[4] = Figure::create(remaining[0],positions[indices[4]]);
    figures[5] = Figure::create(remaining[2],positions[indices[5]]);

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
