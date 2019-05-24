#include <iostream>
using namespace std;

struct Node{
    int x;
    int y;
    Node* next;
    Node(int xin, int yin, Node* n):x(xin), y(yin), next(n){}
};