#include "useful.h"


string ntos(int n)
{
    string s;
    while (n)
    {
        s = char('0' + (n % 10)) + s;
        n /= 10;
    }
    return s;
}

//int random()
//{
//    return rand() % 12;
//}
