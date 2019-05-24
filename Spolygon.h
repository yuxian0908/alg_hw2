#include "main.h"
 
// solid polygon
class Spolygon
{
    public:
        Spolygon();
        ~Spolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);
};