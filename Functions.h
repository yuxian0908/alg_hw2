#include "NodePool.h"
float cross(Node* o, Node* n1, Node* n2);
float cross(Node* n1, Node* n2);
Node* junct(Node *n1, Node *n2);
Node** findJunct(Node *n1, Node *n2);
bool onPoly(Node *n1, Node *n2);
bool onEdge(Node *n1, Node *n2);
bool comPoly(Node *n1, Node *n2);
bool isCommon(Node *n1, Node *n2);
Node* reverseNode(Node *n);