#ifndef E_C
#define E_C
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
    cout<<containCur<<" "<<containNext<<endl;
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
        cout<<containCur<<" "<<containNext<<endl;
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



#endif