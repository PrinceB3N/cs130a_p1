#include <string>
#include <iostream>
#include "BST.h"
using namespace std;
Node::Node(string data) {
	this->data = data;
	this->count = 1;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
	}
Node::Node(string data, Node* parent) {
	this->data = data;
	this->count = 1;
	this->left = NULL;
	this->right = NULL;
	this->parent = parent;
}
BST::BST() {
	this->root = NULL;
}
BST::~BST() {
	destructHelper(this->root);
}
string BST::search(string word) {
	Node* found = get(word);
	if(found!=NULL)
		return word + " found, count = " + to_string(found->count);
	else
		return word + " not found";
}
string BST::insert(string word) {
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
string BST::del(string word) {
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
string BST::range_search(string start, string end) {
	return range_searchHelper(this->root, start, end);
}
string BST::print_inorder(){
	return inorder_helper(this->root);	
}
string BST::range_searchHelper(Node* node, string start, string end) {
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
void BST::destructHelper(Node* to_del) {
	if (to_del == NULL)
		return;
	destructHelper(to_del->left);
	destructHelper(to_del->right);
	delete to_del;
}
Node* BST::get(string word) {
	Node* tmp = this->root;
	while (tmp != NULL) {
		if(tmp->data == word)
			return tmp;
		else if (tmp->data > word) {
			tmp = tmp->left;
		}
		else if (tmp->data < word) {
			tmp = tmp->right;
		}
	}
	return NULL;
}
Node* BST::min(Node* node) {
	Node* prev = NULL;
	while (node != NULL) {
		prev = node;
		node = node->left;
	}
	return prev;
}
Node* BST::max(Node* node) {
	Node* prev = NULL;
	while (node != NULL) {
		prev = node;
		node = node->right;
	}
	return prev;
}
Node* BST::successor(Node* tmp) {
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
Node* BST::predecessor(Node* tmp) {
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
string BST::inorder_helper(Node* tmp){
	if(tmp==NULL)
		return "";
	string data="";
	data+=inorder_helper(tmp->left);
	data+=tmp->data+" ";
	data+=inorder_helper(tmp->right);
	return data;
}
