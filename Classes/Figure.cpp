#include "Figure.h"
#include <ADLib.h>
#include <math.h>
#include <ctime>
#define PI 3.14159265358979323846
#define SQRT2 sqrt(2)


void Figure::initVertices()
{
    // Q: should I use Factory (Method)?
    switch (_shape)
    {
    case SmallTrapezium:
    {
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(100*SQRT2-100,100), ccp(100*SQRT2,0)};
        _vertices = vector<CCPoint>(v,v+4);
    }
        break;
    case Triangle:
    {
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(100,0)};
        _vertices = vector<CCPoint>(v,v+3);
    }
        break;
    case LargeTrapezium:
    {
        CCPoint v[] = {ccp(0,0), ccp(0,100), ccp(200,100), ccp(300,0)};
        _vertices = vector<CCPoint>(v,v+4);
    }
        break;
    case KFigure:
    {
        CCPoint v[] = {ccp(0,0), ccp(50*SQRT2,50*SQRT2), ccp(100-50*SQRT2,100), ccp(100+50*SQRT2,100), ccp(200+50*SQRT2,0)};
        _vertices = vector<CCPoint>(v,v+5);
    }
        break;
    case SmallTrapeziumR:
    {
        CCPoint v[] = {ccp(0,0), ccp(100,100), ccp(100*SQRT2,100), ccp(100*SQRT2,0)};
        _vertices = vector<CCPoint>(v,v+4);
    }
        // TODO: define other figures' vertices
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

Figure::Figure(const FigureShape & shape, const CCPoint & startPos):
    _shape(shape), _movable(true), _angle(0)
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

Figure * Figure::create(const FigureShape & shape, const CCPoint & startPos)
{
    Figure * fig = new Figure(shape,startPos);
    if (fig != NULL)
        fig->autorelease();
    return fig;
}

void Figure::drawImage()
{
    switch (_shape)
    {
    case SmallTrapezium:
        _image = CCSprite::create("game/small_trapezium.png");
        break;
    case Triangle:
        _image = CCSprite::create("game/triangle.png");
        break;
    case LargeTrapezium:
        _image = CCSprite::create("game/large_trapezium.png");
        break;
    case KFigure:
        _image = CCSprite::create("game/k_figure.png");
        break;
    case SmallTrapeziumR:
        _image = CCSprite::create("game/small_trapezium_r.png");
        break;
    case TriangleR:
        _image = CCSprite::create("game/triangle_r.png");
        break;
    case LargeTrapeziumR:
        _image = CCSprite::create("game/large_trapezium_r.png");
        break;
    case KFigureR:
        _image = CCSprite::create("game/k_figure_r.png");
        break;
    }

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
void Figure::rotate(float n/*, bool clockwise*/)
{
//    float alpha = 45 * (clockwise ? 1 : -1);
    float alpha = _rotationStep * n;
    _angle = int(_angle + alpha) % 360;

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

void Figure::setRotationStep(int step)
{
    _rotationStep = step;
    srand(time(0));
    rotate(rand() % (360 / step));
}
