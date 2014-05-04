#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "SceneStyle.h"
#include "cocos2d-A.h"
#include "Figure.h"

using namespace cocos2d;

class GameScene: public SceneStyle
{
private:
    Figure * _figure;
    bool init();
    void onBackClick();

public:
    GameScene();
    static CCScene * scene();
    static GameScene * create();
};

#endif // GAMESCENE_H
