#include<iostream>
#include<stack>
#include <sstream>
#include <cctype>
#include<vector>
#include <string>
#include <algorithm>
using namespace std;



struct node{
        int data;
        node* left;
        node* right;
        node(int value){
            this->data = value;
            this->left = NULL;
            this->right= NULL;
        }
};

class BST{

    node* root;
    public:
    node* successor(node *current);
    void insert(int value);
    void insert(node *root,int value);
    bool remove(int value);
    node* deleteNode(node* root,int value);
    node* Search(int value);
    void  access(int value);
    void INorder(node* root);
    void preorder(node* root);
    void postorder(node* root);
    void print();
    

};



node* BST::Search(int value){
    node *current = root;
    while(current)
    {
        if(current->data == value)
            break;
        if(value > current->data)
            current = current->right;
        else
            current = current ->left;
    }
    return current;
}

void BST::access(int value){
    if(Search(value) == NULL)
        cout<<"Element not found"<<endl;
    else
        cout<<"Element accessed"<<endl;
    
}

node* BST::successor(node *current){
    node *successor = current->right;
    while(successor->left){
        successor = successor->left;
    }
    return successor;
}

void BST::insert(node *root,int value){
    if(value > root->data){
        if(!root -> right)
            root->right = new node(value);
        else
            insert(root->right,value);
    }
    else
    {
        if(!root->left)
        root->left = new node(value);
        else
            insert(root->left,value);

     }
    
}

void BST::insert(int value){
    if(!root){
        root = new node(value);
    }
    else
    {
        if(Search(value)){
            cout<<"Element already present"<<endl;
        }
        else{
            insert (root,value);
            cout<<"Element inserted"<<endl;
        }
    }
    
}

node* findmin(node* t){
    if(t== NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else 
        return findmin(t->left);
}

node* deleteNode(node* current, int value){
    node *temp;
    if(current==NULL)
        return NULL;
    else if (value < current->data)
        current->left = deleteNode(current->left,value);
    else if (value > current->data)
        current->right = deleteNode(current->right,value);
    else if(current->left && current->right ){
        temp = findmin(current->right);
        current->data = temp->data;
        current->right = deleteNode(current->right,current->data);
    }
    else{
        temp = current;
        if(current->left == NULL)
            current=current->right;
        else if(current->right == NULL)
            current = current-> left;
        delete temp;
    }
    return current;
} 


bool BST::remove(int value){
    if(!Search(value)){
    cout<<"Element not found"<<endl;
    return false;
    }
    else{
        this->root=deleteNode(root,value);
        cout<<"Element deleted"<<endl;
        return true;
    }

}

void BST::INorder( node* root){
    stack<node *>s;
    node *curr = root;
    while(curr != NULL || s.empty() == false){
        while(curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout<<curr->data<<" ";
        curr = curr->right;
    }

}

void BST:: preorder(node*  root){
     if (root == NULL) 
        return; 
    stack<node*> s;
    node* current=root;
    s.push(current);
    while(!s.empty()){
        current=s.top();
        cout<<current->data<<" ";
        s.pop();
        if(current->right){s.push(current->right);}
        if(current->left){s.push(current->left);}
    }
    
}

void BST:: postorder(node*  root){
    if (root == NULL) 
        return; 
  
    // Create two stacks 
    stack<node *> s1, s2; 
  
    // push root to first stack 
    s1.push(root); 
    node* node; 
  
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
        cout << node->data << " "; 
    } 
} 
  

void BST::print(){
    INorder(root);
    cout<<endl;
    preorder(root);
    cout<<endl;
    postorder(root);
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
            bst->remove(num);
            }
           
        
    }
}
