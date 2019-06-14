#include "Spolygon.h"
#include <limits.h>
#include <algorithm>
#include <stack>

using namespace std;

float cross(Node* o, Node* n1, Node* n2);
float cross(Node* n1, Node* n2);
Node* junct(Node *n1, Node *n2);
Node** findJunct(Node *n1, Node *n2);
bool onPoly(Node *n1, Node *n2);
bool onEdge(Node *n1, Node *n2);
bool comPoly(Node *n1, Node *n2);
bool isCommon(Node *n1, Node *n2);
Node* reverseNode(Node *n);

// merge two solid polygon
void Spolygon::merge(Spolygon *s2){
    Spolygon *s1 = this;
    Node* copiedS1 = copyNodes();
    Node* copiedS2 = s2->copyNodes();

// go through s1 and store into pool
    Node *firstS1 = copiedS1;
    Node *curS1 = firstS1;
    Node *nextS1 = curS1->next;
    // check first node

    Node** junct = findJunct(copiedS2, curS1);
    Node *junctBegin = junct[0];
    Node *junctEnd = junct[1];
    bool containCur = s2->containsNode(curS1);
    bool containNext = s2->containsNode(nextS1);
    if( !containCur ){ // if s2 does not contain current node
        nodePool.add(curS1);
        if(junctBegin==0 && !containNext){
            nodePool.add(nextS1);
            nodePool.addEdge(curS1, nextS1);
        }
        else if(junctBegin!=0){
            nodePool.add(junctBegin);
            nodePool.addEdge(curS1, junctBegin);
        }
    }
    if(!containNext){ // if s2 does not contain next node
        nodePool.add(nextS1);
        if(junctEnd!=0){
            nodePool.add(junctEnd);
            nodePool.addEdge(junctEnd, nextS1);
        }
    }
    
    curS1 = nextS1;
    nextS1 = nextS1->next;

    while(curS1!=firstS1){
        junct = findJunct(copiedS2, curS1);
        junctBegin = junct[0];
        junctEnd = junct[1];
        containCur = s2->containsNode(curS1);
        containNext = s2->containsNode(nextS1);
        if( !containCur ){
            nodePool.add(curS1);
            if(junctBegin==0 && !containNext){
                nodePool.add(nextS1);
                nodePool.addEdge(curS1, nextS1);
            }
            else if(junctBegin!=0){
                nodePool.add(junctBegin);
                nodePool.addEdge(curS1, junctBegin);
            }
        }
        if(!containNext){
            nodePool.add(nextS1);
            if(junctEnd!=0){
                nodePool.add(junctEnd);
                nodePool.addEdge(junctEnd, nextS1);
            }
        }
        curS1 = nextS1;
        nextS1 = nextS1->next;
    }

    nodePool.printPool();
    nodePool.printEdgePool();

// go through s2 and store into pool
    Node *firstS2 = copiedS2;
    Node *curS2 = firstS2;
    Node *nextS2 = curS2->next;

    // check first node
    junct = findJunct(copiedS1, curS2);
    junctBegin = junct[0];
    junctEnd = junct[1];
    containCur = s1->containsNode(curS2);
    containNext = s1->containsNode(nextS2);
    if( !containCur ){ // if s2 does not contain current node
        nodePool.add(curS2);
        if(junctBegin==0 && !containNext){
            nodePool.add(nextS2);
            nodePool.addEdge(curS2, nextS2);
        }
        else if(junctBegin!=0){
            nodePool.add(junctBegin);
            nodePool.addEdge(curS2, junctBegin);
        }
    }
    if(!containNext){ // if s2 does not contain next node
        nodePool.add(nextS2);
        if(junctEnd!=0){
            nodePool.add(junctEnd);
            nodePool.addEdge(junctEnd, nextS2);
        }
    }
    
    curS2 = nextS2;
    nextS2 = nextS2->next;

    while(curS2!=firstS2){
        junct = findJunct(copiedS1, curS2);
        junctBegin = junct[0];
        junctEnd = junct[1];
        containCur = s1->containsNode(curS2);
        containNext = s1->containsNode(nextS2);
        if( !containCur ){
            nodePool.add(curS2);
            if(junctBegin==0 && !containNext){
                nodePool.add(nextS2);
                nodePool.addEdge(curS2, nextS2);
            }
            else if(junctBegin!=0){
                nodePool.add(junctBegin);
                nodePool.addEdge(curS2, junctBegin);
            }
        }
        if(!containNext){
            nodePool.add(nextS2);
            if(junctEnd!=0){
                nodePool.add(junctEnd);
                nodePool.addEdge(junctEnd, nextS2);
            }
        }
        curS2 = nextS2;
        nextS2 = nextS2->next;
    }

    nodePool.printPool();
    nodePool.printEdgePool();

// merge all nodes
    this->firstNode = nodePool.first();
    firstS1 = this->firstNode;
    curS1 = firstS1;
    nextS1 = nodePool.edgeOutPool[curS1];
    nodePool.removeOutEdge(curS1);
    curS1->replaceNext(nextS1);
    nodePool.remove(curS1);
    curS1 = nextS1;
    while(curS1!=firstS1){
        nextS1 = nodePool.edgeOutPool[curS1];
        nodePool.removeOutEdge(curS1);
        curS1->replaceNext(nextS1);
        nodePool.remove(curS1);
        curS1 = nextS1;
    }


// handle empty polygon
    Node* firR = nodePool.first();
    Node* curR = firR;
    Node* nextR = firR;
    nodePool.remove(curR);
    if( nodePool.edgeOutPool.find(curR)!=nodePool.edgeOutPool.end() ){
        nextR = nodePool.edgeOutPool[curR];
        nodePool.removeOutEdge(curR);
    }
    curR->replaceNext(nextR);
    curR = nextR;
    while(curR!=firR){
        nextR = firR;
        nodePool.remove(curR);
        if( nodePool.edgeOutPool.find(curR)!=nodePool.edgeOutPool.end() ){
            nextR = nodePool.edgeOutPool[curR];
            nodePool.removeOutEdge(curR);
        }
        curR->replaceNext(nextR);
        curR = nextR;
    }
    epo.push_back(firR);




// reset the polygon
    resetFirstNode();
    nodePool.printPool();
    nodePool.printEdgePool();
    nodePool.resetEdgePool();
    nodePool.resetNodePool();
}


/*    done     */

    // solid polygon contructor
    Spolygon::Spolygon(Node *n){
        this->firstNode = n;
        n = n->next;
        while(n!=this->firstNode){
            n = n->next;
        }
        resetFirstNode();
    }

    void Spolygon::printPolygon(){
        cout<<"SPolygon: "<<endl;
        firstNode->printNodes();
        cout<<endl<<"Epolygon: "<<endl;
        for(int i=0; i<epo.size(); i++){
            cout<<"epo"<<i<<": "<<endl;
            epo[i]->printNodes();
        }
    }


    bool Spolygon::containsNode(Node *n2){
        Node* n1 = this->firstNode;
        bool in = false;
        Node *testN = new Node(n2->x, n2->y);
        testN->replaceNext(new Node(INT_MAX, n2->y));

        Node *curN = n1;
        Node *tmp = junct(curN, testN);
        if(tmp!=0) in = !in;

        curN = curN -> next;
        while(curN!=n1){
            tmp = junct(curN, testN);
            if(tmp!=0) in = !in;
            curN = curN->next;
        }
        return in;
    }

    void Spolygon::resetFirstNode(){
        int smallX = INT_MAX;
        int smallY = INT_MAX;
        Node *initN = this->firstNode;
        smallX = initN->x;
        smallY = initN->y;

        Node *curN = initN->next;
        while(curN != initN){
            if(curN->y < smallY){
                this->firstNode = curN;
                smallX = curN->x;
                smallY = curN->y;
            }
            if(curN->y == smallY && curN->x < smallX){
                this->firstNode = curN;
                smallX = curN->x;
                smallY = curN->y;
            }
            curN = curN->next;
        }
    }


    Node* Spolygon::copyNodes(){

        Node *n = this->firstNode;

        if(n->pre!=0) n = n->pre;
        while(n->pre!=0 & n!=this->firstNode){
            n = n->pre;
        }
        this->firstNode = n;


        Node *res = new Node(n->x, n->y);
        Node *tmp = res;
        n = n->next;
        while(n!=0 & n!=this->firstNode){
            tmp->replaceNext(new Node(n->x, n->y));
            tmp = tmp->next;
            n = n->next;
        }
        if(n==firstNode) tmp->replaceNext(res);
        return res;
    }



/*   pure functions  */

    // compute the cross of two vector
    float cross(Node *o, Node* n1, Node* n2){
        return (n1->x - o->x) * (n2->y-o->y) - (n1->y - o->y) * (n2->x - o->x);
    }
    float cross(Node* n1, Node* n2){
        Node *o = new Node(0,0,0);
        return cross(o, n1, n2);
    }

    // given two vector, return their junction
    Node* junct(Node *n1, Node *n2){
        float c1 = cross(n1, n1->next, n2);
        float c2 = cross(n1, n1->next, n2->next);
        float c3 = cross(n2, n2->next, n1);
        float c4 = cross(n2, n2->next, n1->next);
        Node* a = *(n1->next) - *n1;
        Node* b = *(n2->next) - *n2;
        Node* s = *n2 - *n1;
        float pos = cross(s, b) / cross(a, b);
        Node *t = *a * pos;
        if (c1 * c2 < 0 && c3 * c4 < 0)
            return *n1 + *t;
        else return 0;
    }

    // given a polygon(n1) and a vector(n2), return their junction nodes
    Node** findJunct(Node *n1, Node *n2){
        // check return order
        bool increment = true;
        if(n2->x == n2->next->x){
            increment = (n2->y - n2->next->y)>0 ? false : true;
        }else if(n2->y == n2->next->y){
            increment = (n2->x - n2->next->x)>0 ? false : true;
        }


        // find function nodes
        Node *curN = n1;
        Node *res = new Node(0,0);
        Node *tmp = junct(curN, n2);
        if(tmp){
            res->replaceNext(tmp);
            res = res->next;
        }

        curN = curN -> next;
        while(curN!=n1){
            tmp = junct(curN, n2);
            if(tmp){
                res->replaceNext(tmp);
                res = res->next;
            }
            curN = curN->next;
        }

        // set return value
        while(res->pre){
            res = res->pre;
        }

        res = res->next;
        if(res && res->next){
            if(res->x == res->next->x){
                bool order = (res->y - res->next->y)>0 ? false : true;
                if(order != increment) res = reverseNode(res);
            }else if(res->y == res->next->y){
                bool order = (res->x - res->next->x)>0 ? false : true;
                if(order != increment) res = reverseNode(res);
            }
        }

        Node* end = res;
        while(end && end->next){
            end = end->next;
        }

        Node* *r = new Node*[2];
        r[0] = res;
        r[1] = end;
        

        return r;
    }


    // check if node n2 is on the edges of polygon n1
    bool onPoly(Node *n1, Node *n2){
        Node *initN = n1;
        Node *curN = initN->next;
        bool on = false;
        while(curN != initN){
            on = onEdge(curN, n2);
            curN = curN->next;
        }
        return on;
    }

    // check if n2 is on the edge (n1, n1->next)
    bool onEdge(Node *n1, Node *n2){
        bool on = false;
        if( (n1->x == n1->next->x && n1->next->x == n2->x) &&
            ( (n2->y - n1->y)*(n2->y - n1->next->y) <= 0) ) on=true;
        if( (n1->y == n1->next->y && n1->next->y == n2->y) &&
            ( (n2->x - n1->x)*(n2->x - n1->next->x) <= 0) ) on=true;
        return on;
    }

    // check if edge (n2, n2->next) has common edge on the edges of polygon n1
    bool comPoly(Node *n1, Node *n2){
        Node *initN = n1;
        Node *curN = initN->next;
        bool comm = false;
        while(curN != initN){
            comm = isCommon(curN, n2);
            curN = curN->next;
        }
        return comm;
    }

    // check if n2(n2, n2->next) is common edge of the edge (n1, n1->next)
    bool isCommon(Node *n1, Node *n2){
        bool comm = false;
        if( n1->x == n1->next->x && n1->next->x == n2->x && n2->next->x == n2->x) comm=true;
        if( n1->y == n1->next->y && n1->next->y == n2->y && n2->next->y == n2->y) comm=true;
        return comm;
    }

    Node* reverseNode(Node *n){
        Node* res = new Node(0,0);
        stack<Node*> s;
        while(n){
            s.push(n);
            n = n->next;
        }
        while(!s.empty()){
            res->replaceNext(s.top());
            s.pop();
            res = res->next;
        }
        res->next = 0;
        while(res->pre){
            res = res->pre;
        }

        return res->next;
    }