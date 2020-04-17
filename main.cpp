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
	cout<<bst->range_search(start,end)<<endl;
	cout<<table->range_search(start,end)<<endl;
}
vector<string> split(const string& commands, char delimiter){
	vector<string> tokens;
  	string token;
   	istringstream tokenStream(commands);
   	while (getline(tokenStream, token, delimiter)){
      		tokens.push_back(token);
   	}
   	return tokens;
}
void handle_commands(BST* bst, HashTable* table, char* commands){
	string str(commands);
	vector<string> result=split(str, ',');
	for(vector<string>::iterator i = result.begin(); i !=result.end();i++){
		vector<string> tmp = split((*i),' ');
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
	HashTable* table = new HashTable(10000);
	fill_BST_HashTable(bst, table, "PA1_dataset.txt");
	handle_commands(bst, table, argv[1]);
	
	return 0;
}
