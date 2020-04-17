#include <string>
#include <list> 
#include <vector>
#include "CMakeProject1.h"

using namespace std;
class HashTable {
	class Entry {
		public:
		string data;
		int count;
		Entry(string data) {
			this->data = data;
			this->count = 1;
		}
	};
	vector<list<Entry*>>* entries;
	int size;
public:
	HashTable(int size) {
		this->entries = new vector<list<Entry*>>(size);
		this->size = size;
		fill(this->entries->begin(), this->entries->end(), list<Entry*>(0));
	}
	~HashTable() {
		delete this->entries;
	}
	string search(string word) {
		int index = hash(word);
		for (list<Entry*>::iterator i = this->entries->at(index).begin();
			i != this->entries->at(index).end(); i++) {
			if ((*i)->data == word) {
				return word + " found, count = " + to_string((*i)->count);
			}
		}
		return word + " not found";
	}
	string insert(string word) {
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
	string del(string word) {
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
	list<string>* range_search(string start, string end) {
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
	int hash(string word) {
		return (31*(word.front() + word.back())) % size;
	}
	void sorted_insert(list<string>* append, string word) {
		if (append->empty) {
			append->push_front(word);
			return;
		}
		for (list<string>::iterator a = append->begin(); a != append->end(); a++) {
			if (a->data > word) {
				if (a == append->begin()) {
					append->push_front(word);
					return;
				}
				else {
					append->insert(a, word);
					return;
				}
			}
			else if (a->data == word)	//same word, don't add
				return;
		}
		append->push_back(word);	//Either empty list or word is greatest
		return;	
	}
};
