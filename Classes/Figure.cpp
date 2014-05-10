#include "Figure.h"
#include <ADLib.h>
//#define SQRT2 sqrt(2)


void Figure::initVertices()
{
    switch (_type)
    {
    case Trapezium:
//        _vertices.resize(4);
        //_vertices = {ccp(0,0), ccp(0,100), ccp(40,100), ccp(140,0)};
//        _vertices[0] = ccp(0,0);
        break;
    }
}

Figure::Figure(const FigureType & type, const CCPoint & startPos, int angle):
    _type(type), _angle(angle), _movable(true)
{
    setAnchorPoint(ccp(0.5,0.5));
    initVertices();
    setPosition(startPos);
    drawImage();
    setContentSize(_image->getContentSize());
}

Figure::~Figure()
{
}

Figure * Figure::create(const FigureType & type, const CCPoint & startPos, int angle)
{
    Figure * fig = new Figure(type,startPos,angle);
    if (fig != NULL)
        fig->autorelease();
    return fig;
}

void Figure::drawImage()
{
    _image = CCSprite::create("game/rect.png");
//    _image->setPosition(ccp(0,0));
    _image->setAnchorPoint(ccp(0,0));
    addChild(_image);
}

void Figure::onExit()
{
    // TODO: check when this method is invoked
    // Event callback that is invoked every time the CCNode leaves the 'stage'.
    // => I doubt that overring this method will be necessary
    CCNodeRGBA::onExit();
}

void Figure::rotate(bool clockwise)
{
    _angle += 45 * (clockwise ? 1 : -1);
    setRotation(_angle);
}
