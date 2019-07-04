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
		flag = 0;
		string_size j = i;
		while(j != s.size() && flag == 0){
			for(string_size x = 0; x < seperator.size(); ++x)
				if(s[j] == seperator[x]){
					flag = 1;
					break;
				}
			if(flag == 0) ++j;
		}
		if(i != j){
			result.push_back(s.substr(i, j-i));
			i = j;
		}
	}
	return result;
}


int main(int argc, char* argv[]){
    
    bool master_exist = false;
    int count_for_split = 1;
    bool SH;
    bool SV;
    bool SO;
    int SH_p = 0;
    int SV_p = 0;
    Spolygon *master_polygon;
    fstream myfile;
    string line;
    myfile.open (argv[1]);
    char *file_out = argv[2];

  	getline(myfile, line);
  	vector<string> s =split(line, " ");
  	for(vector<string>::size_type i = 0; i != s.size(); ++i){
  		if(s[i] == "SH"){
  			count_for_split++;
  			SH=true;
  			SH_p = i;
		}else if(s[i] == "SV"){
			SV=true;
			count_for_split++;
			SV_p = i ;
		}else if(s[i] == "SO"){
			SO=true;
			count_for_split++;
		}
	}
	  
    for(int i = 1 ;i < s.size() - count_for_split; i++){
    	getline(myfile, line);
    	getline(myfile, line);
        vector<string> operation =split(line, " ");
		while (getline (myfile,line) && line!="END DATA" ){
    		vector<string> temp = split(line, " ");
			int len = temp.size()-1;
    		int points[len];
    		for (int k = 1; k < len; k++){
    			points[k]=stoi(temp[k],nullptr,10);
			}

			Node *n1 = new Node(points[1], points[2]);
			Node *curN = n1;
			Node *tmpN;
			for(int k=3; k<len; k+=2){
				tmpN = new Node(points[k], points[k+1]);
				curN->replaceNext(tmpN);
				curN = tmpN;
			}
			tmpN->replaceNext(n1);

            Spolygon *s1 = new Spolygon(n1);
           	if(operation[1] == "MERGE"){
           		if(!master_exist){
					master_polygon = new Spolygon(n1);
					master_exist = true;
				}
				master_polygon->merge(s1);
		   	} 
			else if(operation[1]=="CLIPPER"){
					master_polygon->clip(s1);
			} 
			else if(operation[1] == "MERGE"){
					master_polygon->merge(s1);
			} 
		
		}
	}
		
		if(SH_p > SV_p){
			if(SH){
		    	Split_H(master_polygon, file_out);
			}
			if(SV){
				Split_V(master_polygon, file_out);
			}
			if(SO){
				Split_H(master_polygon, file_out);
			}
		}else{
			if(SV){
				Split_V(master_polygon, file_out);
			}
			if(SH){
		    	Split_H(master_polygon, file_out);
			}
			if(SO){
				Split_H(master_polygon, file_out);
			}		
		}
		
		myfile.close();
    return 0;
}
