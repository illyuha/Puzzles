#ifndef PUZZLE_H
#define PUZZLE_H
#include "cocos2d-A.h"


class Puzzle : public CCNodeRGBA
{
private:
    CCSprite * _image;

    Puzzle(int, const CCPoint &);
    explicit Puzzle();
    void drawPuzzle(int);

    Puzzle(int, const Puzzle &);
    Puzzle & operator=(const Puzzle &);

public:
    ~Puzzle();
    static Puzzle * create(int, const CCPoint &);

};


#endif // PUZZLE_H
