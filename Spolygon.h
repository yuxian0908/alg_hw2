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

        vector<Node*> epo;
        NodePool nodePool;
        Node *firstNode;

};

// empty polygon
class Epolygon
{
    public:
        Epolygon(Node *n);
        ~Epolygon();
        void merge(Spolygon *s);
        void clip(Epolygon *e);

        void resetFirstNode(); // set the firstNode to be the left-bottom one

        Node* copyNodes();
        bool containsNode(Node *n);
        void printPolygon();
        NodePool nodePool;
        Node *firstNode;
};
