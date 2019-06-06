#include "Spolygon.h"
#include <limits.h>
#include <algorithm>
#include <stack>

using namespace std;

float cross(Node* o, Node* n1, Node* n2);
float cross(Node* n1, Node* n2);
Node* junct(Node *n1, Node *n2);
Node** findJunct(Node *n1, Node *n2);
bool onEdge(Node *n1, Node *n2);
bool containsNode(Node *n1, Node *n2);
Node* reverseNode(Node *n);

// merge two solid polygon
void Spolygon::merge(Spolygon *s2){
    Spolygon *s1 = this;
    Node* copiedS1 = copyNodes();
    Node* copiedS2 = s2->copyNodes();
    Node* tmp;

// save nodes into nodePool
    Node *saveN = s1->firstNode;
    nodePool[saveN->x][saveN->y] = saveN;
    saveN = saveN->next;
    while(saveN!=s1->firstNode){
        nodePool[saveN->x][saveN->y] = saveN;
        saveN = saveN->next;
    }
    saveN = s2->firstNode;
    nodePool[saveN->x][saveN->y] = saveN;
    saveN = saveN->next;
    while(saveN!=s2->firstNode){
        nodePool[saveN->x][saveN->y] = saveN;
        saveN = saveN->next;
    }

// go through s1 to find and gather the junction nodes with s2

    Node *s1CurN = s1->firstNode;
    Node *s1nextN = s1CurN->next;

    // check the first node
    Node** junct = findJunct(s2->firstNode, s1CurN);
    Node *junctBegin = junct[0];
    Node *junctEnd = junct[1];

    if(containsNode(s2->firstNode,s1CurN)){ // if current node is in s2
        nodePool[s1CurN->x][s1CurN->y]=0;
        if(junctEnd) junctEnd->replaceNext(s1nextN);
    }else if(containsNode(s2->firstNode,s1nextN)){ // if next node is in s2
        nodePool[s1nextN->x][s1nextN->y]=0;
        if(junctBegin) s1CurN->replaceNext(junctBegin);
    }else{
        if(junctEnd) junctEnd->replaceNext(s1nextN);
        if(junctBegin) s1CurN->replaceNext(junctBegin);
    }
    // set junction in nodePool
    while(junctBegin!=junctEnd){
        nodePool[junctBegin->x][junctBegin->y] = junctBegin;
        if(junctBegin->next) junctBegin = junctBegin->next;
    }
    s1CurN = s1nextN;
    s1nextN = s1nextN->next;

    // check the other node
    while(s1nextN!=0 & s1CurN != s1->firstNode){
        junct = findJunct(s2->firstNode, s1CurN);
        junctBegin = junct[0];
        junctEnd = junct[1];

        if(containsNode(s2->firstNode,s1CurN)){ // if current node is in s2
            nodePool[s1CurN->x][s1CurN->y]=0;
            if(junctEnd) junctEnd->replaceNext(s1nextN);
        }else if(containsNode(s2->firstNode,s1nextN)){ // if next node is in s2
            nodePool[s1nextN->x][s1nextN->y]=0;
            if(junctBegin) s1CurN->replaceNext(junctBegin);
        }else{
            if(junctEnd) junctEnd->replaceNext(s1nextN);
            if(junctBegin) s1CurN->replaceNext(junctBegin);
        }
        // set junction in nodePool
        while(junctBegin!=junctEnd){
            nodePool[junctBegin->x][junctBegin->y] = junctBegin;
            if(junctBegin->next) junctBegin = junctBegin->next;
        }
        if(junctBegin) nodePool[junctBegin->x][junctBegin->y] = junctBegin;
        
        s1CurN = s1nextN;
        s1nextN = s1nextN->next;
    }

    cout<<nodePool[0][50]->next->x<<" "<<nodePool[0][50]->next->y<<endl;
    cout<<"========"<<endl;

// go through s2 and concate all the nodes
    Node *s2CurN = copiedS2;
    Node *s2nextN = s2CurN->next;

    // check the first node
    junct = findJunct(copiedS1, s2CurN);
    junctBegin = junct[0] ? nodePool[junct[0]->x][junct[0]->y] : 0;
    junctEnd = junct[1] ? nodePool[junct[1]->x][junct[1]->y] : 0;
    Node *conc;

    if(containsNode(copiedS1,s2CurN)){ // if current node is in s1
        nodePool[s2CurN->x][s2CurN->y]=0;
        conc = nodePool[s2nextN->x][s2nextN->y];
        if(junctEnd) junctEnd->replaceNext(conc);
    }else if(containsNode(copiedS1,s2nextN)){ // if next node is in s1
        nodePool[s2nextN->x][s2nextN->y]=0;
        conc = nodePool[s2CurN->x][s2CurN->y];
        if(junctBegin) conc->replaceNext(junctBegin);
    }else{
        if(junctEnd){
            conc = nodePool[s2nextN->x][s2nextN->y];
            junctEnd->replaceNext(conc);
        }
        if(junctBegin){
            conc = nodePool[s2CurN->x][s2CurN->y];
            conc->replaceNext(junctBegin);
        }
    }
    s2CurN = s2nextN;
    s2nextN = s2nextN->next;

    // check the other node
    // while(s2nextN!=0 & s2CurN != s2->firstNode){
    //     junct = findJunct(copiedS1, s2CurN);
    //     junctBegin = junct[0] ? nodePool[junct[0]->x][junct[0]->y] : 0;
    //     junctEnd = junct[1] ? nodePool[junct[1]->x][junct[1]->y] : 0;

    //     if(containsNode(copiedS1,s2CurN)){ // if current node is in s1
    //         nodePool[s2CurN->x][s2CurN->y]=0;
    //         conc = nodePool[s2nextN->x][s2nextN->y];
    //         if(junctEnd) junctEnd->replaceNext(conc);
    //     }else if(containsNode(copiedS1,s2nextN)){ // if next node is in s1
    //         nodePool[s2nextN->x][s2nextN->y]=0;
    //         conc = nodePool[s2CurN->x][s2CurN->y];
    //         if(junctBegin) conc->replaceNext(junctBegin);
    //     }else{
    //         if(junctEnd){
    //             conc = nodePool[s2nextN->x][s2nextN->y];
    //             junctEnd->replaceNext(conc);
    //         }
    //         if(junctBegin){
    //             conc = nodePool[s2CurN->x][s2CurN->y];
    //             conc->replaceNext(junctBegin);
    //         }
    //     }
        
    //     s2CurN = s2nextN;
    //     s2nextN = s2nextN->next;
    // }


}

/*    done     */

// solid polygon contructor
Spolygon::Spolygon(Node *n){
    this->firstNode = n;
    nodePool[n->x][n->y] = n;
    n = n->next;
    while(n!=this->firstNode){
        nodePool[n->x][n->y] = n;
        n = n->next;
    }
    resetFirstNode();
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
    // check common edge
    Node *conN = n2;
    Node *nonN = onEdge(curN, n2)&onEdge(n2, curN->next) ? curN->next : 0;
    bool con = con || (onEdge(curN, n2)^onEdge(curN,n2->next));
    if(tmp){
        res->replaceNext(tmp);
        res = res->next;
    }

    curN = curN -> next;
    while(curN!=n1){
        con = con || (onEdge(curN, n2)^onEdge(curN,n2->next));
        nonN = nonN==0 ? (onEdge(curN, n2)&onEdge(n2, curN->next) ? curN->next : 0) : nonN;
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
    
    if(res==0 && con){
        res = conN;
        end = res;
        if(nonN){
            cout<<res<<" "<<con<<" "<<nonN->x<<" "<<nonN->y<<endl;
            res->next = nonN;
            end = nonN;
        }
    }

    Node* *r = new Node*[2];
    r[0] = res;
    r[1] = end;
    

    return r;
}

// check if a node (n2) is in a polygon (n1)
bool containsNode(Node *n1, Node *n2){
    int smallX = INT_MAX;
    int smallY = INT_MAX;
    int bigX = INT_MIN;
    int bigY = INT_MIN;


    Node *initN = n1;
    smallX = bigX = initN->x;
    smallY = bigY = initN->y;

    Node *curN = initN->next;

    bool on = false;
    
    while(curN != initN){
        smallX = min(smallX, curN->x);
        bigX = max(bigX, curN->x);
        smallY = min(smallY, curN->y);
        bigY = max(bigY, curN->y);

        on = onEdge(curN, n2);

        curN = curN->next;
    }
    bool in = n2->x > smallX & n2->x < bigX & n2->y > smallY & n2->y < bigY;

    return in || on;
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