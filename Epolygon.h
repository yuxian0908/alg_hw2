#ifndef E_H
#define E_H
#include "Spolygon.h"

class Spolygon;

// empty polygon
class Epolygon
{
    public:
        Epolygon();
        ~Epolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);
};
#endif
