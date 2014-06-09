#include "GameScene.h"
#include <ADLib/ADString.h>
#include <algorithm>


//const int GameScene::MAX_DELTA_TOUCH_TIME = 7000;
const float GameScene::MAX_DELTA_TOUCH_DISTANCE = 15;

void GameScene::clearLevel()
{
    _gameManager.clearGameData();
    removeChild(_puzzle);
    for (uint i = 0; i < _figures.size(); ++i)
        removeChild(_figures[i]);
}

void GameScene::prepareLevel()
{
    clearLevel();

    if (_currentLevelNumber > _levelsManager.numberOfLevels())
        return;


    LevelData lvlData = _levelsManager.getLevelData(_currentLevelNumber);

    static const CCPoint ORIGIN = ADScreen::getOrigin();
    static const CCSize VISIBLE_SIZE = ADScreen::getVisibleSize();

    _puzzle = Puzzle::create(_currentLevelNumber,lvlData.puzzle);
    _puzzle->setPosition(ccp(0.5*VISIBLE_SIZE.width+ORIGIN.x,0.5*VISIBLE_SIZE.height+ORIGIN.y));
    _puzzle->setAnchorPoint(ccp(0.5,0.5));

    float scale = 0.5 * VISIBLE_SIZE.width / _puzzle->getContentSize().width;
    scale = min(scale,0.75 * VISIBLE_SIZE.height / _puzzle->getContentSize().height);

    _puzzle->setScale(scale);
    addChild(_puzzle);

    float dx = _puzzle->getPositionX() -
                _puzzle->getAnchorPoint().x * _puzzle->getContentSize().width * _puzzle->getScaleX(),
            dy = _puzzle->getPositionY() -
                _puzzle->getAnchorPoint().y * _puzzle->getContentSize().height * _puzzle->getScaleY();

    CCPoint positions[] = {ccp(0.2,0.25), ccp(0.2,0.5), ccp(0.2,0.75), ccp(0.8,0.75), ccp(0.8,0.5), ccp(0.8,0.2)};
    for (uint i = 0; i < _levelsManager.FIGURES_IN_LEVEL; ++i)
    {
        positions[i].x *= VISIBLE_SIZE.width;
        positions[i].y *= VISIBLE_SIZE.height;
        positions[i].x += ORIGIN.x;
        positions[i].y += ORIGIN.y;
    }

    srand(time(NULL));
    int indices[] = {0,1,2,3,4,5};
    random_shuffle(indices,indices+_levelsManager.FIGURES_IN_PUZZLE);

    _figures.resize(_levelsManager.FIGURES_IN_LEVEL);
    for (uint i = 0; i < _figures.size(); ++i)
    {
        _figures[i] = Figure::create(lvlData.shapes[i]);
        Figure * fig = _figures[i];
        fig->setPosition(positions[indices[i]]);
        fig->setVertices(_gameManager.getShapeVertices(fig->getShape()));
        fig->setScale(scale);
        fig->rotationStep() = 45;
        fig->rotateRandomly();
        addChild(fig);
        if (i < 4) // i.e. if shape is a part of puzzle
        {
            float x = lvlData.puzzle.positions[i].x,
                    y = lvlData.puzzle.positions[i].y,
                    angle = lvlData.puzzle.angles[i];
            _gameManager.setSlot(fig,ccp(x*scale+dx,y*scale+dy),angle);
        }
    }

    ++_currentLevelNumber;
}

GameScene::GameScene(uint initialLevelNumber):
    _firstTouchId(-1),
    _gameManager(GameManager::getInstance()),
    _levelsManager(LevelsManager::getInstance()),
    _currentLevelNumber(initialLevelNumber)
{
}

CCScene * GameScene::scene(uint initialLevelNumber)
{
    // 'scene' is an autorelease object
    CCScene * scene = CCScene::create();

    // 'layer' is an autorelease object
    GameScene * layer = GameScene::create(initialLevelNumber);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene * GameScene::create(uint initialLevelNumber)
{
    GameScene * pRet = new GameScene(initialLevelNumber);
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
    // Q: is it unncecessary?
    _selectedFigure = NULL;

    _gameManager.clearGameData();
    exit(0);
}

void GameScene::onTick(float /*dt*/)
{
    // is this method necessary?
}

bool GameScene::init()
{
    if (!SceneStyle::init())
        return false;

    prepareLevel();

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
        for (uint i = 0; i < _figures.size() && _selectedFigure == NULL; ++i)
        {
           Figure * fig = _figures[i];
           if (fig->movable() && fig->containsPoint(touchLocation))
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
//            const CCPoint ORIGIN = ADScreen::getOrigin();
//            float lx = selRect.getMinX() - _selectedFigure->getAnchorPoint().x * _selectedFigure->getContentSize().width - ORIGIN.x,
//                    by = selRect.getMinY() - _selectedFigure->getAnchorPoint().y * _selectedFigure->getContentSize().height - ORIGIN.y,
//                    rx = selRect.getMaxX() - _selectedFigure->getAnchorPoint().x * _selectedFigure->getContentSize().width - ORIGIN.x,
//                    ty = selRect.getMaxY() - _selectedFigure->getAnchorPoint().y * _selectedFigure->getContentSize().height - ORIGIN.y;
//            if (lx < 0 || by < 0 || rx > ADScreen::getVisibleSize().width || ty > ADScreen::getVisibleSize().height)
//                return;

            // preventing from overlapping
//            for (int i = 0; i < _figures.size(); ++i)
//                // it is allowed to overlap "fixed" figures
//                if (_selectedFigure != _figures[i] && _figures[i]->movable())
//                {
//                    CCRect otherRect(_figures[i]->getPositionX(),
//                                     _figures[i]->getPositionY(),
//                                     _figures[i]->getContentSize().width,
//                                     _figures[i]->getContentSize().height);
//                    if (selRect.intersectsRect(otherRect))
//                        return;
//                }

            // moving figure
            _selectedFigure->setPosition(ccpAdd(_selectedFigure->getPosition(),translation));

            // preventing a figure from moving if it matches the slot
            if (_gameManager.figureMatchesSlot(const_cast<const Figure * const>(_selectedFigure)))
            {
                CCLog("hit");
                // TODO: looks awfully
                _selectedFigure->setPosition(_gameManager.getSlotPosition(*_selectedFigure));
                _selectedFigure->movable() = false;
                _selectedFigure = NULL;
                if (_gameManager.levelComplete())
                {
                    // Q: will it be better if use signals and slots?
                    CCCallFunc* moveCallback = CCCallFunc::create(this, callfunc_selector(GameScene::prepareLevel));
                    CCDelayTime* delayAction = CCDelayTime::create(3.0f);
                    this->runAction(CCSequence::create(delayAction, moveCallback, NULL));
//                    ++_currentLevelNumber;
//                    prepareLevel();
                }
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
