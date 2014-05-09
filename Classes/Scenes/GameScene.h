#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "SceneStyle.h"
#include "cocos2d-A.h"
#include "Figure.h"
#include <vector>
//#define PTM_RATIO 32.0 // Q: is it necessary?


using namespace cocos2d;

class GameScene: public SceneStyle
{
private:
    vector<Figure *> _figures;
    Figure * _selectedFigure;

    GameScene();
    bool init();
    void onBackClick();
    void onTick(float);
    bool ccTouchBegan(CCTouch *, CCEvent *);
    void ccTouchMoved(CCTouch *, CCEvent *);
    void ccTouchEnded(CCTouch *, CCEvent *);
    void initFigures();

public:
    static CCScene * scene();
    static GameScene * create();
};

#endif // GAMESCENE_H
