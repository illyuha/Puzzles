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
//    vector<CCPoint> _vertices;
    CCSprite * _image;

    explicit Figure(const FigureType & type = Trapezium, const CCPoint & startPos = ccp(0,0));
    void initVertices(const FigureType &);
    void drawImage();
    void onExit();

    Figure(const Figure &);
    Figure & operator=(const Figure &);

public:
    // Q: what's the point of using the static method instead of constructor?
    // A: Cocos requires this method
    static Figure * create(const FigureType &, const CCPoint &);
    ~Figure();

};


#endif // FIGURE_H
