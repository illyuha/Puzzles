#include "Puzzle.h"
#include <string>


Puzzle::Puzzle(int num, const CCPoint & startPos, const PuzzleData &)
{
    setAnchorPoint(ccp(0,0));
    setPosition(startPos);
    drawPuzzle(num);
    setContentSize(_image->getContentSize());
}

Puzzle::~Puzzle()
{
}

Puzzle * Puzzle::create(int num, const CCPoint & startPos, const PuzzleData & data)
{
    Puzzle * puz = new Puzzle(num,startPos,data);
    if (puz != NULL)
        puz->autorelease();
    return puz;
}

void Puzzle::drawPuzzle(int num)
{
    string filename = string("game/puzzles/puzzle" + ntos(num) + ".png");
    _image = CCSprite::create(filename.c_str());
    _image->setAnchorPoint(ccp(0,0));
    addChild(_image);
}
