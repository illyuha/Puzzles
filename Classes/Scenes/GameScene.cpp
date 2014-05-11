#include "GameScene.h"
#include <ADLib/ADString.h>

//const int GameScene::MAX_DELTA_TOUCH_TIME = 7000;
const float GameScene::MAX_DELTA_TOUCH_DISTANCE = 15;

void GameScene::initFigures()
{
    _gameManager.loadFigures(_figures);
    for (int i = 0; i < _figures.size(); ++i)
        addChild(_figures[i]);
}

void GameScene::initPuzzle()
{
    _gameManager.loadNextPuzzle(_puzzle);
    addChild(_puzzle);
}

GameScene::GameScene():
    _firstTouchId(-1), _gameManager(GameManager::getInstance())
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

    initPuzzle();
    initFigures();

    // TODO: return false if something wrong happens

//    schedule(schedule_selector(GameScene::onTick));

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

    return true;
}

bool GameScene::ccTouchBegan(CCTouch * touch, CCEvent *)
{
//    if (_firstTouchId == -1)
    {
        CCPoint touchLocation = touch->getLocation();
        _selectedFigure = NULL;
        for (int i = 0; i < _figures.size() && _selectedFigure == NULL; ++i)
        {
           Figure * fig = _figures[i];
           CCRect r(fig->boundingBox());
           if (fig->movable() && fig->/*boundingBox().*/containsPoint(touchLocation))
               _selectedFigure = fig;
        }
        if (_selectedFigure != NULL)
        {
//            _firstTouchTime = f();
            _firstTouchId = touch->getID();
            _firstTouchPosition = touchLocation;
            return true;
        }
        else
        {
//            _firstTouchTime = 0;
            _firstTouchId = -1;
            _firstTouchPosition = ccp(-1,-1);
            return false;
        }
    }
//    else
//    {
//        return true;
//    }
}

void GameScene::ccTouchMoved(CCTouch * touch, CCEvent *)
{
//    if (_firstTouchId == touch->getID())
    {
        if (_selectedFigure != NULL)
        {
            CCPoint touchLocation = convertTouchToNodeSpace(touch);

            // Q: is it a good decision?
            // if the touch position is outside of the rectangle
//            if (!_selectedFigure->boundingBox().containsPoint(touchLocation))
//            {
                // or call ccTouchEnded?
//              _selectedFigure = NULL; // or just return?
//                return;
//            }

            // calculating length of movement
            CCPoint prevTouchLocation = convertToNodeSpace(touch->getPreviousLocation());
            CCPoint translation = ccpSub(touchLocation,prevTouchLocation);
            CCRect selRect(_selectedFigure->getPositionX()+translation.x,
                     _selectedFigure->getPositionY()+translation.y,
                     _selectedFigure->getContentSize().width,
                     _selectedFigure->getContentSize().height);

            // preventing from moving image outside of screen
            const CCPoint ORIGIN = ADScreen::getOrigin();
            float lx = selRect.getMinX() - _selectedFigure->getAnchorPoint().x * _selectedFigure->getContentSize().width - ORIGIN.x,
                    by = selRect.getMinY() - _selectedFigure->getAnchorPoint().y * _selectedFigure->getContentSize().height - ORIGIN.y,
                    rx = selRect.getMaxX() - _selectedFigure->getAnchorPoint().x * _selectedFigure->getContentSize().width - ORIGIN.x,
                    ty = selRect.getMaxY() - _selectedFigure->getAnchorPoint().y * _selectedFigure->getContentSize().height - ORIGIN.y;
            if (lx < 0 || by < 0 || rx > ADScreen::getVisibleSize().width || ty > ADScreen::getVisibleSize().height)
                return;

            // preventing from overlapping
            for (int i = 0; i < _figures.size(); ++i)
                // it is allowed to overlap "fixed" figures
                if (_selectedFigure != _figures[i] && _figures[i]->movable())
                {
                    CCRect otherRect(_figures[i]->getPositionX(),
                                     _figures[i]->getPositionY(),
                                     _figures[i]->getContentSize().width,
                                     _figures[i]->getContentSize().height);
                    if (selRect.intersectsRect(otherRect))
                        return;
                }

            // moving figure
            _selectedFigure->setPosition(ccpAdd(_selectedFigure->getPosition(),translation));
            CCLog("%f %f",_selectedFigure->getPositionX(),_selectedFigure->getPositionY());

            // preventing a figure from moving if it matches the slot
            if (_gameManager.figureMatchesSlot(*_selectedFigure))
            {
                CCLog("hit");
                _selectedFigure->setPosition(_gameManager.getSlotPosition(*_selectedFigure));
                _selectedFigure->movable() = false;
                _selectedFigure = NULL;
            }
        }
    }
//    else
//    {

//    }
}

void GameScene::ccTouchEnded(CCTouch * touch, CCEvent *)
{
    if (_selectedFigure != NULL)
    {
        CCPoint touchLocation = touch->getLocation();
        // TODO: check some deltaTime value
        if (touchLocation.getDistanceSq(_firstTouchPosition) < MAX_DELTA_TOUCH_DISTANCE * MAX_DELTA_TOUCH_DISTANCE)
            _selectedFigure->rotate();
    }
}
