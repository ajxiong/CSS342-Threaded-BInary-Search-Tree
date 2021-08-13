#ifndef ASS5_TBST_H
#define ASS5_TBST_H

#include <iostream>

using namespace std;

class TBST;

class Node{
    friend class TBST;
    //pre-condition: takes an ostream out and a TBST object
    //post-condition: returns amn out ostream variable.
    //purpose: dispplays our tree in inorder traversal.
    friend ostream &operator<<(ostream &out, const TBST &tree);
    private:
    //pre-condition: takes an integer value
    //post-condition: returns no variables
    //purpose: sets pointer variables to nullptr, 
    //while assigning the value argument to the data global variable
    explicit Node(int value);
    int data;
    Node *right;
    Node *left;
    //1 means we have a branch to a child,
    //0 means we dont have a branch to a child
    //thread variables check for branches, not threads.
    int left_thread;
    int right_thread;
}; 

class TBST {

    //pre-condition: takes an ostream out and a TBST object
    //post-condition: returns amn out ostream variable.
    //purpose: dispplays our tree in inorder traversal.
    friend ostream &operator<<(ostream &out, const TBST &tree);

    private:
    //private root pointer
    Node* root;

    //pre-condition: takes a const int value
    //post-condition: returns a Node* from our tree. 
    //purpose: searchs for and returns a node based on 
    //the value given to the method
    Node* containsNode(const int &value);

    //pre-condition: takes a Node pointer variable
    //post-condition: returns a Node pointer variable.
    //purpose: method helps traverse through the tree in order
    //finds the next Node for the in order method.
    Node* inorder_helper (Node* pointer) const;

    //this is the preorder successor method from GFG
    //pre-condition: takes a Node* poiner variable
    //post-condition: returns a Node* pointer variable
    //purpose: method helps traverse through the tree in 
    //pre order. finds the next Node for the preorder method.
    Node* preorder_helper(Node* pointer);

    //pre-condition: takes a Node pointer variable
    //post-condition: returns a bool variable
    //purpose: case if our node to be removed is a leaf node
    //returns true upon successful, false otherwise.
    bool leafRemoval(Node* nodePtr);

    //pre-condition: takes a Node pointer variable
    //post-condition: returns a Node pointer variable
    //purpose: searchs for and returns the parent node of a node.
    //returns the node, nullptr otherwise. 
    //finds the parent node of a node/value
    Node* findParentNode(Node* nodePtr);

    //pre-condition: takes a Node pointer variable
    //post-condition: returns a bool variable
    //pupose: case if our node to be removed is a node with one child
    //returns true upon successful, false otherwise.
    bool node_With_One_Child_removal(Node*nodePtr);

    //pre-condition: takesa Node pointer variable
    //post-condition: returns a bool variable
    //purpose: case if our node to be removed is a node with two children
    //returns true upon successful, false otherwise.
    bool node_With_Two_Children_removal(Node* nodePtr);

    //pre-condition: takes no arguemnts
    //post-condition: no return variable
    //purpose: clears tree. can use in destrcutor if possible
    void clear();

    //pre-condition: takes an integer array and an int for array size
    //post-condition: no return variable
    //purpose: creates an array, finds the midpoint, then adds
    //that midpoint to the tree. recursively calls itself until
    //the array size is 1.
    void TBST_helper(int array1[], int array_size);

    //pre-condition: takes a Node pointer variable
    //post-condition: returns a Node pointer variable
    //purpose: searchs for and returns the successor node 
    //of a specific node
    Node* inSuccessor(Node* nodePtr);

    //pre-condition: takes a Node pointer variable
    //post-condition: returns a Node pointer variable
    //purpose: searchs for and returns the predecessor
    //node of a specific node
    Node* inPredecessor(Node* nodePtr);

    public:
    //pre-conditions: takes no arguemnts
    //post-condition: returns no varaibles
    //purpose: initliazes data fields to default variables
    TBST();

    //pre-condition: takes a const integer value
    //post-condition: returns no variables
    //purpose: takes a value as the size, creates an array based on that size,
    //then adds the midpoint of the array to the tree. calls TBST_helper() method.
    //constructor
    TBST(const int &value);

    //pre-condition: takes a TBST object
    //post-condition: returns no variables
    //purpose: takes a TBST object and copies the tree values
    //in the specific position the original tree was in. 
    //calls the assignment operator method overloader.
    //copy constructor
    TBST(const TBST &other);

    //pre-condition: takes no arguments
    //post-condition: returns no variables
    //purpose: destroys the tree object. calls the method clear.
    //destructor
    virtual ~TBST();

    //pre-condition: takes a constant integer value
    //post-condition: returns no variables
    //purpose: inserts a new node within the tree.
    //adds node to tree 
    void add(const int &value);

    //pre-condition: takes no arguments.
    //post-condition: returns no variables
    //purpose: displays our tree in inorder traversal
    //displays our tree by inorder traversal 
    virtual void display_inorder();

    //pre-condition: takes no arguments
    //post-condition: returns no variables
    //purpose: displays our tree in pre order traversal
    //displays our tree by preorder traversal
    void display_preorder();

    //pre=condition: takes a constant integer value
    //post-condition: returns a bool variable
    //purpose: removes a value. returns true upon successful,
    //false otherwise.
    //removes a node
    virtual bool remove(const int &value);

    //pre-condition: takes no arguments
    //post-condition: returns no variables.
    //purpose: removes all even values.
    void remove_all_even_values();

    //pre-condition: takes a constant integer value.
    //post-condition: returns a bool variable
    //purpose: searchs for a specific value within the tree.
    //returns true if the value is found, false otherwise
    bool contains(const int &value);

    //pre-condition: takes a TBST object
    //post-condition: returns a TBST object
    //purpose: copies the values of the TBST in the argument
    //and adds it to the new tree.
    //assignment operator overload method
    TBST& operator= (const TBST& Other);
};


#endif