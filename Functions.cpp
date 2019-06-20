#ifndef H_C
#define H_C
#include "Functions.h"
#include "Node.h"
#include "NodePool.h"
#include <stack>

/*   pure functions  */

    // compute the cross of two vector
    float cross(Node *o, Node* n1, Node* n2){
        return (n1->x - o->x) * (n2->y-o->y) - (n1->y - o->y) * (n2->x - o->x);
    }
    float cross(Node* n1, Node* n2){
        Node *o = new Node(0,0,0);
        return cross(o, n1, n2);
    }

    float dot(Node *o, Node* n1, Node* n2){
        return (n1->x - o->x) * (n2->x - o->x) + (n1->y - o->y) * (n2->y - o->y);
    }
    float dot(Node* n1, Node* n2){
        Node *o = new Node(0,0,0);
        return dot(o, n1, n2);
    }

    bool intersect(Node* p, Node* p1, Node* p2){
        // cout<<dot(p, p1, p2)<<"intersect"<<endl;
        return cross(p, p1, p2) == 0
            && dot(p, p1, p2) <= 0;
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

    // given a node(n1) and a vector(n2), return if n1 is on n2
    Node* onJunct(Node *n1, Node *n2){
        Node *a1 = n1;
        Node *a2 = n1->next;
        Node *b1 = n2;
        Node *b2 = n2->next;

        float c1 = cross(a1, a2, b1);
        float c2 = cross(a1, a2, b2);
        float c3 = cross(b1, b2, a1);
        float c4 = cross(b1, b2, a2);

        if (c1 == 0 && c2 == 0){
            if (a1 == b1 && dot(a1, a2, b2) <= 0) return a1;
            if (a1 == b2 && dot(a1, a2, b1) <= 0) return a1;
            // if (a2 == b1 && dot(a2, a1, b2) <= 0) return a2;
            // if (a2 == b2 && dot(a2, a1, b1) <= 0) return a2;
        }
        // to determine whether the point is on the polygon
        // if (c1 == 0 && intersect(b1, a1, a2)) return b1;
        // if (c2 == 0 && intersect(b2, a1, a2)) return b2;
        if (c3 == 0 && intersect(a1, b1, b2)) return a1;
        // if (c4 == 0 && intersect(a2, b1, b2)) return a2;

        return 0;
    }

    // given a polygon(n1) and a vector(n2), return their on junction node
    Node* findOnJunct(Node *n1, Node *n2){
        Node *curN = n1;
        Node *res = onJunct(n2, curN);
        // cout<<res<<endl;
        curN = curN -> next;
        while(curN!=n1){
            if(res==0) res = onJunct(n2, curN);
            // cout<<res<<endl;
            curN = curN->next;
        }
        return res;
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


#endif