#include "Figure.h"
#include <ADLib.h>
#include <math.h>
#define PI 3.14159265358979323846
//#define SQRT2 sqrt(2)


void Figure::initVertices()
{
    switch (_type)
    {
    case Trapezium:
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(40,100), ccp(140,0)};
        _vertices = vector<CCPoint>(v,v+4);
        break;
    }
    Figure * thisFigure = const_cast<Figure *>(this);
    static const float k = _image->getContentSize().height / 100.0;
    for (int i = 0; i < _vertices.size(); ++i)
    {
        CCPoint * p = &_vertices[i];
        p->x *= k;
        p->y *= k;
        p->x -= _image->getContentSize().width * thisFigure->getAnchorPoint().x;
        p->y -= _image->getContentSize().height * thisFigure->getAnchorPoint().y;
    }
}

Figure::Figure(const FigureType & type, const CCPoint & startPos, int angle):
    _type(type), _angle(angle), _movable(true)
{
    setAnchorPoint(ccp(0.5,0.5));
    setPosition(startPos);
    drawImage();
    setContentSize(_image->getContentSize());
    initVertices();
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

// TODO: find out why this algo works
void Figure::rotate(bool clockwise)
{
    float alpha = 45 * (clockwise ? 1 : -1);
    _angle += alpha;

    // rotating round the point (0;0)
    alpha *= -1;
    float s = sin(alpha/180.0*PI), c = cos(alpha/180.0*PI);
    for (int i = 0; i < _vertices.size(); ++i)
    {
        CCPoint * p = &_vertices[i];
        float nx = p->x * c - p->y * s, ny = p->x * s + p->y * c;
        p->x = nx;
        p->y = ny;
    }

    setRotation(_angle);
}

// TODO: find out why this algo works
bool Figure::containsPoint(const CCPoint & point) const
{
    bool odd = false;
    // Q: How on Earth can I avoid such casting?
    Figure * thisFigure = const_cast<Figure *>(this);
    float x = point.x - (thisFigure->getPositionX()),
            y = point.y - (thisFigure->getPositionY());
    // TODO: avoid hard-coded constants
    for (int i = 0; i < _vertices.size(); ++i)
    {
        int j = (i + 1) % _vertices.size();
        const CCPoint * pi = &_vertices[i], * pj = &_vertices[j];
        if ((pi->y > y) != (pj->y > y) &&
                pi->x + (y - pi->y) / (pj->y - pi->y) * (pj->x - pi->x) < x)
            odd = !odd;
    }
    return odd;
}
