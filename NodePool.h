#ifndef NP_H
#define NP_H

#include "Node.h"
#include <unordered_map> 

// linkedList which value is Node
struct ListNode{
    Node *val;
    ListNode *next;
    ListNode *pre;
    ListNode(Node *n, ListNode *next=0, ListNode *pre=0):val(n), next(next), pre(pre){};
    void replaceNext(ListNode* n){
        this->next = n;
        if(n) n->pre = this;
    }
};

struct NodePool{
    unordered_map<int, ListNode*> x_lists; // lists index by x (incrementing)
    unordered_map<int, ListNode*> y_lists; // lists index by y (incrementing)

    unordered_map<Node*, Node* > edgeInPool;
    unordered_map<Node*, Node* > edgeOutPool;

// NODE POOL
    Node* first(){
        int first = INT_MAX;
        for(unordered_map<int,ListNode*>::iterator it=x_lists.begin();it!=x_lists.end();it++) {
            first = min(first, it->first);
        }
        return x_lists[first]->val;
    }

    bool isEmpty(){
        
        return x_lists.empty();
    }

    void add(Node *n){
        if(n==0) return;
        int x = n->x;
        int y = n->y;
        ListNode *xTmp = new ListNode(n);
        ListNode *yTmp = new ListNode(n);
        if(find(x, y)!=0) return;

        // add to x_lists
        if(x_lists[x]==0){
            x_lists[x] = xTmp; 
        }else{
            ListNode *head = x_lists[x];
            if(xTmp->val->y < head->val->y){ // insert before head
                xTmp->replaceNext(head);
                x_lists[x] = xTmp;
            }else{
                ListNode *curN = head;
                while(xTmp->val->y > curN->val->y && curN->next!=0){
                    curN = curN->next;
                }
                
                if(xTmp->val->y > curN->val->y){
                    curN->replaceNext(xTmp);
                }else{
                    curN->pre->replaceNext(xTmp);
                    xTmp->replaceNext(curN);
                }
            }
        }

        // add to y_lists
        if(y_lists[y]==0){
            y_lists[y] = yTmp;
        }else{
            ListNode *head = y_lists[y];
            if(yTmp->val->x < head->val->x){
                yTmp->replaceNext(head);
                y_lists[y] = yTmp;
            }else{
                ListNode *curN = head;
                while(yTmp->val->x > curN->val->x && curN->next){
                    curN = curN->next;
                }
                if(yTmp->val->x > curN->val->x){
                    curN->replaceNext(yTmp);
                }else{
                    curN->pre->replaceNext(yTmp);
                    yTmp->replaceNext(curN);
                }
            }
        }
    }
    
    void remove(Node *n){
        if(n==0) return;
        int x = n->x;
        int y = n->y;
        remove(x, y);
    }

    void remove(int x, int y){
        if(x_lists[x]==0 && y_lists[x]==0){
            return;
        }
        if(find(x,y)==0) return;
        Node* removed;
        // remove from x_lists
        ListNode* curN = x_lists[x];
        while(curN!=0 && curN->next){
            if(curN->val->y == y){
                if(curN->pre && curN!=x_lists[x]) curN->pre->replaceNext(curN->next);
                else x_lists[x] = curN->next;
                removed = curN->val;
            }
            curN = curN->next;
        }
        if(curN->val->y == y){
            if(curN->pre && curN!=x_lists[x]) curN->pre->replaceNext(curN->next);
            else x_lists[x] = curN->next;
            removed = curN->val;
        }
        if(x_lists[x]==0) x_lists.erase(x);


        // remove from y_lists
        curN = y_lists[y];

        while(curN!=0 && curN->next){
            if(curN->val->x == x){
                if(curN->pre && curN!=y_lists[y]) curN->pre->replaceNext(curN->next);
                else y_lists[y] = curN->next;
            }
            curN = curN->next;
        }
        if(curN->val->x == x){
            if(curN->pre && curN!=y_lists[y]) curN->pre->replaceNext(curN->next);
            else y_lists[y] = curN->next;
        }

        if(y_lists[y]==0) y_lists.erase(y);

        return;
    }

    Node* find(Node *n){
        int x = n->x;
        int y = n->y;
        return find(x,y);
    }

    Node* find(int x, int y){
        if(x_lists[x]==0){
            return 0;
        }
        ListNode* curN = x_lists[x];
        while(curN!=0){
            if(curN->val->y == y) return curN->val;
            curN = curN->next;
        }
        return 0;
    }

    // find y_list successor (right, dir=0)
    Node* yListNext(Node* n){
        int x = n->x;
        int y = n->y;
        if(y_lists[y]==0){
            return 0;
        }
        ListNode* curN = y_lists[y];
        while(curN!=0 && curN->next!=0){
            if(curN->val->x == x) return curN->next->val;
            curN = curN->next;
        }
        return 0;
    }

    // find x_list successor (up, dir=1)
    Node* xListNext(Node* n){
        int x = n->x;
        int y = n->y;
        if(x_lists[x]==0){
            return 0;
        }
        ListNode* curN = x_lists[x];
        while(curN!=0 && curN->next!=0){
            if(curN->val->y == y) return curN->next->val;
            curN = curN->next;
        }
        return 0;
    }

    // find y_list successor (left, dir=2)
    Node* yListPre(Node* n){
        int x = n->x;
        int y = n->y;
        if(y_lists[y]==0){
            return 0;
        }
        ListNode* curN = y_lists[y];
        while(curN!=0 && curN->next!=0){
            if(curN->val->x == x){
                if(curN!=y_lists[y]) return curN->pre->val;
                else return 0;
            }
            curN = curN->next;
        }
        if(curN->val->x == x && curN!=y_lists[y]) return curN->pre->val;
        return 0;
    }

    // find x_list predecessor (down, dir=3)
    Node* xListPre(Node* n){
        int x = n->x;
        int y = n->y;
        if(x_lists[x]==0){
            return 0;
        }
        ListNode* curN = x_lists[x];
        while(curN!=0 && curN->next!=0){
            if(curN->val->y == y){
                if(curN!=x_lists[x]) return curN->pre->val;
                else return 0;
            }
            curN = curN->next;
        }
        if(curN->val->x == x && curN!=x_lists[x]) return curN->pre->val;
        return 0;
    }

    void printPool(){
        // print x_list
        cout<<endl<<"x_list: "<<endl;
        for(unordered_map<int,ListNode*>::iterator it=x_lists.begin();it!=x_lists.end();it++) {
            ListNode *curN = it->second;
            cout<<it->first<<": ";
            while(curN){
                cout<<"("<<curN->val->x<<","<<curN->val->y<<")"<<", "; 
                curN = curN->next;
            }
            cout<<endl;
        }
        // print y_list
        cout<<"y_list:"<<endl;
        for(unordered_map<int,ListNode*>::iterator it=y_lists.begin();it!=y_lists.end();it++) {
            ListNode *curN = it->second;
            cout<<it->first<<": ";
            while(curN){
                cout<<"("<<curN->val->x<<","<<curN->val->y<<")"<<", "; 
                curN = curN->next;
            }
            cout<<endl;
        }
        cout<<endl;
    }
        
    void resetNodePool(){
        x_lists.clear();
        y_lists.clear();
    }


// EDGE POOL
    void removeEdges(Node *n){
        // for(unordered_map<Node*, bool>::iterator it=edgeInPool[n].begin();it!=edgeInPool[n].end();it++) {
        //     Node* n2 = it->first;
        //     edgeInPool[n][n2] = false;
        //     edgeOutPool[n2][n] = false;
        //     // if(edgeOutPool[n2].find(n) != edgeOutPool[n2].end()) edgeOutPool[n2].erase(n);
        // }
        // for(unordered_map<Node*, bool>::iterator it=edgeOutPool[n].begin();it!=edgeOutPool[n].end();it++) {
        //     Node* n2 = it->first;
        //     edgeOutPool[n][n2] = false;
        //     edgeInPool[n2][n] = false;
        //     // if(edgeInPool[n2].find(n) != edgeOutPool[n2].end()) edgeInPool[n2].erase(n);
        // }
    }

    void addEdge(Node *n1, Node *n2){
        if(n1==0 || n2==0) return;
        n1 = find(n1);
        n2 = find(n2);
        edgeOutPool[n1] = n2;
        edgeInPool[n2] = n1;
    }

    void resetEdgePool(){
        edgeInPool.clear();
        edgeOutPool.clear();
    }

    void removeEdge(Node* n){
        Node* in = edgeOutPool[n];
        edgeOutPool.erase(n);
        edgeInPool.erase(in);
    }

    void printEdgePool(){
        cout<<endl<<"edgeInPool: "<<endl;

        for(unordered_map<Node*, Node* >::iterator it=edgeInPool.begin();it!=edgeInPool.end();it++) {
            cout<<"("<<it->first->x<<","<<it->first->y<<")"<<": "<<"("<<it->second->x<<","<<it->second->y<<")"<<endl;
            
        }
        cout<<endl<<"edgeOutPool: "<<endl;
        for(unordered_map<Node*, Node* >::iterator it=edgeOutPool.begin();it!=edgeOutPool.end();it++) {
            cout<<"("<<it->first->x<<","<<it->first->y<<")"<<": "<<"("<<it->second->x<<","<<it->second->y<<")"<<endl;
        }

        // for(unordered_map<Node*, unordered_map<Node*, bool> >::iterator it=edgeInPool.begin();it!=edgeInPool.end();it++) {
        //     unordered_map<Node*, bool> curPool = it->second;
        //     if(it->first){
        //         cout<<"("<<it->first->x<<","<<it->first->y<<")"<<": ";
        //         for(unordered_map<Node*, bool>::iterator it2=curPool.begin();it2!=curPool.end();it2++) {
        //             if(it2->first && it2->second) cout<<"("<<it2->first->x<<","<<it2->first->y<<")"<<", ";
        //         }
        //         cout<<endl;
        //     }
        // }
        // cout<<endl<<"edgeOutPool: "<<endl;
        // for(unordered_map<Node*, unordered_map<Node*, bool> >::iterator it=edgeOutPool.begin();it!=edgeOutPool.end();it++) {
        //     unordered_map<Node*, bool> curPool = it->second;
        //     if(it->first){
        //         cout<<"("<<it->first->x<<","<<it->first->y<<")"<<": ";
        //         for(unordered_map<Node*, bool>::iterator it2=curPool.begin();it2!=curPool.end();it2++) {
        //             if(it2->first && it2->second) cout<<"("<<it2->first->x<<","<<it2->first->y<<")"<<", ";
        //         }
        //         cout<<endl;
        //     }
        // }

        // cout<<endl<<"edgeInPool: "<<endl;
        // for(unordered_map<Node*, unordered_map<Node*, bool> >::iterator it=edgeInPool.begin();it!=edgeInPool.end();it++) {
        //     unordered_map<Node*, bool> curPool = it->second;
        //     cout<<it->first<<": ";
        //     for(unordered_map<Node*, bool>::iterator it2=curPool.begin();it2!=curPool.end();it2++) {
        //         cout<<it2->first<<", ";
        //     }
        //     cout<<endl;
        // }
        // cout<<endl<<"edgeOutPool: "<<endl;
        // for(unordered_map<Node*, unordered_map<Node*, bool> >::iterator it=edgeOutPool.begin();it!=edgeOutPool.end();it++) {
        //     unordered_map<Node*, bool> curPool = it->second;
        //     cout<<it->first<<": ";
        //     for(unordered_map<Node*, bool>::iterator it2=curPool.begin();it2!=curPool.end();it2++) {
        //         cout<<it2->first<<", ";
        //     }
        //     cout<<endl;
        // }
    }
};



#endif