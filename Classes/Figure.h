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

    explicit Figure(const FigureShape &, const CCPoint &, int);
    void initVertices();
    void drawImage();
    void onExit();

    Figure(const Figure &);
    Figure & operator=(const Figure &);

public:

    static Figure * create(const FigureShape & shape = Triangle, const CCPoint & startPos = ccp(0,0), int angle = 0);
    ~Figure();
    void rotate(bool clockwise = true);
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

};


#endif // FIGURE_H
