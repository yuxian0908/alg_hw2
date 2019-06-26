#include "main.h"
#include "Spolygon.h"
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "Split.h"
using namespace std;
vector<string> split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;
  
  while(i != s.size()){
    //���r�Ŧꤤ���Ӥ����_���j�Ū��r���F
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
          ++i;
          flag = 0;
          break;
        }
    }
    //���S�@�Ӥ��j�šA�N��Ӥ��j�Ť��Ӫ��r�Ŧ���X�F
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
          flag = 1;
          break;
        }
      if(flag == 0) 
        ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}


int main(){
        
    // first polygon
    
    Node *n1, *n2, *n3, *n4;

            	Spolygon *master_polygon;
    /*
    n1 = new Node(1036000,1000);
    n2 = new Node(4193980,1000);
    n3 = new Node(4193980,1700);
    n4 = new Node(1036000,1700);
    n1->replaceNext(n2);
    n2->replaceNext(n3);
    n3->replaceNext(n4);
    n4->replaceNext(n1);
    Spolygon *master_polygon = new Spolygon(n1);*/
    
    bool master_exist = false;
    
    fstream myfile;
    string line;
    //myfile.open ("OpenCase_1.txt");
    myfile.open ("testdata.txt");
    //���Ĥ@��A�ooperation��T 
  	getline(myfile, line);
  	vector<string> s =split(line, " ");
  	for(vector<string>::size_type i = 0; i != s.size(); ++i)
    cout << s[i] << "\n";
    cout << endl;
    cout << s.size() <<"\n"; 
    cout << s[s.size()-2];
    for(int i = 1 ;i < s.size() - 2; i++){
    	getline(myfile, line);
    	getline(myfile, line);
        vector<string> operation =split(line, " "); // operation[1] is the operation
        cout<< "\n"<< operation[1]<<"\n"; //��߬O�f�ɰw�Aclip�n�e���ɰw 
        	while (getline (myfile,line) && line!="END DATA" ){
    		vector<string> temp = split(line, " ");
    		for(vector<string>::size_type j = 0; j != temp.size()-1; ++j)
    			cout << temp[j]  << " ";
    		cout<<endl;
    		int points[9];
    		int x_min, x_max;
    		int y_min, y_max;
    		for (int k = 1; k < 9; k++){
    			points[k]=stoi(temp[k],nullptr,10);
			}
			x_min=points[1];
			x_max=points[1];
    		y_min=points[2];
			y_max=points[2];
			for (int k = 1; k < 9; k++){
    			if(k%2==1){
    				x_max = (points[k]>x_max)?points[k]:x_max;
    				x_min = (points[k]<x_min)?points[k]:x_min;		    
				}else{
					y_max = (points[k]>y_max)?points[k]:y_max;
    				y_min = (points[k]<y_min)?points[k]:y_min;
				}
			}
			//cout<<"\n NOTICE : "<<x_max<<"@"<<x_min<<"@"<<y_max<<"@"<<y_max<<"@"<<"\n";
			
			n1 = new Node(x_min, y_min);
			n2 = new Node(x_max, y_min);
			n3 = new Node(x_max, y_max);
			n4 = new Node(x_min, y_max);
			n1->replaceNext(n2);
            n2->replaceNext(n3);
            n3->replaceNext(n4);
            n4->replaceNext(n1);
            
            Spolygon *s1 = new Spolygon(n1);
            //s1->printPolygon();
            //cout << temp[j] << "+";
            //cout << "\n";
        if(operation[1] == "MERGE"){
           	if(!master_exist){
              master_polygon = new Spolygon(n1);
           		master_exist = true;
			   }
           	master_polygon->merge(s1);
			//cout<<endl<<"merge"<<endl;
			//master_polygon->printPolygon();
		   } 
		   else if(operation[1]=="CLIPPER"){
		   	    master_polygon->clip(s1);
                //cout<<endl<<"clip"<<endl;
                //master_polygon->printPolygon();
		   } 
		   else if(operation[1] == "MERGE"){
		   	    master_polygon->merge(s1);
           		//cout<<endl<<"merge"<<endl;
			    //master_polygon->printPolygon();
		   } 
		
			}
		}
		
		//master_polygon->storeInPool();
		if(s[s.size()-2] == "SH"){	
		    cout << "SH";
		    Split_H(master_polygon);
		}else if(s[s.size()-2] == "SV"){
			cout << "SV";
			Split_V(master_polygon);
		}
		myfile.close();
    return 0;
	}
