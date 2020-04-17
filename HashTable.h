#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <list>
#include <vector>
class HashTable {
	class Entry {
		public:
		std::string data;
		int count;
		Entry(std::string data);
	};
	std::vector<std::list<Entry*>>* entries;
	int size;
public:
	HashTable(int size);
	~HashTable();
	std::string search(std::string word);
	std::string insert(std::string word);
	std::string del(std::string word);
	std::list<std::string>* range_search(std::string start, std::string end);
	int hash(std::string word);
	void sorted_insert(std::list<std::string>* append, std::string word);
};
#endif
