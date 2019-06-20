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
    n1 = new Node(0,0);
    n2 = new Node(0,0);
    n3 = new Node(0,0);
    n4 = new Node(0,0);

    n1->replaceNext(n2);
    n2->replaceNext(n3);
    n3->replaceNext(n4);
    n4->replaceNext(n1);
    Spolygon *master_polygon = new Spolygon(n1);
    
    
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
    
    for(int i = 1 ;i < s.size() - 1; i++){
    	getline(myfile, line);
    	getline(myfile, line);
        vector<string> operation =split(line, " "); // operation[1] is the operation
        cout<< "\n"<< operation[1]<<"\n"; //��߬O�f�ɰw�Aclip�n�e���ɰw 
        if(operation[1] == "MERGE"){
        	while (getline (myfile,line) && line!="END DATA"){
    		
    		vector<string> temp = split(line, " ");
    		int points[9];
    		int x_min=0, x_max=0;
    		int y_min=0, y_max=0;
    		for (int k = 0; k < 9; k++){
    			points[k]=stoi(temp[k]);
    			if(k%2==1){
    				x_max = (points[k]>x_max)?points[k]:x_max;
    				x_min = (points[k]<x_min)?points[k]:x_min;		    
				}else{
					y_max = (points[k]>y_max)?points[k]:y_max;
    				y_min = (points[k]<y_min)?points[k]:y_min;
				}
			}
			
			n1 = new Node(x_min, y_min);
			n2 = new Node(x_max, y_min);
			n3 = new Node(x_max, y_max);
			n4 = new Node(x_min, y_max);
			n1->replaceNext(n2);
            n2->replaceNext(n3);
            n3->replaceNext(n4);
            n4->replaceNext(n1);
            Spolygon *s1 = new Spolygon(n1);
            s1->firstNode->printNodes();
            //cout << temp[j] << "+";
            //cout << "\n";
           
			master_polygon->merge(s1);
			cout<<endl<<"merge"<<endl;
			master_polygon->firstNode->printNodes();
			}
		}
		else if(operation[1]=="CLIPPER"){
            while (getline (myfile,line) && line!="END DATA"){
                
                vector<string> temp = split(line, " ");
                int points[9];
                int x_min=0, x_max=0;
                int y_min=0, y_max=0;
                for (int k = 0; k < 9; k++){
                    points[k]=stoi(temp[k]);
                    if(k%2==1){
                        x_max = (points[k]>x_max)?points[k]:x_max;
                        x_min = (points[k]<x_min)?points[k]:x_min;		    
                    }else{
                        y_max = (points[k]>y_max)?points[k]:y_max;
                        y_min = (points[k]<y_min)?points[k]:y_min;
                    }
                }
                n1 = new Node(x_min, y_min); //���U 
                n2 = new Node(x_min, y_max); //���W 
                n3 = new Node(x_max, y_max); //�k�W 
                n4 = new Node(x_max, y_min); //�k�U 
                n1->replaceNext(n2);
                n2->replaceNext(n3);
                n3->replaceNext(n4);
                n4->replaceNext(n1);
                Epolygon *s1 = new Epolygon(n1);
                s1->firstNode->printNodes();
                //cout << temp[j] << "+";
                //cout << "\n";
                master_polygon->clip(s1);
                cout<<endl<<"clip"<<endl;
                master_polygon->firstNode->printNodes();
            }
        }
	}
    myfile.close();
  

    return 0;
}
