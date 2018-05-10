/**
 * @file binary.cpp
 * @author Modified by Mark Brown (provided by CS3610)
 * @brief functions for class binaryTree
 * @date October 06, 2016
 */

#include <iostream>
#include "binary.h"
using namespace std;

//******* INSERT
void BinaryTree::insert(const int key) {
	bool isTaller = false;
	BinaryNode* node;
	
	node = new BinaryNode(key);
	insert_helper(root, node, isTaller);
}


void BinaryTree::insert_helper(BinaryNode* &root, BinaryNode* parent, bool& isTaller) {

  if(root == NULL){
	 root = parent;
	 isTaller = true;
  }
  
  else if (root -> key == parent->key)
	  cout << "No Duplicates" << endl;
  
  else if (root->key > parent->key){
	  insert_helper(root->left, parent, isTaller);
	  
	  if(isTaller)
		  switch (root->bfactor){
				case -1:
					balanceFromLeft(root);
					isTaller = false;
					break;
				case 0:
					root->bfactor = -1;
					isTaller = true;
					break;
				case 1:
					root->bfactor = 0;
					isTaller = false;
		  }
  }
  
  else{
	  insert_helper(root->right, parent, isTaller);
	  
	  if(isTaller)
		  switch (root->bfactor){
				case -1:
					root->bfactor = 0;
					isTaller = false;
					break;
				case 0:
					root->bfactor = 1;
					isTaller = true;
					break;
				case 1:
					balanceFromRight(root);
					isTaller = false;
		  }
  }

}
void BinaryTree::rotateToLeft(BinaryNode* &root){
	BinaryNode* pointer;
	
	if(root == NULL)
		cout << "Error finding parent: 404" << endl;
	else if (root->right == NULL)
		cout << "Error: No right subtree to rotate" << endl;
	else{
		pointer = root->right;
		root->right= pointer->left;
		pointer->left= root;
		root = pointer;
	}
}

void BinaryTree::rotateToRight(BinaryNode* &root){
	BinaryNode* pointer;
	
	if(root == NULL)
		cout << "Error finding parent: 404" << endl;
	else if (root->right == NULL)
		cout << "Error: No left subtree to rotate" << endl;
	else{
		pointer = root->left;
		root->left = pointer->right;
		pointer->right= root;
		root = pointer;
	}
}

void BinaryTree::balanceFromLeft(BinaryNode* &root){
	BinaryNode* pointer;
	BinaryNode* w;
	
	pointer = root->left;
	
	switch(pointer->bfactor){
		case -1:
			root->bfactor = 0;
			pointer->bfactor = 0;
			rotateToRight(root);
			break;
		case 0:
			cout << "Error: Cannot balance tree" << endl;
			break;
		case 1:
			w = pointer->right;
			switch(w->bfactor){
				case -1:
					root->bfactor = 1;
					pointer->bfactor = 0;
					break;
				case 0:
					root->bfactor = 0;
					pointer->bfactor  =0;
					break;
				case 1:
					root->bfactor = 0;
					pointer->bfactor =-1;
			}
			w->bfactor=0;
			rotateToLeft(pointer);
			root->left = pointer;
			rotateToRight(root);
	}
}

void BinaryTree::balanceFromRight(BinaryNode* &root){
	BinaryNode* pointer;
	BinaryNode* w;
	
	pointer = root->right;
	
	switch(pointer->bfactor){
		case -1:
			w = pointer->left;
			switch(w->bfactor){
				case -1:
					root->bfactor =0;
					pointer->bfactor = 1;
					break;
				case 0:
					root->bfactor = 0;
					pointer->bfactor  =0;
					break;
				case 1:
					root->bfactor = -1;
					pointer->bfactor =0;
				}
			w->bfactor=0;
			rotateToRight(pointer);
			root->right = pointer;
			rotateToLeft(root);
			break;
			
		case 0:
			cout << "Error: Cannot balance tree" << endl;
			break;
		case 1:
			root->bfactor = 0;
			pointer->bfactor = 0;
			rotateToLeft(root);
	}
}

//******* REMOVE 
void BinaryTree::remove(const int key) {

	bool shorter = false;
	BinaryNode* tmp;
	tmp = root;
	remove_helper(key, root, tmp, shorter);

}

void BinaryTree::remove_helper(int key, BinaryNode* parent, BinaryNode* &prev, bool& shorter){
	
	if (parent == NULL)
		return;
	
	if (key < parent->key)
		remove_helper(key, parent->left, parent, shorter);
	
	else if (key > parent->key)
		remove_helper(key, parent->right, parent, shorter);
	
	else{
		if(parent->left == NULL || parent->right == NULL){
			delete parent;
			prev = NULL;
			shorter = true;
		}
		else if (parent->left != NULL || parent->right == NULL){
			BinaryNode* tmp;
			tmp = parent;
			parent = parent->left;
			delete tmp;
			prev->left = parent;
			shorter = true;
		}
		else if (parent->left == NULL || parent->right != NULL){
			BinaryNode* tmp;
			tmp = parent;
			parent = parent->right;
			delete tmp;
			prev->right = parent;
			shorter = true;
		}
		else{
			if(prev == parent){
				
			}
		}
	}
	
}

//********** PRINT
void BinaryTree::print_keys() const {
  print_keys_helper(root);
  cout << endl;
}

void BinaryTree::print_keys_helper(BinaryNode* node) const {
  if (node == NULL)
    return;

  print_keys_helper(node->left);
  cout << node->key << " ";
  print_keys_helper(node->right);
}

void BinaryTree::print_heights(){

  //** Implement an inorder traversal to
  //** print the height of each node
	int count = 1;
	int depth = 1;
	print_heights_helper(root, count, depth);
	cout << endl;
  
  ///same as above print_keys_helper BUT when you go into a recursive call it adds to the count and when it exits it removes from the count. Print them as soon as you count them.

}

void BinaryTree::print_heights_helper(BinaryNode* node, int count, int depth){
	/*
	if null
	plus [both]
		recL
	minus[depth]
	cout
	plus[depth]
		recR
	minus[depth]
	*/
	if (node == NULL)
		return;
	
	depth++;
	count++;
	print_heights_helper(node->left, count, depth);
	
	
}
