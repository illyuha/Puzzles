#include "Figure.h"
#include <ADLib.h>
//#define SQRT2 sqrt(2)


void Figure::initVertices(const FigureType & type)
{
    switch (type)
    {
    case Trapezium:
//        _vertices.resize(4);
        //_vertices = {ccp(0,0), ccp(0,100), ccp(40,100), ccp(140,0)};
//        _vertices[0] = ccp(0,0);
        break;
    }
}

Figure::Figure(const FigureType & type, const CCPoint & startPos)
{
    setAnchorPoint(ccp(0.5,0.5));
    initVertices(type);
    setPosition(startPos);
    drawImage();
    setContentSize(_image->getContentSize());
}

Figure::~Figure()
{
}

Figure * Figure::create(const FigureType & type, const CCPoint & startPos)
{
    Figure * fig = new Figure(type,startPos);
    if (fig != NULL)
        fig->autorelease();
    return fig;
}

void Figure::drawImage()
{
    _image = CCSprite::create("game/figure1.png");
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
