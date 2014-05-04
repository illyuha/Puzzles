#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "cocos2d-A.h"
#include "SceneStyle.h"

class MainMenuScene: public SceneStyle
{
public:
    MainMenuScene();
    static cocos2d::CCScene* scene();
    static MainMenuScene* create();

private:
    bool init();
    void onBackClick();
};

#endif // MAINSCENE_H
