#include <iostream>
#include <string>
#include "BST.h"
#include "HashTable.h"
using namespace std;

void assertEquals(string test, string expected){
	if(test==expected)
		cout<<"PASS: "+test+" == "+expected<<endl;
	else
		cout<<"FAIL: "<<endl<<"Expected: "+expected<<endl<<"Actual: "+test<<endl;
}
 
//BST TESTSi
void test_bst_destructor(){
        BST* bst = new BST();
        bst->insert("broadcasting");
	bst->insert("broaching");
        bst->insert("brocaded");
        bst->insert("brochure");
        bst->insert("brochures");
	delete bst;
	cout<<"PASS, but may need memcheck"<<endl;

}
void test_bst_range_check(){
	BST bst;
	bst.insert("broadcasting");
	bst.insert("broaching");
	bst.insert("brocaded");
	bst.insert("brochure");
	bst.insert("brochures");

	assertEquals(bst.range_search("broaching","brochures"),"broaching\nbroadcasting\nbrocaded\nbrochure\nbrochures\n");
}
//HASHTABLE TESTS
void test_table_destructor(){
	HashTable* table = new HashTable(100);
	table->insert("broadcasting");
	table->insert("groder");
	table->insert("repter");
	delete table;
	cout<<"PASS, but may need mem-check"<<endl;
}
void test_table_range_check(){
	HashTable table(6);
	table.insert("broadcasting");
	table.insert("broaching");
	table.insert("brocaded");
	table.insert("brochure");
	table.insert("brochures");

	assertEquals(table.range_search("broaching","brochures"),"broaching\nbroadcasting\nbrocaded\nbrochure\nbrochures\n");
}
int main(){
	test_bst_destructor();
	test_bst_range_check();

	test_table_destructor();
	test_table_range_check();
	return 0;
}
