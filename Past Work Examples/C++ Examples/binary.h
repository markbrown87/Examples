/**
 * @file binary.h
 * @author Modified by Mark Brown (provided by CS3610)
 * @brief .h file for class BinaryTree used for AVL list
 * @date October 06, 2016
 */

 
class BinaryTree{

public:
  BinaryTree() : root(NULL) {}
  ~BinaryTree() { 
    delete root;
  }
  

  void insert(const int key);
  void remove(const int key);

  void print_keys() const;
  void print_heights();
  
private:
  struct BinaryNode {
    BinaryNode(const int k) : key(k), bfactor(0), left(NULL), right(NULL) {}
    ~BinaryNode() {
      delete left;
      delete right;
      left = right = NULL;
    }

    int key;
	int bfactor;
    BinaryNode *left;
    BinaryNode *right;
  };

  BinaryNode* root;
  
  void balanceFromRight(BinaryNode* &root);
  void balanceFromLeft(BinaryNode* &root);
  
  void rotateToLeft(BinaryNode* &root);
  void rotateToRight(BinaryNode* &root);
  
  void insert_helper(BinaryNode* &root, BinaryNode* parent, bool& isTaller);
  void remove_helper(int key, BinaryNode* parent, BinaryNode* &prev, bool& shorter);
  
  void print_keys_helper(BinaryNode* node) const;
  void print_heights_helper(BinaryNode* node, int count, int depth);

};
