class BST {
	class Node {
		public:
		string data;
		int count;
		Node* left;
		Node* right;
		Node* parent;
		Node(string data);
		Node(string data, Node* parent);
	};
private:
	Node* root;
public:
	BST();
	~BST();
	string search(string word);
	string insert(string word);
	string del(string word);
	string range_search(string start, string end);
private:
	string range_searchHelper(Node* node, string start, string end);
	void destructHelper(Node* to_del);
	Node* get(string word);
	Node* min(Node* node);
	Node* max(Node* node);
	Node* successor(Node* tmp);
	Node* predecessor(Node* tmp);
};
