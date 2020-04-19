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
	Node* next;
	if (tmp == NULL)
		return "DNE";
	//if count>1, dont delete from BST
	if (tmp->count > 1) {
		tmp->count--;
		return word + " deleted, new count = " + to_string(tmp->count);
	}
	//delete tmp
	while(true){	
		if (tmp->left!=NULL && tmp->right!=NULL) {
			next = successor(tmp);	//get successor
			tmp->data=next->data;		//swap data
			tmp->count = next->count;
			tmp=next;		
		}
		else if (tmp->left != NULL) {
			if(tmp->parent==NULL)
				this->root=tmp->left;
			else if (tmp->parent->left == tmp)
				tmp->parent->left = tmp->left;
			else
				tmp->parent->right = tmp->left;
			tmp->left->parent=tmp->parent;
			delete tmp;
			return word+" deleted";
		}
		else if (tmp->right != NULL){
			if(tmp->parent==NULL)
				this->root=tmp->right;
			else if (tmp->parent->left == tmp)
				tmp->parent->left = tmp->right;
			else
				tmp->parent->right = tmp->right;

			tmp->right->parent=tmp->parent;
			delete tmp;
			return word+" deleted";
		}
		else{
			if(tmp->parent==NULL)
				this->root=NULL;
			else if(tmp->parent->left==tmp)
				tmp->parent->left=NULL;
			else
				tmp->parent->right=NULL;

			delete tmp;
			return word+" deleted";
		}
	}
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
	Node* tmpr = tmp->right;
	if(!tmpr)
		return NULL;
	Node* tmpUp = tmp->parent;

	if (tmpr) {
		while (tmpr->left) {
			tmpr = tmpr->left;
		}
		return tmpr;
	}
	else if (!tmpr) {
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

	Node* tmpl = tmp->left;
	if(!tmpl)
		return NULL;
	Node* tmpUp = tmp->parent;

	if (tmpl) {
		while (tmpl->right) {
			tmpl = tmpl->right;
		}
		return tmpl;
	}
	else if (!tmpl) {
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
