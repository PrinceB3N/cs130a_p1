#ifndef BST_H_
#define BST_H_
#include <string>

class Node {
public:
	std::string data;
	int count;
	Node* left;
	Node* right;
	Node* parent;
	Node(std::string data);
	Node(std::string data, Node* parent);
	};
class BST{
private:
	Node* root;
public:
	BST();
	~BST();
	std::string search(std::string word);
	std::string insert(std::string word);
	std::string del(std::string word);
	std::string range_search(std::string start, std::string end);
	std::string print_inorder();
private:
	std::string range_searchHelper(Node* node, std::string start, std::string end);
	void destructHelper(Node* to_del);
	Node* get(std::string word);
	Node* min(Node* node);
	Node* max(Node* node);
	Node* successor(Node* tmp);
	Node* predecessor(Node* tmp);
	std::string inorder_helper(Node* tmp);
};
#endif
