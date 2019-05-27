#include "main.h"
#include "Spolygon.h"
#include "Epolygon.h"

using namespace std;

int main(){

    // first polygon
    Node *n1, *n2, *n3, *n4;
    n1 = new Node(0,0,0);
    n2 = new Node(100, 0, 0);
    n3 = new Node(100, 100, 0);
    n4 = new Node(0, 100, 0);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n1;

    Spolygon *s1 = new Spolygon(n1);
    s1->test();


    cout<<endl<<"sencond"<<endl;

    // second polygon
    n1 = new Node(50,50,0);
    n2 = new Node(150, 50, 0);
    n3 = new Node(150, 150, 0);
    n4 = new Node(50, 150, 0);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n1;

    Spolygon *s2 = new Spolygon(n1);
    s2->test();


    // s1->merge(s2);
    s1->merge(s2);

    cout<<endl<<"hello world"<<endl;
    return 0;
}