#ifndef FIGURE_H
#define FIGURE_H
#include "cocos2d.h"
#include <vector>


using namespace cocos2d;
using namespace std;

enum FigureType
{
    Trapezium
};

class Figure : public CCNodeRGBA
{
private:
    vector<CCPoint> _vertices;
    CCSprite * _image;
    FigureType _type;
    int _angle;
    bool _movable;

    explicit Figure(const FigureType &, const CCPoint &, int);
    void initVertices();
    void drawImage();
    void onExit();

    Figure(const Figure &);
    Figure & operator=(const Figure &);

public:

    static Figure * create(const FigureType & type = Trapezium, const CCPoint & startPos = ccp(0,0), int angle = 0);
    ~Figure();
    void rotate(bool clockwise = true);
    bool containsPoint(const CCPoint &) const;

    FigureType getType() const
    {
        return _type;
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
