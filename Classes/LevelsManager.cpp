#include "LevelsManager.h"


const uint LevelsManager::FIGURES_IN_LEVEL = 6;
const uint LevelsManager::FIGURES_IN_PUZZLE = 4;

LevelsManager::LevelsManager():
    _levelsNum(0)
{
}

LevelsManager::~LevelsManager()
{
}

LevelsManager & LevelsManager::getInstance()
{
    static LevelsManager instance;
    return instance;
}

void LevelsManager::initFromFile(const string & filePath)
{
    unsigned long fileSize = 0;
    string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath.c_str());
    unsigned char * fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(),"r",&fileSize);
    string contents;
    contents.append((char *)fileContents);
    delete fileContents;
    fileContents = NULL;
    istringstream fin(contents);

    fin >> _levelsNum;
    _levels.resize(_levelsNum);
    for (uint i = 0; i < _levelsNum; ++i)
    {
        vector<FigureShape> shapes(FIGURES_IN_LEVEL);
        vector<CCPoint> positions(FIGURES_IN_PUZZLE);
        vector<float> angles(FIGURES_IN_PUZZLE);
        for (uint j = 0; j < FIGURES_IN_LEVEL; ++j)
        {
            string shape;
            fin >> shape;
            shapes[j] = createFigure(shape);
            if (j < FIGURES_IN_PUZZLE)
                fin >> positions[j].x >> positions[j].y >> angles[j];
        }
        vector<FigureShape> necessaryShapes(shapes.begin(),shapes.begin()+FIGURES_IN_PUZZLE);
        _levels[i] = LevelData(PuzzleData(necessaryShapes,positions,angles),shapes);
    }

}

FigureShape LevelsManager::createFigure(const string & sshape)
{
    FigureShape shape;
    if (sshape == "Triangle")
        shape = Triangle;
    else if (sshape == "SmallTrapeziumR")
        shape = SmallTrapeziumR;
    else if (sshape == "KFigure")
        shape = KFigure;
    else if (sshape == "LargeTrapezium")
        shape = LargeTrapezium;
    else if (sshape == "SmallTrapezium")
        shape = SmallTrapezium;
    else if (sshape == "KFigureR")
        shape = KFigureR;
    else if (sshape == "LargeTrapeziumR")
        shape = LargeTrapeziumR;
    return shape;
}
