#include "GameScene.h"
#include <ADLib/ADString.h>


void GameScene::initFigures()
{
    _figures.resize(2);
    const CCPoint ORIGIN = ADScreen::getOrigin();
    _figures[0] = Figure::create(Trapezium,ccp(200,100+ORIGIN.y));
    _figures[1] = Figure::create(Trapezium,ccp(400,300+ORIGIN.y));
    for (int i = 0; i < _figures.size(); ++i)
        addChild(_figures[i]);
}

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
    // seems that it is unncecessary
    _selectedFigure = NULL;
}

void GameScene::onTick(float dt)
{
    // is this method necessary?
}

bool GameScene::init()
{
    if (!SceneStyle::init())
        return false;

    initFigures();

    // TODO: return false if something wrong happens


//    schedule(schedule_selector(GameScene::onTick));

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

    return true;
}

bool GameScene::ccTouchBegan(CCTouch * touch, CCEvent *)
{
    CCPoint touchLocation = touch->getLocation();
    _selectedFigure = NULL;
    for (int i = 0; i < _figures.size() && _selectedFigure == NULL; ++i)
    {
       Figure * fig = _figures[i];
       if (fig->boundingBox().containsPoint(touchLocation))
           _selectedFigure = fig;
    }
    return (_selectedFigure != NULL);
}

void GameScene::ccTouchMoved(CCTouch * touch, CCEvent *)
{
    if (_selectedFigure != NULL)
    {
        CCPoint touchLocation = convertTouchToNodeSpace(touch);

        // Q: is it a good decision?
        ///
        if (!_selectedFigure->boundingBox().containsPoint(touchLocation))
        {
            // or call ccTouchEnded?
//            _selectedFigure = NULL; // or just return?
            return;
        }
        ///

        CCPoint prevTouchLocation = convertToNodeSpace(touch->getPreviousLocation());
        CCPoint translation = ccpSub(touchLocation,prevTouchLocation);
        CCRect selRect(_selectedFigure->getPositionX()+translation.x,
                 _selectedFigure->getPositionY()+translation.y,
                 _selectedFigure->getContentSize().width,
                 _selectedFigure->getContentSize().height);

        const CCPoint ORIGIN = ADScreen::getOrigin();
        float lx = selRect.getMinX() - _selectedFigure->getAnchorPoint().x * _selectedFigure->getContentSize().width - ORIGIN.x,
                by = selRect.getMinY() - _selectedFigure->getAnchorPoint().y * _selectedFigure->getContentSize().height - ORIGIN.y,
                rx = selRect.getMaxX() - _selectedFigure->getAnchorPoint().x * _selectedFigure->getContentSize().width - ORIGIN.x,
                ty = selRect.getMaxY() - _selectedFigure->getAnchorPoint().y * _selectedFigure->getContentSize().height - ORIGIN.y;
        if (lx < 0 || by < 0 || rx > ADScreen::getVisibleSize().width || ty > ADScreen::getVisibleSize().height)
            return;

        for (int i = 0; i < _figures.size(); ++i)
            if (_selectedFigure != _figures[i])
            {
                CCRect otherRect(_figures[i]->getPositionX(),
                                 _figures[i]->getPositionY(),
                                 _figures[i]->getContentSize().width,
                                 _figures[i]->getContentSize().height);
                if (selRect.intersectsRect(otherRect))
                    return;
            }

         _selectedFigure->setPosition(ccpAdd(_selectedFigure->getPosition(),translation));
    }

}

void GameScene::ccTouchEnded(CCTouch * touch, CCEvent *)
{
}
