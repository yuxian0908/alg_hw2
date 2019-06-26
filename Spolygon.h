#ifndef S_H
#define S_H
#include "NodePool.h"
#include <boost/polygon/polygon.hpp>

using namespace boost::polygon;
using namespace boost::polygon::operators;

typedef polygon_45_with_holes_data<int> PolygonWithHole;

// solid polygon
class Spolygon
{
    public:
        Spolygon(Node *n);
        ~Spolygon();
        void merge(Spolygon *s);
        void clip(Spolygon *s);
        void printPolygon();
        void storeInPool();
        void resetNodePool();
        void printNodePool();
        void updateNodePool();
        vector<PolygonWithHole> poly;
        vector<NodePool> nodePool;
};

#endif