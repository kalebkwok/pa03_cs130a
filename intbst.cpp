// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n) return;
    printInOrder(n->left);
    cout<<n->info<<" ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout<<n->info<<" ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n== NULL) {
        return 0;
    }
    return n->info+sum(n->right)+sum(n->left); // REPLACE THIS NON-SOLUTION
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n== NULL) {
        return 0;
    }
    return 1+count(n->right)+count(n->left); // REPLACE THIS NON-SOLUTION
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n==NULL)
        return NULL;
    if (n->info == value)
        return n;
    
    if (n->info < value)
        return getNodeFor(value,n->right);
    
    else if (n->info > value)
        return getNodeFor(value,n->left);
    
    return NULL;
}

bool IntBST::contains(int value) const {
    if(getNodeFor(value,root) == 0)
        return false;
    else
        return true;

}


bool IntBST::helpercontains(int value, Node* n) const{
    Node* a =getNodeFor(value,n);
if(a== NULL){
    return 0;
}
if(a->info == value)
    return 1;
return(helpercontains(value,n->left)||helpercontains(value,n->right));
}


// returns true if value is in the tree; false if not


// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n =getNodeFor(value,root);
    if (n == NULL){
    return NULL;
    }
    else if(n->left){
        Node *tmp = n->left;
        while(tmp ->right)
            tmp = tmp->right;
        return tmp;
    }
    else {
        Node *tmp = n->parent;
        while(tmp && tmp->info >= n->info)
            tmp = tmp->parent;
        if(tmp == NULL)
            return NULL;
        else
            return tmp;
        }
    

}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* v= getPredecessorNode(value);
    if(v == NULL){
    return 0; 
    }
    else
    return v->info;
    
}


// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n =getNodeFor(value,root);
    
    if (n == NULL){
        return NULL;
    }
    else if(n->right){
        Node *tmp = n->right;
        while(tmp ->left)
            tmp = tmp->left;
                return tmp;
    }
    else {
        Node *amp = n->parent;
        while( amp && amp->info <= n->info)
            amp = amp->parent;
        if(amp == NULL) {
            return NULL;
        }
        else {
            return amp;
        }
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* v= getSuccessorNode(value);

    if(v==NULL){
    return 0; 
    }
    else{
    return v->info;
    }
    
}



// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
     Node* n =getNodeFor(value,root);
    if(!n->left && !n->right){
        if(!n->parent){
            clear(root);
            root = NULL;
            return true;
        }
        if(n->parent->left == n)
            n->parent->left = NULL;
        else 
            n->parent->right = NULL;
        n->parent = NULL;
        delete n;
    }
    else if(n->left && !n->right){

        if(n->parent->left == n){
                n->parent->left = n->left;
                n->left->parent = n->parent;
                
            }
            else{
                n->parent->right = n->left;
                n->left->parent = n->parent;
                
            }
            n->parent = NULL;
            delete n;
        }
    else if(!n->left && n->right){

        if(n->parent->left == n){
            n->parent->left = n->right;
            n->right->parent = n->parent;
            
            }
            else{
                n->parent->right = n->right;
                n->right->parent = n->parent;
                
                
            }
            n->parent = NULL;
            delete n;
        }

    else if(n->left && n->right){
        Node* temp = getSuccessorNode(value);
        int number = temp->info;
        temp->info = n->info;
        n->info = number;
        if(!temp->left && !temp->right){
            if(temp->parent->left == temp)
                temp->parent->left = NULL;
            else
                temp->parent->right = NULL;
            
            temp->parent = NULL;
            delete temp;
            
        }
        else if(temp->left && !temp->right){
            if(temp->parent->left == temp){
                temp->parent->left = temp->left;
                temp->left->parent = temp->parent;
                
            }
            else{
                temp->parent->right = temp->left;
                temp->left->parent = temp->parent;
                
            }
            temp->parent = NULL;
            delete temp;
        }
        else if(!temp->left && temp->right){
            if(temp->parent->left == temp){
                temp->parent->left = temp->right;
                temp->right->parent = temp->parent;
                
            }
            else{
                temp->parent->right = temp->right;
                temp->right->parent = temp->parent;
                
                
            }
            temp->parent = NULL;
            delete temp;
        }
    

    }
    else if(n->left == NULL && n->right == NULL) {
        n->parent = NULL;
        root = NULL;
        delete n;
    }
    return true;
}
