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
        updateNodePool();   
    }

    void Spolygon::merge(Spolygon* s){
        assign(poly,poly+s->poly);
        updateNodePool();  
    }

    void Spolygon::clip(Spolygon* s){
        assign(poly,poly-s->poly);
        updateNodePool();  
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
            NodePool s;
            for(polygon_45_with_holes_data<int>::iterator_type it_pt1=it->begin(); it_pt1!=it->end(); ++it_pt1)
            {
                s.add(it_pt1->x(), it_pt1->y());
            }

            for(polygon_45_with_holes_data<int>::iterator_holes_type it_hole=it->begin_holes(); it_hole!=it->end_holes(); ++it_hole)
            {
                for(polygon_45_data<int>::iterator_type it_pt=it_hole->begin(); it_pt!=it_hole->end(); ++it_pt)
                {
                    s.add(it_pt->x(), it_pt->y());
                }
            }
            nodePool.push_back(s);
        }
    }

    void Spolygon::printNodePool(){

        cout<<endl<<"NodePool for this graph"<<endl;
        for(vector<NodePool>::iterator it=this->nodePool.begin(); it!=this->nodePool.end(); ++it){
            it->printPool();
        }
    }

    void Spolygon::resetNodePool(){
        for(vector<NodePool>::iterator it=this->nodePool.begin(); it!=this->nodePool.end(); ++it){
            it->reset();
        }
        this->nodePool.clear();
    }

    void Spolygon::updateNodePool(){
        resetNodePool();
        storeInPool();
    }
#endif