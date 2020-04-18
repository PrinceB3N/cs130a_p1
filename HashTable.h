#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <list>
#include <vector>

class Entry {
	public:
	std::string data;
	int count;
	Entry(std::string data);
};
class HashTable{
	std::vector<std::list<Entry*>>* entries;
	unsigned int size;
public:
	HashTable(unsigned int size);
	~HashTable();
	std::string search(std::string word);
	std::string insert(std::string word);
	std::string del(std::string word);
	std::string range_search(std::string start, std::string end);
	unsigned int hash(std::string word);
	void sorted_insert(std::list<std::string>* append, std::string word);
};
#endif
