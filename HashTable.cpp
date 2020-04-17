#include <string>
#include <list> 
#include <vector>
#include "HashTable.h"

using namespace std;
Entry::Entry(string data) {
	this->data = data;
	this->count = 1;
}

HashTable::HashTable(int size) {
	this->entries = new vector<list<Entry*>>(size);
	this->size = size;
	fill(this->entries->begin(), this->entries->end(), list<Entry*>(0));
}
HashTable::~HashTable() {
	delete this->entries;
}
string HashTable::search(string word) {
	int index = hash(word);
	for (list<Entry*>::iterator i = this->entries->at(index).begin();
		i != this->entries->at(index).end(); i++) {
		if ((*i)->data == word) {
			return word + " found, count = " + to_string((*i)->count);
		}
	}
	return word + " not found";
}
string HashTable::insert(string word) {
	int index = hash(word);
	for (list<Entry*>::iterator i = this->entries->at(index).begin();
		i != this->entries->at(index).end(); i++) {
		if ((*i)->data == word) {
			(*i)->count++;
			return word + " inserted, new count = " + to_string((*i)->count);
		}
	}
	Entry* tmp = new Entry(word);
	this->entries->at(index).push_back(tmp);
	return word + " inserted, new count = " + to_string(tmp->count);
}
string HashTable::del(string word) {
	int index = hash(word);
	for (list<Entry*>::iterator i = this->entries->at(index).begin();
		i != this->entries->at(index).end(); i++) {
		if ((*i)->data == word) {
			if ((*i)->count == 1) {
				this->entries->at(index).erase(i);
				return word + " deleted";
			}
			else {
				(*i)->count--;
				return word + " deleted, new count = " + to_string((*i)->count);
			}
		}
	}
	return word + " not found";
}
list<string>* HashTable::range_search(string start, string end) {
	list<string>* append = new list<string>(0);
	for (vector<list<Entry*>>::iterator i = this->entries->begin();
		i != this->entries->end(); i++) {
		for (list<Entry*>::iterator l = i->begin(); l != i->end(); l++) {
			if ((*l)->data >=start && (*l)->data <=end) {
				sorted_insert(append, (*l)->data);
			}
		}
	}
	return append;
}
int HashTable::hash(string word) {
	return (31*(word.front() + word.back())) % size;
}
void HashTable::sorted_insert(list<string>* append, string word) {
	if (append->empty()) {
		append->push_front(word);
		return;
	}
	for (list<string>::iterator a = append->begin(); a != append->end(); a++) {
		if ((*a) > word) {
			if (a == append->begin()) {
				append->push_front(word);
				return;
			}
			else {
				append->insert(a, word);
				return;
			}
		}
		else if ((*a) == word)	//same word, don't add
			return;
	}
	append->push_back(word);	//Either empty list or word is greatest
	return;	
}
