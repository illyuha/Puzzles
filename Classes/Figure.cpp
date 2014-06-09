#include "Figure.h"
#include <ADLib.h>
#include <math.h>
#include <ctime>
#define PI 3.14159265358979323846


Figure::Figure(const FigureShape & shape):
    _shape(shape), _movable(true), _angle(0)
{
    setAnchorPoint(ccp(0.5,0.5));
}

Figure::~Figure()
{
}

Figure * Figure::create(const FigureShape & shape)
{
    Figure * fig = new Figure(shape);
    if (fig != NULL)
        fig->autorelease();
    return fig;
}

void Figure::drawImage()
{
    bool generate = false;
    if (!generate)
    {
        switch (_shape)
        {
        case SmallTrapezium:
            _image = CCSprite::create("game/shapes/small_trapezium.png");
            break;
        case Triangle:
            _image = CCSprite::create("game/shapes/triangle.png");
            break;
        case LargeTrapezium:
            _image = CCSprite::create("game/shapes/large_trapezium.png");
            break;
        case KFigure:
            _image = CCSprite::create("game/shapes/k_figure.png");
            break;
        case SmallTrapeziumR:
            _image = CCSprite::create("game/shapes/small_trapezium_r.png");
            break;
        case LargeTrapeziumR:
            _image = CCSprite::create("game/shapes/large_trapezium_r.png");
            break;
        case KFigureR:
            _image = CCSprite::create("game/shapes/k_figure_r.png");
            break;
        }
    }
    else
    {
        CCRenderTexture * rt = CCRenderTexture::create(400,400);
        rt->begin();
        CCDrawNode * node = CCDrawNode::create();
        CCPoint * v = new CCPoint[_vertices.size()];//{ccp(0,0), ccp(0,100), ccp(100,0)};
        for (int i = 0; i < _vertices.size(); ++i)
            v[i] = _vertices[i];
        ccColor4F fillColour;
        fillColour.r = 1;
        fillColour.g = 222;
        fillColour.b = 120;
        fillColour.a = 1;
        ccColor4F backColour;
        backColour.r = 0;
        backColour.g = 0;
        backColour.b = 1;
        backColour.a = 1;
        node->drawPolygon(v,_vertices.size(),fillColour,0,backColour);
        node->visit();
        rt->end();
        _image = CCSprite::createWithTexture(rt->getSprite()->getTexture());
    }

    _image->setAnchorPoint(ccp(0,0));
    addChild(_image);
    setContentSize(_image->getContentSize());
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
    for (int i = 0; i < _vertices.size(); ++i)
    {
        int j = (i + 1) % _vertices.size();
        // Q: why const?
        const CCPoint * pi = &_vertices[i], * pj = &_vertices[j];
        if ((pi->y > y) != (pj->y > y) &&
                pi->x + (y - pi->y) / (pj->y - pi->y) * (pj->x - pi->x) < x)
            odd = !odd;
    }
    return odd;
}

void Figure::rotateRandomly()
{
    rotate(rand() % (360 / int(_rotationStep)));
}

void Figure::setVertices(const vector<CCPoint> & vertices)
{
    _vertices = vertices;
    drawImage();
    Figure * thisFigure = const_cast<Figure *>(this);
    static const float k = 1;//_image->getContentSize().height / 100.0;
    for (int i = 0; i < _vertices.size(); ++i)
    {
        CCPoint * p = &_vertices[i];
        p->x *= k;
        p->y *= k;
        p->x -= _image->getContentSize().width * thisFigure->getAnchorPoint().x;
        p->y -= _image->getContentSize().height * thisFigure->getAnchorPoint().y;
    }
}

void Figure::setScale(float scale)
{
    CCNodeRGBA::setScale(scale);
    for (uint i = 0; i < _vertices.size(); ++i)
    {
        _vertices[i].x *= scale;
        _vertices[i].y *= scale;
    }
}

void Figure::onExit()
{
    // TODO: check when this method is invoked
    // Event callback that is invoked every time the CCNode leaves the 'stage'.
    // => I doubt that overring this method will be necessary
    CCNodeRGBA::onExit();
}
