#ifndef S_H
#define S_H
#include "Epolygon.h"
#include "Node.h"

class Epolygon;

// solid polygon
class Spolygon
{
    public:
        Spolygon(Node *n);
        ~Spolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);
        bool containsNode(Node *n);
        Node* findJunct(Node *n);
        Node *firstNode;

        // test
        void test();
};

#endif