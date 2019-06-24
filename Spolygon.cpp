#ifndef S_C
#define S_C

#include "Spolygon.h"
#include <boost/polygon/polygon.hpp>
#include <vector>
#include <list>

using namespace std;
    Spolygon::Spolygon(Node *n){

        PolygonWithHole p;
        list<point_data<int > > vpts;
        Node* first = n;
        vpts.push_back(point_data<int>(n->x,n->y));
        n = n->next;
        while(n!=first){
            vpts.push_back(point_data<int>(n->x,n->y));
            n = n->next;
        }
        p.set(vpts.begin(),vpts.end());

        poly.push_back(p);    
    }

    void Spolygon::merge(Spolygon* s){
        assign(poly,poly+s->poly);
    }

    void Spolygon::clip(Spolygon* s){
        assign(poly,poly-s->poly);
    }

    void Spolygon::printPolygon(){
        for(vector<PolygonWithHole>::iterator it=poly.begin(); it!=poly.end(); ++it)
        {
            cout<<"Polygon with hole :"<<endl;
            cout<<"outline: "<<endl;
            for(polygon_45_with_holes_data<int>::iterator_type it_pt1=it->begin(); it_pt1!=it->end(); ++it_pt1)
            {
                cout<<it_pt1->x()<<","<<it_pt1->y()<<endl;
            }

            for(polygon_45_with_holes_data<int>::iterator_holes_type it_hole=it->begin_holes(); it_hole!=it->end_holes(); ++it_hole)
            {
                cout<<"hole:"<<endl;
                for(polygon_45_data<int>::iterator_type it_pt=it_hole->begin(); it_pt!=it_hole->end(); ++it_pt)
                {
                    cout<<it_pt->x()<<","<<it_pt->y()<<endl;
                }

            }
        }
    }

    void Spolygon::storeInPool(){
        for(vector<PolygonWithHole>::iterator it=poly.begin(); it!=poly.end(); ++it)
        {
            cout<<"Polygon45 with hole :"<<endl;
            cout<<"outline: "<<endl;
            for(polygon_45_with_holes_data<int>::iterator_type it_pt1=it->begin(); it_pt1!=it->end(); ++it_pt1)
            {
                cout<<it_pt1->x()<<","<<it_pt1->y()<<endl;
                nodePool.add(it_pt1->x(), it_pt1->y());
            }

            for(polygon_45_with_holes_data<int>::iterator_holes_type it_hole=it->begin_holes(); it_hole!=it->end_holes(); ++it_hole)
            {
                cout<<"hole:"<<endl;
                for(polygon_45_data<int>::iterator_type it_pt=it_hole->begin(); it_pt!=it_hole->end(); ++it_pt)
                {
                    cout<<it_pt->x()<<","<<it_pt->y()<<endl;
                    nodePool.add(it_pt->x(), it_pt->y());
                }

            }
        }
    }
#endif