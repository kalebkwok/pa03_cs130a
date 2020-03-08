#include<iostream>
#include<stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include<vector>
using namespace std; 
  
// An AVL tree node  
class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};  

class BST
{
    public:
        Node* head;
        int max(int a, int b);  
        int height(Node *N);
        Node* newNode(int key);
        Node* rightRotate(Node *y);
        Node* leftRotate(Node *x);
        int getBalance(Node *N); 
        Node* minValueNode(Node* node);
        Node* insert(Node* node, int key);
        bool insert(int key);
        Node* deleteNode(Node* root, int key);
        bool deleteNode(int key);
        Node* Search(int value);
        void access(int value);
        void INorder( Node* root);
        void preorder(Node* root);
        void postorder(Node* root);
        void print();

};

  
// A utility function to get maximum 
// of two integers    
// A utility function to get height  
// of the tree  
int BST::height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  
// A utility function to get maximum 
// of two integers  
int BST:: max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  
/* Helper function that allocates a  
   new node with the given key and  
   NULL left and right pointers. */
Node* BST::newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return(node);  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
Node* BST::rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
Node* BST::leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int BST::getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) -  
           height(N->right);  
}  
  
Node* BST::insert(Node* node, int key)  
{  
    /* 1. Perform the normal BST rotation */
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else // Equal keys not allowed  
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  
                           height(node->right));  
  
    /* 3. Get the balance factor of this  
        ancestor node to check whether  
        this node became unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, 
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}  
  
/* Given a non-empty binary search tree,  
return the node with minimum key value  
found in that tree. Note that the entire  
tree does not need to be searched. */
Node* BST::minValueNode(Node* node)  
{  
    Node* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  
  
// Recursive function to delete a node  
// with given key from subtree with  
// given root. It returns root of the  
// modified subtree.  
Node* BST::deleteNode(Node* root, int key)  
{  
      
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the key to be deleted is smaller  
    // than the root's key, then it lies 
    // in left subtree  
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            Node* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // key to this node  
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right,  
                                     temp->key);  
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(height(root->left),  
                           height(root->right));  
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  

bool BST::insert(int key){
    if (Search(key)){
        cout<<"Element already present"<<endl;
        return true;
    }
    head = insert(head, key);
    cout<<"Element inserted"<<endl;
    return false;

}


bool BST::deleteNode(int key){
    if (Search(key)==NULL){
        cout<<"Element not found"<<endl;
        return false;
    }
    head = deleteNode(head,key);
    cout<<"Element deleted"<<endl;
}


Node* BST::Search(int value){
    Node *current = head;
    while(current)
    {
        if(current->key == value)
            break;
        if(value > current->key)
            current = current->right;
        else
            current = current ->left;
    }
    return current;
}

void  BST::access(int value){
    if(Search(value) == NULL)
        cout<<"Element not found"<<endl;
    else
        cout<<"Element accessed"<<endl;
    
}


void BST::INorder( Node* root){
    stack<Node *>s;
    Node *curr = root;
    while(curr != NULL || s.empty() == false){
        while(curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout<<curr->key<<" ";
        curr = curr->right;
    }

}

void BST:: preorder(Node*  root){
     if (root == NULL) 
        return; 
    stack<Node*> s;
    Node* current=root;
    s.push(current);
    while(!s.empty()){
        current=s.top();
        cout<<current->key<<" ";
        s.pop();
        if(current->right){s.push(current->right);}
        if(current->left){s.push(current->left);}
    }
    
}

void BST:: postorder(Node*  root){
    if (root == NULL) 
        return; 
  
    // Create two stacks 
    stack<Node *> s1, s2; 
  
    // push root to first stack 
    s1.push(root); 
    Node* node; 
  
    // Run while first stack is not empty 
    while (!s1.empty()) { 
        // Pop an item from s1 and push it to s2 
        node = s1.top(); 
        s1.pop(); 
        s2.push(node); 
  
        // Push left and right children 
        // of removed item to s1 
        if (node->left) 
            s1.push(node->left); 
        if (node->right) 
            s1.push(node->right); 
    } 
  
    // Print all elements of second stack 
    while (!s2.empty()) { 
        node = s2.top(); 
        s2.pop(); 
        cout << node->key << " "; 
    } 
} 
  


void BST::print(){
    preorder(head);
    cout<<endl;
    INorder(head);
    cout<<endl;
    postorder(head);
    cout<<endl;

}


vector<string> getInput(string s)
{
    vector<string> result;
    stringstream ss(s);
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ','); //get first string delimited by comma
        result.push_back(substr);
    }
    return result;
}

int getNum(string s)
{
    string temp;
    for (auto item : s)
    {
        if (isdigit(item) || item == '-')
        {
            temp += item;
        }
    }
    if (temp != "")
    {
        return stoi(temp);
    }
    return -1;
}

int main(int argc, char *argv[])
{
    
    string s = argv[1];
    int num;
    vector<string> sep = getInput(s);
    BST *bst = new BST();
    for (auto item : sep)
    {
        // cout << item << endl;
        if (item.find("insert") != -1)
        {
            //insert
            num = getNum(item);
            bst->insert(num);
        }
        else if (item.find("access") != -1)
        {
            //look up
            num = getNum(item);
            bst->access(num);
        }
        else if (item.find("print") != -1)
        {
            // print
            bst->print();
        }
        else if (item.find("delete") != -1)
            {
            num = getNum(item);
            bst->deleteNode(num);
            }
           
        
    }
}