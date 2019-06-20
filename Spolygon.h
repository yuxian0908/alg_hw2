#ifndef S_H
#define S_H
#include "NodePool.h"
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
        void test(Spolygon *s);

        vector<Epolygon*> epo;
        NodePool nodePool;
        Node *firstNode;

};

// empty polygon
class Epolygon: public Spolygon
{
    public:
        Epolygon(Node *n):Spolygon(n){};
        ~Epolygon();
        void merge(Epolygon *s);
        void clip(Spolygon *e);
};

#endif