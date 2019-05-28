#include "Spolygon.h"
#include <limits.h>
#include <algorithm>

using namespace std;
float cross(Node* o, Node* n1, Node* n2);
float cross(Node* n1, Node* n2);
Node* junct(Node *n1, Node *n2);
Node* findJunct(Node *n1, Node *n2);
bool containsNode(Node *n1, Node *n2);



/*   done  */

// solid polygon contructor
Spolygon::Spolygon(Node *n)
{
    this->firstNode = n;
    unordered_map<int, unordered_map<int, Node*> > pool = this->nodePool;
    
    pool[n->x][n->y] = n;
    n = n->next;
    while(n!=this->firstNode){
        pool[n->x][n->y] = n;
        n = n->next;
    }
}

// merge two solid polygon
void Spolygon::merge(Spolygon *s2){
    Spolygon *s1 = this;
    Node* copiedS1 = copyNodes();
    Node* tmp;

// find which s1 node is in s2 and do the merge
    Node *s1CurN = s1->firstNode;
    Node *s1nextN = s1CurN->next;

    // check the first node
    if(containsNode(s2->firstNode,s1CurN)){
        tmp = findJunct(s2->firstNode, s1CurN);
        s1->replaceNextNode(tmp, s1nextN);
        s1->firstNode = tmp; // reset firstNode
    }else if(containsNode(s2->firstNode,s1nextN)){
        tmp = findJunct(s2->firstNode, s1CurN);
        s1->replaceNextNode(s1CurN, tmp);
    }
    s1CurN = s1nextN;
    s1nextN = s1nextN->next;

    // check the other node
    while(s1nextN!=0 & s1CurN != s1->firstNode){
        if(containsNode(s2->firstNode,s1CurN)){
            tmp = findJunct(s2->firstNode,s1CurN);
            s1->replaceNextNode(tmp, s1nextN);
            s1->firstNode = tmp; // reset firstNode
        }else if(containsNode(s2->firstNode,s1nextN)){
            tmp = findJunct(s2->firstNode,s1CurN);
            s1->replaceNextNode(s1CurN, tmp);
        }
        s1CurN = s1nextN;
        s1nextN = s1nextN->next;
    }

// find which s2 node is in s1 and do the merge
    Node *s2CurN = s2->firstNode;
    Node *s2nextN = s2CurN->next;
    copiedS1->printNodes();
    // check the first node
    if(containsNode(copiedS1,s2CurN)){
        tmp = findJunct(copiedS1, s2CurN);
        if(nodePool[tmp->x][tmp->y]!=0){
            tmp = nodePool[tmp->x][tmp->y];
        }
        s2->replaceNextNode(tmp, s2nextN);
        s2->firstNode = tmp; // reset firstNode
    }else if(containsNode(copiedS1,s2nextN)){
        tmp = findJunct(copiedS1, s2CurN);
        if(nodePool[tmp->x][tmp->y]!=0) tmp = nodePool[tmp->x][tmp->y];
        s2->replaceNextNode(s1CurN, tmp);
    }
    s2CurN = s2nextN;
    s2nextN = s2nextN->next;

    // check the other node
    while(s2nextN!=0 & s2CurN != s2->firstNode){
        if(containsNode(copiedS1,s2CurN)){
            tmp = findJunct(copiedS1,s2CurN);
            if(nodePool[tmp->x][tmp->y]!=0) tmp = nodePool[tmp->x][tmp->y];
            s2->replaceNextNode(tmp, s2nextN);
            s2->firstNode = tmp; // reset firstNode
        }else if(containsNode(copiedS1,s2nextN)){
            tmp = findJunct(copiedS1,s2CurN);
            if(nodePool[tmp->x][tmp->y]!=0) tmp = nodePool[tmp->x][tmp->y];
            s2->replaceNextNode(s2CurN, tmp);
        }
        s2CurN = s2nextN;
        s2nextN = s2nextN->next;
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

void Spolygon::replaceNextNode(Node *n1, Node *n2){
    Node* delN = n1->next;
    if(delN!=0) nodePool[delN->x][delN->y] = 0;
    nodePool[n2->x][n2->y] = n2;
    n1->replaceNext(n2);
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

Node* findJunct(Node *n1, Node *n2){
    Node *curN = n1;
    Node* res = junct(curN, n2);
    if(res) return res;
    curN = curN -> next;
    while(curN!=n1){
        res = junct(curN, n2);
        if(res) break;
        curN = curN->next;
    }
    return res;
}


bool containsNode(Node *n1, Node *n2){
    int smallX = INT_MAX;
    int smallY = INT_MAX;
    int bigX = INT_MIN;
    int bigY = INT_MIN;


    Node *initN = n1;
    smallX = bigX = initN->x;
    smallY = bigY = initN->y;

    Node *curN = initN->next;
    while(curN != initN){
        smallX = min(smallX, curN->x);
        bigX = max(bigX, curN->x);
        smallY = min(smallY, curN->y);
        bigY = max(bigY, curN->y);
        curN = curN->next;
    }

    return n2->x > smallX & n2->x < bigX & n2->y > smallY & n2->y < bigY;
}
