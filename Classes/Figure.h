#ifndef FIGURE_H
#define FIGURE_H
#include "cocos2d.h"

using namespace cocos2d;

// Class for handling motions, transformations etc. of images

class Figure : public CCTouchDelegate, public CCNodeRGBA
{
private:
    CCSprite * _image;
    Figure(const CCPoint &);
    void drawImage();
    bool ccTouchBegan(CCTouch *, CCEvent *);
    void ccTouchMoved(CCTouch *, CCEvent *);
    void ccTouchEnded(CCTouch *, CCEvent *);
//    void ccTouchCancelled(CCTouch *, CCEvent *);
    void onExit();

public:
    // Q: what's the point of using the static method instead of constructor?
    // A: Cocos requires this method
    static Figure * create(const CCPoint &);
    ~Figure();
    void startTrackingTouch();
    void stopTrackingTouch();

};

#endif // FIGURE_H
