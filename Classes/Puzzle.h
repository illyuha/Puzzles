#ifndef PUZZLE_H
#define PUZZLE_H
#include "cocos2d-A.h"
#include "Figure.h"


struct PuzzleData
{
    vector<CCPoint> positions;
    vector<float> angles;
    vector<FigureShape> shapes;

    PuzzleData(const vector<FigureShape> & s = vector<FigureShape>(),
               const vector<CCPoint> & p = vector<CCPoint>(),
               const vector<float> & a = vector<float>()):
        shapes(s), positions(p), angles(a)
    {
    }
};

class Puzzle : public CCNodeRGBA
{
private:
    CCSprite * _image;

    Puzzle(int, const CCPoint &, const PuzzleData &);
    explicit Puzzle();
    void drawPuzzle(int);

    Puzzle(const Puzzle &);
    Puzzle & operator=(const Puzzle &);

public:
    ~Puzzle();

    static Puzzle * create(int, const CCPoint &, const PuzzleData &);

};


#endif // PUZZLE_H
