#include "main.h"
#include "Spolygon.h"
#include "Epolygon.h"

using namespace std;

int main(){

    // first polygon
    Node *n1, *n2, *n3, *n4;
    n1 = new Node(0, 0);
    n2 = new Node(100, 0);
    n3 = new Node(100, 100);
    n4 = new Node(0, 100);

    n1->replaceNext(n2);
    n2->replaceNext(n3);
    n3->replaceNext(n4);
    n4->replaceNext(n1);

    Spolygon *s1 = new Spolygon(n1);
    s1->firstNode->printNodes();


    cout<<endl<<"sencond"<<endl;

    // second polygon
    n1 = new Node(0, 50);
    n2 = new Node(200, 50);
    n3 = new Node(200, 150);
    n4 = new Node(0, 150);

    n1->replaceNext(n2);
    n2->replaceNext(n3);
    n3->replaceNext(n4);
    n4->replaceNext(n1);

    Spolygon *s2 = new Spolygon(n1);
    s2->firstNode->printNodes();


    cout<<endl<<"merge"<<endl;
    s1->merge(s2);

    s1->firstNode->printNodes();




    // Node *t = s2->findJunct(s1->firstNode->next->next);
    // cout<<t->x<<" "<<t->y;

    cout<<endl<<"hello world"<<endl;
    return 0;
}