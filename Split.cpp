#include <iostream>
#include <algorithm> 
#include "Spolygon.h"
using namespace std;

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

void Split_H(Spolygon *s1){
	//���Ls1�@��A���Ny�ȥѤj��p�ƦC(�]�n�O��y������x�ȡAx�ȥѤp�ƨ�j�A�P��y��)�A�P�ɰO�����k���� 
	/*clip����|����node�A���A�ΡC�̤jy�ȥi��]���h���I*/ 
	//clip(s' with node(���W_x,y[0])node(���W_x,y[1])node(�k�W_x,y[1])node(�k�W_x,y[0])) 
	//junct (  �u�qnode(left_max, y[1] )�Bnode(right_max, y[1] ) , s1 )                ��
	//�C��y�ȭn
	//
	//�Y�g�Lclip�A�̤W�ӥk���I�֩w�O��X�A�̤W�ӥ��I��x�Ȫ֩w�O��Xy�ȬOylist���U�@��y�� 
	//�Y�gclip�o��h�Ӱf������ (Epolygon) �A��u��4�I�̿�X�A��l�~��split�A�Y�ұo�Ҭ�4�I�A�h��X���G�|��Ϋᵲ�� 
	// 
	//�H�U���~ 
	//n1->next �M n1 -> prev -> prev ��j�p �A���p�� �V�k/���ojunction ���In1' (n1->next�p�h�V�k) 
	//�V�k�ojunction -> clipper(Polygon ( n1, (n1->next ), n1' , (n1->previous), n1 ) )  cout << "Polygon"<< (n1->next ) (n1->previous)
	//�V���ojunction -> clipper(Polygon ( n1, (n1->next ), n1' , (n1->previous), n1 ) ) 
	//���@�Ӧsnode_y�̪�list�BSolid & empty polygon --> horizontal  
	//�����W�U���k��ɭȥH�K�ϥ�findJunct
	 
	 
	//clip�k
	//���Lpolygon s1 ���Ҧ�node�A�@y array�A�]�tEPolygon��Y�� --> y_raw
	Node *current = s1 -> firstNode;
	int *y_raw;
	int expand_y = 100;
	y_raw = new int[100];
	y_raw[0]= current->y;
	current = current->next;
	int count_for_expand = 1;
	while (current != s1->firstNode){
		if(count_for_expand == expand_y){
			int* temp = new int[expand_y * 2];
            copy(y_raw, y_raw + expand_y, temp);
            delete [] y_raw;
            y_raw = temp;
            expand_y = expand_y * 2;
		}
		y_raw[count_for_expand]= current->y;
		Node *current = current -> next;
		count_for_expand++;
	}
	//����duplicate��y�� 
	int len_y_raw =  sizeof(y_raw)/sizeof(*y_raw);
	for(int i = 0; i < len_y_raw; i++){
		for(int j = i+1; j < len_y_raw;){
			if(y_raw[i] == y_raw[j]){
				for(int k = j; k < len_y_raw-1; k++)
			 	    y_raw[k] = y_raw[k+1];
				len_y_raw --;
			}
			else
			    j++ ;
		}
	}
	int y[len_y_raw];
	for(int i=0; i<len_y_raw; i++)
		y[i] = y_raw[i];
	//�Ƨ�
	sort(y,y+len_y_raw);
	//����
	reverse(y,y+len_y_raw) ;
	
	//���Spolygon s1���W���I�A����y�̤j�M�ĤG�j�� �C�P�ɰO���̤jy�ȹ�����X�ȡA�ѥ��ƨ�k 
	int count_for_x = 0;
	int expand_x=20;
	int *x_raw;
	x_raw = new int[20];
	
	int count_for_x1 = 0;
	int expand_x1=20;
	int *x1_raw;
	x1_raw = new int[20];
	if (current->y == y[0]){
		x_raw[0]=current->x;
		count_for_x+=1;
	}else if(current->y == y[1]){
		x1_raw[0]=current->x;
		count_for_x1+=1;
	}
	current = current->next;
	while (current != s1->firstNode){
	    if(count_for_x == expand_x){
			int* temp = new int[expand_x * 2];
            copy(x_raw, x_raw + expand_x, temp);
            delete [] x_raw;
            x_raw = temp;
            expand_x = expand_x * 2;
		}
		if(count_for_x1 == expand_x1){
			int* temp = new int[expand_x1 * 2];
            copy(x1_raw, x1_raw + expand_x1, temp);
            delete [] x1_raw;
            x1_raw = temp;
            expand_x1 = expand_x1 * 2;
		}
			
        if (current->y == y[0])
	    	x_raw[count_for_x]=current->x;
	    else if(current->y == y[1])
	    	x1_raw[count_for_x1]=current->x;
		current = current->next;
		
	} 
	
	//�Ƨ�
	int len_x_raw =  sizeof(x_raw)/sizeof(*x_raw);
	int x[len_x_raw];
	copy(x_raw, x_raw + len_x_raw, x);
	sort(x,x+len_x_raw);
	
	int len_x1_raw =  sizeof(x1_raw)/sizeof(*x1_raw);
	int x1[len_x1_raw];
	copy(x1_raw, x1_raw + len_x1_raw, x1);
	sort(x1,x1+len_x1_raw);
	//��X 
	int length_x = sizeof(x)/sizeof(*x);
	int count =0;
	while( count < sizeof(x)/sizeof(*x))  { 
	    Node *n1, *n2, *n3, *n4;
	    //if x1 has a number >=x[count]  <=x[count+1]  
	    if(compare(x[count], x[count+1], x1, 0, len_x1_raw)){
            n1 = new Node(x[count], y[1]);  //���U
        	n2 = new Node(x[count+1], y[1]);//�k�U
        	n3 = new Node(x[count+1], y[0]);//�k�W
        	n4 = new Node(x[count],y[0]);   //���W
        	n1->replaceNext(n2);
        	n2->replaceNext(n3);
        	n3->replaceNext(n4);
        	n4->replaceNext(n1);
        	Spolygon *s2 = new Spolygon(n1);
	    	//s1.clip(s2);
	    	cout<<"RECT "<<x[count] <<" "<<y[1]<<" "<<x[count+1] <<" "<<y[0]<<" ;";
		}
        count+=2;
	}
	//return Split_H(Spolygon *s1)
}



void Split_V(Spolygon *s1){
    //���Lpolygon s1 ���Ҧ�node�A�@y array�A�]�tEPolygon��Y�� --> y_raw
    Node *current = s1 -> firstNode;
	int *x_raw;
	int expand_x = 100;
	x_raw = new int[100];
	x_raw[0]= current->x;
	current = current->next;
	int count_for_expand = 1;
	while (current != s1->firstNode){
		if(count_for_expand == expand_x){
			int* temp = new int[expand_x * 2];
            copy(x_raw, x_raw + expand_x, temp);
            delete [] x_raw;
            x_raw = temp;
            expand_x = expand_x * 2;
		}
		x_raw[count_for_expand]= current->x;
		Node *current = current -> next;
		count_for_expand++;
	}
	//����duplicate��y�� 
	int len_x_raw =  sizeof(x_raw)/sizeof(*x_raw);
	for(int i = 0; i < len_x_raw; i++){
		for(int j = i+1; j < len_x_raw;){
			if(x_raw[i] == x_raw[j]){
				for(int k = j; k < len_x_raw-1; k++)
			 	    x_raw[k] = x_raw[k+1];
				len_x_raw --;
			}
			else
			    j++ ;
		}
	}
	int x[len_x_raw];
	for(int i=0; i<len_x_raw; i++)
		x[i] = x_raw[i];
	//�Ƨ�
	sort(x,x+len_x_raw);
	//����
	//reverse(y,y+len_y_raw) ;
	
	//���Spolygon s1���W���I�A����y�̤j�M�ĤG�j�� �C�P�ɰO���̤jy�ȹ�����X�ȡA�ѥ��ƨ�k 
	int count_for_y = 0;
	int expand_y=20;
	int *y_raw;
	y_raw = new int[20];
	
	int count_for_y1 = 0;
	int expand_y1=20;
	int *y1_raw;
	y1_raw = new int[20];
	
	if (current->x == x[0]){
		y_raw[0]=current->y;
		count_for_y+=1;
	}else if(current->x == x[1]){
		y1_raw[0]=current->y;
		count_for_y1+=1;
	}
	current = current->next;
	while (current != s1->firstNode){
	    if(count_for_y == expand_y){
			int* temp = new int[expand_y * 2];
            copy(y_raw, y_raw + expand_y, temp);
            delete [] y_raw;
            y_raw = temp;
            expand_y = expand_y * 2;
		}
		if(count_for_y1 == expand_y1){
			int* temp = new int[expand_y1 * 2];
            copy(y1_raw, y1_raw + expand_y1, temp);
            delete [] y1_raw;
            y1_raw = temp;
            expand_y1 = expand_y1 * 2;
		}
			
        if (current->x == x[0])
	    	y_raw[count_for_y]=current->y;
	    else if(current->x == x[1])
	    	y1_raw[count_for_y1]=current->y;
		current = current->next;
		
	} 
	
	//�Ƨ�
	int len_y_raw =  sizeof(y_raw)/sizeof(*y_raw);
	int y[len_y_raw];
	copy(y_raw, y_raw + len_y_raw, x);
	sort(y,y+len_y_raw);
	
	int len_y1_raw =  sizeof(y1_raw)/sizeof(*y1_raw);
	int y1[len_y1_raw];
	copy(y1_raw, y1_raw + len_y1_raw, y1);
	sort(y1,y1+len_y1_raw);
	//��X 
	int length_y = sizeof(y)/sizeof(*y);
	int count =0;
	while( count < sizeof(y)/sizeof(*y))  { 
	    Node *n1, *n2, *n3, *n4;
	    //if x1 has a number >=x[count]  <=x[count+1]  
	    if(compare(y[count], y[count+1], y1, 0, len_y1_raw)){
	    	n1 = new Node(x[0],y[count]);   //���U 
            n2 = new Node(x[1], y[count]);  //�k�U
        	n3 = new Node(x[1], y[count+1]);//�k�W 
        	n4 = new Node(x[0], y[count+1]);//���W
        	n1->replaceNext(n2);
        	n2->replaceNext(n3);
        	n3->replaceNext(n4);
        	n4->replaceNext(n1);
        	Spolygon *s2 = new Spolygon(n1);
	    	//s1.clip(s2);
	    	cout<<"RECT "<<x[0] <<" "<<y[count]<<" "<<x[1] <<" "<<y[count+1]<<" ;";
		}
        count+=2;
	}
	//return Split_V(Spolygon *s1)
}
