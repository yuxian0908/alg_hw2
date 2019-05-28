#ifndef S_H
#define S_H
#include "Epolygon.h"
#include "Node.h"
#include <unordered_map> 

class Epolygon;

// solid polygon
class Spolygon
{
    public:
        Spolygon(Node *n);
        ~Spolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);

        Node* copyNodes();
        void replaceNextNode(Node *n1, Node *n2);

        unordered_map<int, unordered_map<int, Node*> > nodePool;
        Node *firstNode;

};

#endif