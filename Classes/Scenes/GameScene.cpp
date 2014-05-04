#include "GameScene.h"
#include <ADLib/ADString.h>

GameScene::GameScene()
{
}

CCScene * GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene * scene = CCScene::create();

    // 'layer' is an autorelease object
    GameScene * layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene * GameScene::create()
{
    GameScene * pRet = new GameScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void GameScene::onBackClick()
{
    // TODO: find out what to do
}

bool GameScene::init()
{
    if (!SceneStyle::init())
        return false;

    // Get the screen start of cordinates
    const CCPoint ORIGIN = ADScreen::getOrigin();
    const CCSize VISIBLE_SIZE = ADScreen::getVisibleSize();

    _figure = Figure::create(ORIGIN + VISIBLE_SIZE*0.5f);
//    _figure->setAnchorPoint(ccp(0.5,0.5));
    addChild(_figure);

    //setTouchEnabled(true);

    return true;
}

