#ifndef H_H
#define H_H

#include "Node.h"
#include "NodePool.h"

float cross(Node* o, Node* n1, Node* n2);
float cross(Node* n1, Node* n2);
float dot(Node *o, Node* n1, Node* n2);
float dot(Node* n1, Node* n2);
Node* junct(Node *n1, Node *n2);
Node** findJunct(Node *n1, Node *n2);
Node* reverseNode(Node *n);
Node* onJunct(Node *n1, Node *n2);
Node* findOnJunct(Node *n1, Node *n2);


#endif