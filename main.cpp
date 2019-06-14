#include "main.h"
#include "Spolygon.h"
#include "Epolygon.h"

using namespace std;

int main(){

    // // first polygon
    // Node *n1, *n2, *n3, *n4;
    // n1 = new Node(0, 0);
    // n2 = new Node(100, 0);
    // n3 = new Node(100, 100);
    // n4 = new Node(0, 100);

    // n1->replaceNext(n2);
    // n2->replaceNext(n3);
    // n3->replaceNext(n4);
    // n4->replaceNext(n1);

    // Spolygon *s1 = new Spolygon(n1);
    // s1->firstNode->printNodes();


    // cout<<endl<<"sencond"<<endl;

    // // second polygon
    // n1 = new Node(50, 50);
    // n2 = new Node(150, 50);
    // n3 = new Node(150, 150);
    // n4 = new Node(50, 150);

    // n1->replaceNext(n2);
    // n2->replaceNext(n3);
    // n3->replaceNext(n4);
    // n4->replaceNext(n1);

    // Spolygon *s2 = new Spolygon(n1);
    // s2->firstNode->printNodes();


    // // merge s1 s2
    // cout<<endl<<"merge"<<endl;
    // s1->merge(s2);

    // s1->firstNode->printNodes();


    // first polygon
    Node *n1, *n2, *n3, *n4, *n5,*n6,*n7,*n8,*n9,*n10,*n11;
    n1 = new Node(0, 0);
    n2 = new Node(100, 0);
    n3 = new Node(100, 50);
    n4 = new Node(120, 50);
    n5 = new Node(120,0);
    n6 = new Node(200,0);
    n7 = new Node(200,100);
    n8 = new Node(150,100);
    n9 = new Node(150,150);
    n10 = new Node(50,150);
    n10 = new Node(50,100);
    n11 = new Node(0,100);

    n1->replaceNext(n2);
    n2->replaceNext(n3);
    n3->replaceNext(n4);
    n4->replaceNext(n5);
    n5->replaceNext(n6);
    n6->replaceNext(n7);
    n7->replaceNext(n8);
    n8->replaceNext(n9);
    n9->replaceNext(n10);
    n10->replaceNext(n11);
    n11->replaceNext(n1);

    Spolygon *s1 = new Spolygon(n1);
    s1->firstNode->printNodes();

    // third polygon
    // cout<<endl<<"third"<<endl;
    // n1 = new Node(120, 0);
    // n2 = new Node(200, 0);
    // n3 = new Node(200, 100);
    // n4 = new Node(120, 100);

    // n1->replaceNext(n2);
    // n2->replaceNext(n3);
    // n3->replaceNext(n4);
    // n4->replaceNext(n1);

    // Spolygon *s3 = new Spolygon(n1);
    // s3->firstNode->printNodes();

    // // merge s1 s3
    // cout<<endl<<"merge"<<endl;
    // s1->merge(s3);

    // s1->firstNode->printNodes();

    
    
    
    // fourth polygon
    cout<<endl<<"fourth"<<endl;
    n1 = new Node(50, -50);
    n2 = new Node(150, -50);
    n3 = new Node(150, 30);
    n4 = new Node(50, 30);

    n1->replaceNext(n2);
    n2->replaceNext(n3);
    n3->replaceNext(n4);
    n4->replaceNext(n1);

    Spolygon *s4 = new Spolygon(n1);
    s4->firstNode->printNodes();

    // merge s1 s4
    cout<<endl<<"merge"<<endl;
    s1->merge(s4);

    s1->printPolygon();



    // Node *t = s2->findJunct(s1->firstNode->next->next);
    // cout<<t->x<<" "<<t->y;

    cout<<endl<<"hello world"<<endl;
    return 0;
}