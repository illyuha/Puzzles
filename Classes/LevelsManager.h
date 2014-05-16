#ifndef LEVELSMANAGER_H
#define LEVELSMANAGER_H
#include "cocos2d-A.h"
#include "Puzzle.h"
#include "Figure.h"
#include <string>
#include <vector>


struct LevelData
{
    PuzzleData puzzle;
    vector<FigureShape> shapes;

    LevelData(const PuzzleData & p = PuzzleData(), const vector<FigureShape> & fs = vector<FigureShape>()):
        puzzle(p), shapes(fs)
    {
    }

};

class LevelsManager
{
private:
    vector<LevelData> _levels;
    uint _levelsNum;

    LevelsManager();
    FigureShape createFigure(const string &);

public:
    static const uint FIGURES_IN_LEVEL;
    static const uint FIGURES_IN_PUZZLE;

    static LevelsManager & getInstance();

    ~LevelsManager();
    void initFromFile(const string &);

    LevelData getLevelData(uint lvlNum) const
    {
        return _levels[lvlNum-1];
    }

    uint numberOfLevels() const
    {
        return _levelsNum;
    }

};

#endif // LEVELSMANAGER_H
