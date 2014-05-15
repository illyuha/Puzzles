#ifndef FIGURE_H
#define FIGURE_H
#include "cocos2d-A.h"
#include <vector>


enum FigureShape
{
    // R means "reverse"
    SmallTrapezium, Triangle, LargeTrapezium, KFigure, SmallTrapeziumR, LargeTrapeziumR, KFigureR
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
    void rotateRandomly();

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

    float & rotationStep()
    {
        return _rotationStep;
    }

};


#endif // FIGURE_H
