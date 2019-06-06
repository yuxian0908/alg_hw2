#include <iostream>
using namespace std;

struct Node{
    int x;
    int y;
    Node* next;
    Node* pre;
    Node(int xin, int yin, Node* n=0, Node *p=0):x(xin), y(yin), next(n), pre(p){};
    friend Node* operator - (Node &n1, Node &n2){ 
        return new Node(n1.x - n2.x, n1.y - n2.y, 0); 
    } 
    friend Node* operator + (Node &n1, Node &n2){ 
        return new Node(n2.x + n1.x, n2.y + n1.y, 0); 
    } 
    friend Node* operator * (Node &n1, float f){ 
        return new Node(n1.x*f, n1.y*f, 0); 
    }
    void replaceNext(Node* n){
        this->next = n;
        if(n) n->pre = this;
    }
    void printNodes(){
        Node *n = this;
        cout<<endl<<n->x<<" "<<n->y<<endl;
        n = n->next;
        while(n!=0 && n!=this){
            cout<<n->x<<" "<<n->y<<endl;
            n = n->next;
        }
        if(n==this){
            cout<<n->x<<" "<<n->y<<endl;
        }
    }
};