#include "MainMenuScene.h"
#include <ADLib/ADString.h>

using namespace cocos2d;

MainMenuScene::MainMenuScene()
{
}

CCScene* MainMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    MainMenuScene *layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


MainMenuScene * MainMenuScene::create()
{

    MainMenuScene *pRet = new MainMenuScene();
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

void MainMenuScene::onBackClick()
{
    CCLog("Back clicked");
}

bool MainMenuScene::init()
{
    if(!SceneStyle::init())
        return false;

    //ADSoundManager::playMusic(GameInfo::MENU_MUSIC);

    //Get the screen start of cordinates
    const CCPoint ORIGIN = ADScreen::getOrigin();
    const CCSize VISIBLE_SIZE = ADScreen::getVisibleSize();

//    CCSprite* logo = CCSprite::create("main-menu/facebook_logo.png");

//    logo->setPosition(ORIGIN + VISIBLE_SIZE*0.5f);
//    this->addChild(logo);

    return true;
}


