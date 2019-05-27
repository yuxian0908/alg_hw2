#include "Spolygon.h"
#include <limits.h>
#include <algorithm>

using namespace std;
float cross(Node* n1, Node* n2);
Node* junct(Node *n1, Node *n2);

// solid polygon
Spolygon::Spolygon(Node *n)
{
    this->firstNode = n;
}

void Spolygon::merge(Spolygon *s2){
    Spolygon *s1 = this;

    // test whether s1's nodes is in s2
    Node *s1CurN = s1->firstNode;
    Node *s1nextN = s1CurN->next;
    // if(s2->containsNode(s1nextN)){

    // }
    s1->findJunct(s2->firstNode);
}

Node* Spolygon::findJunct(Node *n){
    Spolygon *s1 = this;
    Node *curN = s1->firstNode;
    Node* test = junct(curN->next, n);
    cout<<"cur: "<<curN->next->x<<" "<<curN->y<<endl;
    cout<<"junct: "<<test->x<<" "<<test->y;
    return n;
}





// done

float cross(Node* n1, Node* n2){
    Node *o = new Node(0,0,0);
    return (o->x - n1->x) * (o->y-n2->y) - (o->y - n1->y) * (o->x - n2->x);
}

Node* junct(Node *n1, Node *n2){
    Node* a = *(n1->next) - *n1;
    Node* b = *(n2->next) - *n2;
    Node* s = *n2 - *n1;
    if (cross(a, b) == 0) return 0;
    Node *t = *a * (cross(b, s) / cross(a, b));
    return *n1 + *t;
}

bool Spolygon::containsNode(Node *n){
    Spolygon *s1 = this;
    int smallX = INT_MAX;
    int smallY = INT_MAX;
    int bigX = INT_MIN;
    int bigY = INT_MIN;


    Node *initN = s1->firstNode;
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

    return n->x >= smallX & n->x <= bigX & n->y >= smallY & n->y <= bigY;
}

// test
void Spolygon::test(){
    Node *n = this->firstNode;
    for(int i=0; i<5; i++){
        cout<< n->x <<" "<< n->y <<endl;
        n = n->next;
    }
}
