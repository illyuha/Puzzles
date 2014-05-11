#include "Puzzle.h"


Puzzle::Puzzle(int num, const CCPoint & startPos)
{
    setAnchorPoint(ccp(0,0));
    setPosition(startPos);
    drawPuzzle(num);
    setContentSize(_image->getContentSize());
}

Puzzle::~Puzzle()
{
}

Puzzle * Puzzle::create(int num, const CCPoint & startPos)
{
    Puzzle * puz = new Puzzle(num,startPos);
    if (puz != NULL)
        puz->autorelease();
    return puz;
}

void Puzzle::drawPuzzle(int num)
{
    // TODO: find out what's wrong here
    // (STATUS_STACK_BUFFER_OVERRUN encountered)

//    char * n = new char[100/*1+sizeof(char)*(num/10+1)*/];
//    itoa(num,n,10);
//    char filename[] = "game/puzzles/puzzle";
//    strcat(filename,n);
//    strcat(filename,".png");

    char filename[] = "game/puzzles/puzzle1.png";
    _image = CCSprite::create(filename);
    _image->setAnchorPoint(ccp(0,0));
    addChild(_image);
}
