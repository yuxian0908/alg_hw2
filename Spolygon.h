#ifndef S_H
#define S_H
#include "NodePool.h"
#include "Epolygon.h"
#include <vector>

class Epolygon;

// solid polygon
class Spolygon
{
    public:
        Spolygon(Node *n);
        ~Spolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);
        void resetFirstNode(); // set the firstNode to be the left-bottom one

        Node* copyNodes();
        bool containsNode(Node *n);
        void printPolygon();

        vector<Epolygon*> epo;
        NodePool nodePool;
        Node *firstNode;

};

#endif