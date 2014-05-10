#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <map>
#include <tuple>
#include "cocos2d-A.h"
#include "Figure.h"


using namespace std;

class GameManager
{
private:
    struct Slot
    {
        int angle;
        CCPoint position;
        bool filled;
        Slot(int a = 0, const CCPoint & p = ccp(0,0), bool f = false):
            angle(a), position(p), filled(f)
        {}
    };

    static const Slot NON_SLOT;
    static const float ALLOWED_DISTANCE_TO_SLOT;

    map<const Figure * const, Slot > _slots;

    GameManager();
    void setSlot(const Figure * const, const CCPoint &, int);

public:
    friend bool operator==(const GameManager::Slot &, const GameManager::Slot &);
    friend bool operator!=(const GameManager::Slot &, const GameManager::Slot &);

    static GameManager & getInstance();

    void loadFigures(vector<Figure *> &);
    bool figureMatchesSlot(const Figure &);

    CCPoint getSlotPosition(const Figure & figure)
    {
        return _slots[&figure].position;
    }

};

bool operator==(const GameManager::Slot & a, const GameManager::Slot & b);

bool operator!=(const GameManager::Slot & a, const GameManager::Slot & b);

#endif // GAMEMANAGER_H
