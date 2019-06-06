#ifndef S_H
#define S_H
#include "Epolygon.h"
#include "NodePool.h"

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
        void replaceNextNode(Node *n1, Node *n2);

        NodePool nodePool;
        Node *firstNode;

};

#endif