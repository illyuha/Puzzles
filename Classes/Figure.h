#ifndef FIGURE_H
#define FIGURE_H
#include "cocos2d.h"
#include <vector>


using namespace cocos2d;
using namespace std;

enum FigureShape
{
    // R means "reverse"
    SmallTrapezium, Triangle, LargeTrapezium, KFigure, SmallTrapeziumR, TriangleR, LargeTrapeziumR, KFigureR
};

class Figure : public CCNodeRGBA
{
private:
    vector<CCPoint> _vertices;
    CCSprite * _image;
    FigureShape _shape;
    int _angle;
    bool _movable;
    float _rotationStep;

    explicit Figure(const FigureShape &, const CCPoint &);
    void initVertices();
    void drawImage();
    void onExit();

    Figure(const Figure &);
    Figure & operator=(const Figure &);

public:

    // Q: do I need to specify the default position?
    static Figure * create(const FigureShape & shape = Triangle, const CCPoint & startPos = ccp(0,0));
    ~Figure();
    void rotate(float n = 1/*bool clockwise = true*/);
    bool containsPoint(const CCPoint &) const;

    FigureShape getShape() const
    {
        return _shape;
    }

    int getAngle() const
    {
        return _angle;
    }

    bool movable() const
    {
        return _movable;
    }

    bool & movable()
    {
        return _movable;
    }

//    float rotationStep() const
//    {
//        return _rotationStep;
//    }

    void setRotationStep(int);

};


#endif // FIGURE_H
