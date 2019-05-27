#include <iostream>
using namespace std;

struct Node{
    int x;
    int y;
    Node* next;
    Node(int xin, int yin, Node* n):x(xin), y(yin), next(n){};
    friend Node* operator - (Node &n1, Node &n2){ 
        return new Node(n2.x - n1.x, n2.y - n1.y, 0); 
    } 
    friend Node* operator + (Node &n1, Node &n2){ 
        return new Node(n2.x + n1.x, n2.y + n1.y, 0); 
    } 
    friend Node* operator * (Node &n1, float f){ 
        return new Node(n1.x*f, n1.y*f, 0); 
    } 
};