#include "BST.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

void fill_BST_HashTable(BST* bst, HashTable* table, string filename){
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open()) {   
		string tmp;
		while (getline(file, tmp)) {
			tmp.erase(tmp.find_last_not_of("\n\r") + 1);
			bst->insert(tmp);
			table->insert(tmp);
		}
		file.close(); 
	}
}
void op_search(BST* bst, HashTable* table, string word){
	cout<<bst->search(word)<<endl;
	cout<<table->search(word)<<endl;
}
void op_insert(BST* bst, HashTable* table, string word){
	cout<<bst->insert(word)<<endl;
	cout<<table->insert(word)<<endl;
}
void op_delete(BST* bst, HashTable* table, string word){
	cout<<bst->del(word)<<endl;
	cout<<table->del(word)<<endl;
}
void op_range_search(BST* bst, HashTable* table, string start, string end){
	cout<<bst->range_search(start,end);
	cout<<table->range_search(start,end);
	
}
string substring(char* command, int index, int end){
	string data="";
	if(end<0){
		for(int i=index;true;i++){
			if(command[i]=='\0')
				return data;
			data+=command[i];
		}
	}
	
	for(int a=index;a<index+end;a++){
		data+=command[a];
	}
	return data;
}
		

vector<string> tokenize(char* commands, string delimiter){
	vector<string> tmp;
	int i=0;
	int index = 0;
	while(true){
		for(int a=0;true;a++){
			if(commands[i+a]=='\0'){
				i=-1;
				break;
			}
			else if(commands[i+a]==delimiter.at(0)){
				i=i+a;
				break;
			}
		}
		
		if(i==-1){
			tmp.push_back(substring(commands, index, -1));
			return tmp;
		}
		tmp.push_back(substring(commands, index, i-index));
		index=i+delimiter.size();
		i=index;

	}
	return tmp;	
}
vector<string> tokenize(const string& commands, string delimiter){
	vector<string> tmp;
	int i=0;
	int index = 0;
	while(i<commands.size()){
		i=commands.find(delimiter,index);
		
		if(i==string::npos){
			tmp.push_back(commands.substr(index));
			return tmp;
		}
		tmp.push_back(commands.substr(index,i-index));
		index=i+delimiter.size();

	}
	return tmp;	
}
void handle_commands(BST* bst, HashTable* table, char* commands){
	vector<string> result=tokenize(commands, ", ");
	for(vector<string>::iterator i = result.begin(); i !=result.end();i++){
		vector<string> tmp = tokenize((*i)," ");
		string op = tmp.at(0);
		string word = tmp.at(1);
		
		if(op=="search")
			op_search(bst,table, word);
		else if(op=="insert")
			op_insert(bst,table,word);
		else if(op=="delete")
			op_delete(bst,table,word);
		else if(op=="range")
			op_range_search(bst,table,tmp.at(2),tmp.at(4));
	}
}
int main(int argc, char** argv){
	BST* bst = new BST();
	HashTable* table = new HashTable(104729);
	//test
	fill_BST_HashTable(bst, table, "PA1_dataset.txt");
	//cout<<bst->search("hellcat");
	handle_commands(bst, table, argv[1]);
	delete bst;
	delete table;
	return 0;
}
