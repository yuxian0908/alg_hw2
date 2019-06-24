#ifndef NP_H
#define NP_H

#include "Node.h"
#include <unordered_map> 
#include <limits.h>

using namespace std;

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


    bool isEmpty(){
        
        return x_lists.empty();
    }

    void add(int x, int y){
        add(new Node(x, y));
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
};



#endif