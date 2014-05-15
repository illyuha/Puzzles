#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <map>
#include <tuple>
#include "cocos2d-A.h"
#include "Figure.h"
#include "Puzzle.h"


class GameManager
{
private:
    struct Slot
    {
        int angle;
        CCPoint position;
        // Q: is filled ever used?
        bool filled;
        Slot(int a = 0, const CCPoint & p = ccp(0,0), bool f = false):
            angle(a), position(p), filled(f)
        {}
    };

    static const Slot NON_SLOT;
    static const float ALLOWED_DISTANCE_TO_SLOT;
    static const int LEVELS_NUMBER;

    map< const Figure * const, Slot > _slots;
    // NB: not the best name for class field
    int _currentPuzzleNumber;
    int _movingFiguresLeft;

    GameManager();
    void setSlot(const Figure * const, const CCPoint &, int);

public:
    friend bool operator==(const GameManager::Slot &, const GameManager::Slot &);
    friend bool operator!=(const GameManager::Slot &, const GameManager::Slot &);

    static GameManager & getInstance();

    // TODO: find out why this works (and why Point*-argument does not)
    // TODOL try without bool
    bool prepareNextLevel(Puzzle * & puzzle, vector<Figure *> & figures);
    bool figureMatchesSlot(const Figure * const);

    const CCPoint & getSlotPosition(const Figure & figure)
    {
        return _slots[&figure].position;
    }

    bool levelComplete() const
    {
        return (_movingFiguresLeft == 0);
    }

//    bool gameFinished() const
//    {
//        return (_currentPuzzleNumber > LEVELS_NUMBER);
//    }

};

bool operator==(const GameManager::Slot & a, const GameManager::Slot & b);

bool operator!=(const GameManager::Slot & a, const GameManager::Slot & b);

#endif // GAMEMANAGER_H
