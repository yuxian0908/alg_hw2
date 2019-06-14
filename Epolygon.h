#ifndef E_H
#define E_H
#include "Spolygon.h"
#include "NodePool.h"
#include <vector>

class Spolygon;


// empty polygon
class Epolygon
{
    public:
        Epolygon(Node *n);
        ~Epolygon();
        void merge(Epolygon *s);
        void clip(Spolygon *e);

        void resetFirstNode(); // set the firstNode to be the left-bottom one

        Node* copyNodes();
        bool containsNode(Node *n);
        void printPolygon();
        NodePool nodePool;
        Node *firstNode;
};
#endif
