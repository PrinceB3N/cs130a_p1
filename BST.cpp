#include <string>
#include "BST.h"
using namespace std;
class BST {
	class Node {
		public:
		string data;
		int count;
		Node* left;
		Node* right;
		Node* parent;
		Node(string data) {
			this->data = data;
			this->count = 1;
			this->left = NULL;
			this->right = NULL;
			this->parent = NULL;
		}
		Node(string data, Node* parent) {
			this->data = data;
			this->count = 1;
			this->left = NULL;
			this->right = NULL;
			this->parent = parent;
		}
	};
private:
	Node* root;
public:
	BST() {
		this->root = NULL;
	}
	~BST() {
		destructHelper(this->root);
		root = NULL;
	}
	string search(string word) {
		Node* found = get(word);
		if(found!=NULL)
			return word + " found, count = " + to_string(found->count);
		else
			return word + " not found";
	}
	string insert(string word) {
		Node* tmp = this->root;
		if (tmp == nullptr) {
			this->root = new Node(word);
			return word + " inserted, new count = " + to_string(this->root->count);
		}
		Node* prev = NULL;
		bool direction = 0;
		while (tmp != NULL) {
			if (tmp->data > word) {
				prev = tmp;
				tmp = tmp->left;
				direction = 0;
			}
			else if (tmp->data < word) {
				prev = tmp;
				tmp = tmp->right;
				direction = 1;
			}
			else {
				tmp->count += 1;
				return word + " inserted, new count = " + to_string(tmp->count);
			}
		}
		if (direction) {	//right node
			tmp = prev->right = new Node(word,prev);
		}
		else {	//left node
			tmp = prev->left = new Node(word,prev);
		}
		
		return word + " inserted, new count = " + to_string(tmp->count);
	}
	string del(string word) {
		Node* tmp = get(word);
		if (tmp == NULL)
			return "DNE";
		//if count>1, dont delete from BST
		if (tmp->count > 1) {
			tmp->count--;
			return word + " deleted, new count = " + to_string(tmp->count);
		}
		Node* swp = successor(tmp);
		if (swp == NULL) {
			swp = predecessor(tmp);
		}
		if (swp == NULL) {	//only root exists
			delete this->root;
			this->root = NULL;
			return word + " deleted";

		}
		//swap internal data
		tmp->data = swp->data;
		tmp->count = swp->count;

		//delete swp
		if (swp->right!=NULL) {
			swp->right->parent = swp->parent;
			if (swp->parent->left == swp)
				swp->parent->left = swp->right;
			else
				swp->parent->right = swp->right;
			min(swp->right)->left = swp->left;
		}
		else if (swp->left != NULL) {
			swp->left->parent = swp->parent;
			if (swp->parent->left == swp)
				swp->parent->left = swp->left;
			else
				swp->parent->right = swp->left;
		}
		else {
			if (swp->parent->left == swp)
				swp->parent->left = NULL;
			else
				swp->parent->right = NULL;
		}
		//finish up
		delete swp;
		return word + " deleted";
	}
	string range_search(string start, string end) {
		return range_searchHelper(this->root, start, end);
	}
private:
	string range_searchHelper(Node* node, string start, string end) {
		if (node == NULL)
			return "";
		string data = "";
		if (node->data > start) {
			data+=range_searchHelper(node->left, start, end);
		}
		if (start <= node->data && end >= node->data) {
			data+= node->data + "\n";
		}
		if (node->data < end) {
			data+=range_searchHelper(node->right, start, end);
		}
		return data;
	}
	void destructHelper(Node* to_del) {
		if (to_del == nullptr)
			return;
		destructHelper(to_del->left);
		destructHelper(to_del->right);
		delete to_del;
	}
	Node* get(string word) {
		Node* tmp = this->root;
		while (tmp != NULL) {
			if (tmp->data > word) {
				tmp = tmp->left;
			}
			else if (tmp->data < word) {
				tmp = tmp->right;
			}
			else {
				return tmp;
			}
		}
		return NULL;
	}
	Node* min(Node* node) {
		Node* prev = NULL;
		while (node != NULL) {
			prev = node;
			node = node->left;
		}
		return prev;
	}
	Node* max(Node* node) {
		Node* prev = NULL;
		while (node != NULL) {
			prev = node;
			node = node->right;
		}
		return prev;
	}
	Node* successor(Node* tmp) {
		if (!tmp)
			return NULL;
		tmp = tmp->right;
		Node* tmpUp = tmp->parent;

		if (tmp) {
			while (tmp->left) {
				tmp = tmp->left;
			}
			return tmp;
		}
		else if (!tmp) {
			Node* prev = tmp;
			while (tmpUp->left != prev) {
				prev = tmpUp;
				tmpUp = tmpUp->parent;
			}
			return tmpUp;
		}
		else {
			return NULL;
		}

	}
	Node* predecessor(Node* tmp) {
		if (!tmp)
			return NULL;

		tmp = tmp->left;
		Node* tmpUp = tmp->parent;

		if (tmp) {
			while (tmp->right) {
				tmp = tmp->right;
			}
			return tmp;
		}
		else if (!tmp) {
			Node* prev = tmp;
			while (tmpUp) {
				if (tmpUp->right == prev)
					return tmpUp;
				prev = tmpUp;
				tmpUp = tmpUp->parent;
			}
			return tmpUp;
		}
		else {
			return NULL;
		}
	}

};
