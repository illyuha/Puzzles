#include "Figure.h"
#include <ADLib.h>

Figure::Figure(const CCPoint & startPos)
{
    setAnchorPoint(ccp(0.5,0.5));
    setPosition(startPos);
    drawImage();
    setContentSize(_image->getContentSize());
    float szh = _image->getContentSize().height, szw = _image->getContentSize().width;
    szh = getContentSize().height * getScaleY();
    szw = getContentSize().height * getScaleX();
    startTrackingTouch();
}

Figure::~Figure()
{
    stopTrackingTouch();
}

Figure * Figure::create(const CCPoint & startPos)
{
    Figure * fig = new Figure(startPos);
    if (fig != NULL)
        fig->autorelease();
    return fig;
}

void Figure::drawImage()
{
    _image = CCSprite::create("game/figure1.png");
//    _image->setAnchorPoint(ccp(0.5,0.5));
    _image->setAnchorPoint(ccp(0,0));
    float posx = _image->getPositionX(), posy = _image->getPositionY();
    std::swap(posx,posy);
    std::swap(posx,posy);
    addChild(_image);
}

// not a member function yet
//bool touchHitsFigure(const CCPoint & touchLocation,  CCNode * const image)
//{
//    // Q: Can I prevent the next line of code from executing at compile time using exactly pointers?
//    //image->setPosition(ccp(0,0));
//    // assuming the anchor point of the CCNode is in its centre
//    float ancx = image->getAnchorPoint().x, ancy = image->getAnchorPoint().y;
//    float lx = image->getPositionX() - ancx * image->getContentSize().width,
//            rx = image->getPositionX() + (1.0 - ancx) * image->getContentSize().width,
//            uy = image->getPositionY() - ancy * image->getContentSize().height,
//            dy = image->getPositionY() + (1.0 - ancy) * image->getContentSize().height,
//            x = touchLocation.x, y = touchLocation.y;
//    CCLog("lx:%f x:%f rx:%f\nuy:%f y:%f dy:%f",lx,x,rx,uy,y,dy);
//    return (lx <= x && x <= rx && uy <= y && y <= dy);
//}

bool Figure::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
//    CCLog("began: %f %f",getAnchorPoint().x,getAnchorPoint().y);
//    CCLog("touch: %f %f",pTouch->getLocation().x,pTouch->getLocation().y);

    auto touchLocation = pTouch->getLocation();
    float ancx = getAnchorPoint().x, ancy = getAnchorPoint().y;
    float lx = getPositionX() - ancx * getContentSize().width,
            rx = getPositionX() + (1.0 - ancx) * getContentSize().width,
            dy = getPositionY() - ancy * getContentSize().height,
            uy = getPositionY() + (1.0 - ancy) * getContentSize().height,
            x = touchLocation.x, y = touchLocation.y;

//    CCLog("y: %f %f %f",dy,y,uy);
//    CCLog("x: %f %f %f",lx,x,rx);

    //if (touchHitsFigure(pTouch->getLocation(),this))
    if (lx <= x && x <= rx && dy <= y && y <= uy)
    {
        setAnchorPoint(ccp((x - lx) / (rx - lx), (y - dy) / (uy - dy)));
        setPosition(pTouch->getLocation());
//        CCLog("after hit: %f %f",getAnchorPoint().x,getAnchorPoint().y);
        return true;
    }
    else
    {
//        CCLog("Misses");
        return false;
    }
}

void Figure::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
    setPosition(pTouch->getLocation());
    //CCLog("moved location: %f %f",pTouch->getLocation().x,pTouch->getLocation().y);
}

void Figure::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
}

//void Figure::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent)
//{
//}

void Figure::startTrackingTouch()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

void Figure::stopTrackingTouch()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void Figure::onExit()
{
    // TODO: check when this method is invoked
    CCNodeRGBA::onExit();
    stopTrackingTouch();
}
