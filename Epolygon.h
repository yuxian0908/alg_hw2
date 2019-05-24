#include "main.h"

// empty polygon
class Epolygon
{
    public:
        Epolygon();
        ~Epolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);
};