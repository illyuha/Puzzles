#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "SceneStyle.h"
#include "cocos2d-A.h"
#include "Figure.h"
#include <vector>
#include "GameManager.h"
#include "Puzzle.h"
#include "LevelsManager.h"


class GameScene: public SceneStyle
{
private:
    Puzzle * _puzzle;
    vector<Figure *> _figures;
    Figure * _selectedFigure;
    int _firstTouchId;
//    int _firstTouchTime;
    CCPoint _firstTouchPosition;
    GameManager & _gameManager;
    LevelsManager & _levelsManager;
    uint _currentLevelNumber;

//    static const int MAX_DELTA_TOUCH_TIME;
    static const float MAX_DELTA_TOUCH_DISTANCE;

    GameScene(uint);
    bool init();
    void onBackClick();
    void onTick(float);
    bool ccTouchBegan(CCTouch *, CCEvent *);
    void ccTouchMoved(CCTouch *, CCEvent *);
    void ccTouchEnded(CCTouch *, CCEvent *);
    void clearLevel();
    void prepareLevel();
    // TODO: clear all _gameManager's data

public:
    static CCScene * scene(uint);
    static GameScene * create(uint);
};

#endif // GAMESCENE_H
