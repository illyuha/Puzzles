#ifndef USEFUL_H
#define USEFUL_H
#include <string>
#define uint size_t


using namespace std;

template<typename T>
string ntos(const T & v)
{
    stringstream ss;
    ss << v;
    return ss.str();
}


#endif // USEFUL_H
