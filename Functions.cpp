#include "Functions.h"

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