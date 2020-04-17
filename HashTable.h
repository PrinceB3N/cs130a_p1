class HashTable {
	class Entry {
		public:
		string data;
		int count;
		Entry(string data);
	};
	vector<list<Entry*>>* entries;
	int size;
public:
	HashTable(int size);
	~HashTable();
	string search(string word);
	string insert(string word);
	string del(string word);
	list<string>* range_search(string start, string end);
	int hash(string word);
	void sorted_insert(list<string>* append, string word);
};
