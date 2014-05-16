#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <map>
#include <tuple>
#include "cocos2d-A.h"
#include "Figure.h"


class GameManager
{
private:
    // TODO: rename this structure
    struct Slot
    {
        int angle;
        CCPoint position;
        Slot(int a = 0, const CCPoint & p = ccp(0,0)):
            angle(a), position(p)
        {}
    };

    static const Slot NON_SLOT;
    static const float ALLOWED_DISTANCE_TO_SLOT;
    static const int LEVELS_NUMBER;

    map< const Figure * const, Slot > _slots;
    int _movingFiguresLeft;

    GameManager();

public:
    friend bool operator==(const GameManager::Slot &, const GameManager::Slot &);
    friend bool operator!=(const GameManager::Slot &, const GameManager::Slot &);

    // Q: or pointer?
    static GameManager & getInstance();

    // TODO: find out why this works (and why Point*-argument does not)
    // TODO: try without bool
    bool figureMatchesSlot(const Figure * const);    
    void clearGameData();
    void setSlot(const Figure * const, const CCPoint &, int);
    vector<CCPoint> getShapeVertices(const FigureShape &) const;

    const CCPoint & getSlotPosition(const Figure & figure)
    {
        return _slots[&figure].position;
    }

    bool levelComplete() const
    {
        return (_movingFiguresLeft == 0);
    }

};

bool operator==(const GameManager::Slot & a, const GameManager::Slot & b);

bool operator!=(const GameManager::Slot & a, const GameManager::Slot & b);

#endif // GAMEMANAGER_H
