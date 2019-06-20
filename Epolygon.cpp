#ifndef E_C
#define E_C
#include "Epolygon.h"
#include "Spolygon.h"
#include <limits.h>
#include <algorithm>
#include <stack>
#include "Functions.h"


void Epolygon::clip(Spolygon *s2){
    Epolygon *s1 = this;
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
    if( containCur ){ // if s1 contain current node
        nodePool.add(curS2);
        if(junctBegin==0 && containNext){
            nodePool.add(nextS2);
            nodePool.addEdge(curS2, nextS2);
        }
        else if(junctBegin!=0){
            nodePool.add(junctBegin);
            nodePool.addEdge(curS2, junctBegin);
        }
    }
    if(containNext){ // if s1 contain next node
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
        if( containCur ){ // if s1 contain current node
            nodePool.add(curS2);
            if(junctBegin==0 && containNext){
                nodePool.add(nextS2);
                nodePool.addEdge(curS2, nextS2);
            }
            else if(junctBegin!=0){
                nodePool.add(junctBegin);
                nodePool.addEdge(curS2, junctBegin);
            }
        }
        if(containNext){ // if s1 contain next node
            nodePool.add(nextS2);
            if(junctEnd!=0){
                nodePool.add(junctEnd);
                nodePool.addEdge(junctEnd, nextS2);
            }
        }
        curS2 = nextS2;
        nextS2 = nextS2->next;
    }

// merge all nodes
    this->firstNode = nodePool.first();
    firstS1 = this->firstNode;
    curS1 = firstS1;
    nextS1 = nodePool.edgeOutPool[curS1];
    nodePool.removeEdge(curS1);
    curS1->replaceNext(nextS1);
    nodePool.remove(curS1);
    curS1 = nextS1;
    while(curS1!=firstS1){
        nextS1 = nodePool.edgeOutPool[curS1];
        nodePool.removeEdge(curS1);
        curS1->replaceNext(nextS1);
        nodePool.remove(curS1);
        curS1 = nextS1;
    }

// reset the polygon
    resetFirstNode();
    nodePool.printPool();
    nodePool.printEdgePool();
    nodePool.resetEdgePool();
    nodePool.resetNodePool();

}

void Epolygon::merge(Epolygon *s2){
    Epolygon *s1 = this;
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
    if( !containCur ){ // if s1 does not contain current node
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
    if(!containNext){ // if s1 does not contain next node
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
    nodePool.removeEdge(curS1);
    curS1->replaceNext(nextS1);
    nodePool.remove(curS1);
    curS1 = nextS1;
    while(curS1!=firstS1){
        nextS1 = nodePool.edgeOutPool[curS1];
        nodePool.removeEdge(curS1);
        curS1->replaceNext(nextS1);
        nodePool.remove(curS1);
        curS1 = nextS1;
    }
    nodePool.printPool();
    nodePool.printEdgePool();

// reset the polygon
    resetFirstNode();
    nodePool.printPool();
    nodePool.printEdgePool();
    nodePool.resetEdgePool();
    nodePool.resetNodePool();

}

Epolygon::Epolygon(Node *n)
{
    this->firstNode = n;
    n = n->next;
    while(n!=this->firstNode){
        n = n->next;
    }
    resetFirstNode();
}

void Epolygon::resetFirstNode(){
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

Node* Epolygon::copyNodes(){

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

bool Epolygon::containsNode(Node *n2){
    Node* n1 = this->firstNode;
    bool in = false;
    Node *testN = new Node(n2->x, n2->y);
    testN->replaceNext(new Node(100000, testN->y));

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

void Epolygon::printPolygon(){
    firstNode->printNodes();
}


#endif