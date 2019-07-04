#include <iostream>
#include <algorithm> 
#include "Spolygon.h"
#include "NodePool.h"
#include <queue>
using namespace std;
vector<NodePool> nodePool;
struct RECT{
    int x0, y0, x1, y1;
     RECT(int a=0, int b=0 ,int c=0,int d=0):
        x0(a),y0(b),x1(c),y1(d){}
 };
bool operator<(RECT a, RECT b){
     if( a.x0== b.x0 ) return a.y0> b.y0;
     return a.x0> b.x0; 
 }

  

bool compare(int low, int up, int *x1, int sec_lower, int sec_upper){
	int mid = ( sec_upper + sec_lower ) / 2;
	if(x1[mid]>=low && x1[mid]<=up)
	    return true;
	else if(mid == sec_lower){
		if(x1[sec_upper]>=low && x1[sec_upper]<=up)
	        return true;
	    else
	        return false;
	}
	else if(x1[mid] < low){
		return compare(low, up, x1, mid, sec_upper);
	}else if(x1[mid] > up){
		return compare(low, up, x1, 0 , mid);
	}else
	    return false;
}

void Split_H(Spolygon *s1,char *file_out){
	// s1->printPolygon();
	FILE *fp;
	fp = fopen(file_out, "w+");
	priority_queue<RECT> q;
	out:
	while(!s1->nodePool.empty()){
	    auto it_s=s1->nodePool.front();
		map<int,ListNode*>::iterator it=it_s.y_lists.begin();

		if(it==it_s.y_lists.end()) break;
	    ListNode *curN = it->second;
	    int y0 = it->first;
		
	    while(curN){ //split out one RECT 
	        int x0 = curN->val->x;
	        curN = curN->next;
			if(!curN) break;
	        int x1 = curN->val->x;
			
	        while(++it != it_s.y_lists.end()){
	            ListNode *curNx = it->second;
	            int y1 = it->first;
	            while(curNx!=0){
	            	int x = curNx->val->x;
	                if(x>x1)
	                	break;
	                if(x>=x0 && x<=x1){
	                	// cout<<"RECT "<<x0<<" "<<y0<<" "<<x1<<" "<<y1<<" ;"<<endl;    
                        q.push( RECT(x0, y0, x1, y1 ) );
	                	Node *n1, *n2, *n3, *n4;
	                	n1 = new Node(x0, y0); 
	                	n2 = new Node(x1, y0);
	                	n3 = new Node(x1, y1);
	                	n4 = new Node(x0, y1);
	        			n1->replaceNext(n2);
	        			n2->replaceNext(n3);
	        			n3->replaceNext(n4);
	        			n4->replaceNext(n1);
	        			Spolygon *s2 = new Spolygon(n1);
		    			s1->clip(s2);
	                	goto out;
					}
					curNx = curNx->next;
	            }  
			}       
	        curN = curN->next;
	    }
	}
	while( !q.empty() ){
		fprintf(fp, "RECT %d %d %d %d ;\n",q.top().x0, q.top().y0, q.top().x1, q.top().y1);
        q.pop();
    }
	fclose(fp);
}



void Split_V(Spolygon *s1,char *file_out){
	s1->updateNodePool();
	FILE *fp;
	fp = fopen(file_out, "w+");
	priority_queue<RECT> q;
	out:
	while(!s1->nodePool.empty()){
	    auto it_s=s1->nodePool.front();
		map<int,ListNode*>::iterator it=it_s.x_lists.begin();

		if(it==it_s.x_lists.end()) break;
	    ListNode *curN = it->second;
	    int x0 = it->first;
		
	    while(curN){ //split out one RECT 
	        int y0 = curN->val->y;
	        curN = curN->next;
			if(!curN) break;
	        int y1 = curN->val->y;
			
	        while(++it != it_s.x_lists.end()){
	            ListNode *curNy = it->second;
	            int x1 = it->first;
	            while(curNy!=0){
	            	int y = curNy->val->y;
	                if(y>y1)
	                	break;
	                if(y>=y0 && y<=y1){
	                	// cout<<"RECT "<<x0<<" "<<y0<<" "<<x1<<" "<<y1<<" ;"<<endl;
	                	q.push( RECT(x0, y0, x1, y1 ) );
	                	Node *n1, *n2, *n3, *n4;
	                	n1 = new Node(x0, y0); 
	                	n2 = new Node(x1, y0);
	                	n3 = new Node(x1, y1);
	                	n4 = new Node(x0, y1);
	        			n1->replaceNext(n2);
	        			n2->replaceNext(n3);
	        			n3->replaceNext(n4);
	        			n4->replaceNext(n1);
	        			Spolygon *s2 = new Spolygon(n1);
		    			s1->clip(s2);
	                	goto out;
					}
					curNy = curNy->next;
	            }  
			}       
	        curN = curN->next;
	    }
	}
	while( !q.empty() ){
		fprintf(fp, "RECT %d %d %d %d ;\n",q.top().x0, q.top().y0, q.top().x1, q.top().y1);
        q.pop();
    }
	fclose(fp);
}
