#ifndef E_C
#define E_C
#include "Epolygon.h"
#include "Spolygon.h"
#include <limits.h>
#include <algorithm>
#include <stack>
#include "Functions.h"


void Epolygon::clip(Spolygon *s){

}

void Epolygon::merge(Epolygon *s){

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