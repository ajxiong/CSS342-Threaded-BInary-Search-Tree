#include <iostream>
#include "tbst.h"
#include <cassert>
#include <climits>

using namespace std;

ostream &operator<<(ostream &out, const TBST &tree){
    if(tree.root->left != tree.root){
        Node* traversing_pointer;
        traversing_pointer = tree.root->left;
        while(traversing_pointer->left_thread == 1){
            traversing_pointer = traversing_pointer->left;
        }
        while(traversing_pointer != tree.root){
            cout << traversing_pointer->data << endl;
            traversing_pointer = tree.inorder_helper(traversing_pointer);
        }
    }
    else{
        cout << "current tree is empty." << endl;
    }
    return out;
}


Node::Node(int value) : data{value} {
    right = left = nullptr;
    right_thread = left_thread = 0;
}

TBST::TBST(){
    root = new Node(INT_MAX);
    root->right_thread = 1;
    root->left_thread = 0;
    root->left = root;
    root->right = root;
}

TBST::TBST(const int &value) {
    if(value > 0){
        int array1_size = value;
        int array1 [value];
        for(int i = 0; i < array1_size; i++){
            array1[i] = i + 1;
        }
        int root_value = value / 2;
        //header root node??
        root = new Node(INT_MAX);
        root->right_thread = 1;
        root->left_thread = 0;
        root->left = root;
        root->right = root;
        add(array1[root_value]);
       
        TBST_helper(array1, value);
        for(int i = 0; i < value; i++){
            if((contains(array1[i])) == false && (array1[i] % 2 != 0))
                add(array1[i]);
        }
        for(int i = 0; i < value; i++){
            if(contains(array1[i]) == false)
                add(array1[i]);
        }
        //we still want to add our value we passed
        //to our constructor 
        //add(value);
    }
    else{
        cout << "value input invalid\nvalue must be greater than 0" << endl;
    }
}

void TBST::TBST_helper(int array1[], int array_size){
    if(array_size == 1){
        return;
    }
    else{
        int midpoint = array_size / 2; //this is 5
        int left_array2 [midpoint];
        int left_array2_size = midpoint;
        for(int i = 0; i < left_array2_size; i++){
            left_array2[i] = array1[i];
        }
        //find midpoint of left_array2, and create a new left node with the midpoint value
        if(contains(left_array2[(left_array2_size / 2)]) == false){
            //cout << "midpoint of left array is " << left_array2[(left_array2_size / 2)] << "\n" << endl;
            add(left_array2[(left_array2_size / 2)]);
        }
        int right_array3 [midpoint];
        int right_array3_size = midpoint;
        int counter = 0;
        for(int i = midpoint; i < array_size; i++){
            right_array3[counter] = array1[i];
            counter++;
        }
        if(contains(right_array3[(right_array3_size / 2)]) == false){
            add(right_array3[(right_array3_size / 2)]);
        }
        //cout << "\nleft array call" << endl;
        TBST_helper(left_array2, left_array2_size);
        //cout << "\nright array call" << endl;
        TBST_helper(right_array3, right_array3_size);
    }
}

TBST::TBST(const TBST &other){
    *this = other;
}

TBST::~TBST() {
    clear();
    delete root;
    root = nullptr;   
}

void TBST::add(const int &value) {
    if(root->left == root && root->right == root){
        Node* tempPtr = new Node(value);
        tempPtr->left = root->left;
        tempPtr->left_thread = root->left_thread;
        tempPtr->right_thread = 0;
        tempPtr->right = root->right;

        root->left = tempPtr;
        root->left_thread = 1;
        return;
    }
    Node* curPtr = root->left;
    while(1){
        if(curPtr->data < value){
            if(curPtr->right_thread == 0){
                Node* tempPtr = new Node(value);
                tempPtr->right = curPtr->right;
                tempPtr->right_thread = curPtr->right_thread;
                tempPtr->left_thread = 0;
                tempPtr->left = curPtr;

                curPtr->right_thread = 1;
                curPtr->right = tempPtr;
                return;
            }
            else{
                curPtr = curPtr->right;
            }
        }
        if(curPtr->data > value){
            if(curPtr->left_thread == 0){
                Node* tempPtr = new Node(value);
                tempPtr->left = curPtr->left;
                tempPtr->left_thread = curPtr->left_thread;
                tempPtr->right_thread = 0;

                tempPtr->right = curPtr;
                curPtr->left_thread = 1;
                curPtr->left = tempPtr;
                return;
            }
            else{
                curPtr = curPtr->left;
            }
        }
    }
}

void TBST::clear() {
    if(root->left != root){
        Node* traversing_pointer;
        traversing_pointer = root->left;
        while(traversing_pointer->left_thread == 1){
            traversing_pointer = traversing_pointer->left;
        }
        while(traversing_pointer != root){
            Node* nodetoDeletePtr = traversing_pointer;
            traversing_pointer = inorder_helper(traversing_pointer);
            delete nodetoDeletePtr;
            nodetoDeletePtr = nullptr;
        }
    }
}

void TBST::display_inorder() {
    if(root->left != root){
        Node* traversing_pointer;
        traversing_pointer = root->left;
        while(traversing_pointer->left_thread == 1){
            traversing_pointer = traversing_pointer->left;
        }
        while(traversing_pointer != root){
            cout << traversing_pointer->data << endl;
            traversing_pointer = inorder_helper(traversing_pointer);
        }
    }
    else{
        cout << "current tree is empty." << endl;
    }
}

Node* TBST::inorder_helper(Node *pointer) const {
    if(pointer->right_thread == 0){
        return pointer->right;
    }
    else{
        pointer = pointer->right;
    }
    while(pointer->left_thread == 1){
        pointer = pointer->left;
    }
    return pointer;
    }

bool TBST::remove(const int &value) {
    bool remove_success = false;
    if(contains(value) == true){
        Node* nodeToRemovePtr = containsNode(value);

        //first case is if the node we want to remove is a leaf
        if(nodeToRemovePtr->left_thread == 0 &&
        nodeToRemovePtr->right_thread == 0){
            remove_success = leafRemoval(nodeToRemovePtr);
        }
        //second case is if the node we want to remove has ONLY one child
        else if((nodeToRemovePtr->left_thread == 1 && 
        nodeToRemovePtr->right_thread == 0) || (nodeToRemovePtr->left_thread == 0
         && nodeToRemovePtr->right_thread == 1)){
            remove_success = node_With_One_Child_removal(nodeToRemovePtr);
        }
        //third case is if the node to be deleted has two children
        else if(nodeToRemovePtr->left_thread == 1 &&
        nodeToRemovePtr->right_thread == 1){
            remove_success = node_With_Two_Children_removal(nodeToRemovePtr);
        }
        else{
            cout << nodeToRemovePtr->data << endl;
        }
    }
    else{
        cout << "error removing node" << endl;
    }
    return remove_success;
}

bool TBST::leafRemoval(Node* nodePtr){
    bool leafRemoval_successful = false;
    Node* parentNode = findParentNode(nodePtr);
    //first case is if the root is the node we want to remove
    if(nodePtr == root->left){
        root->left = root;
        root->right = root;
        delete nodePtr;
        nodePtr = nullptr;
        leafRemoval_successful = true;
    }
    //second case if leaf ndoe is on the left side
    else if(nodePtr == parentNode->left){
        parentNode->left = nodePtr->left;
        parentNode->left_thread = 0;
        delete nodePtr;
        nodePtr = nullptr;
        leafRemoval_successful = true;
    }
    //second case if leaf node is on the right side
    else if(nodePtr == parentNode->right){
        parentNode->right = nodePtr->right;
        parentNode->right_thread = 0;
        delete nodePtr;
        nodePtr = nullptr;
        leafRemoval_successful = true;
    }
    return leafRemoval_successful;
}

bool TBST::node_With_One_Child_removal(Node* nodePtr){
    bool leafRemoval_successful = false;
    Node* parentNodePtr;
    Node* childPtr;
    if(nodePtr->left_thread == 1){
        childPtr = nodePtr->left;
    }
    else{
        childPtr = nodePtr->right;
    }
    if(nodePtr != root->left){
        parentNodePtr = findParentNode(nodePtr);
    }
    //first case if node to be deleted is root node
    if(nodePtr == root->left){
        root->left = childPtr;
    }
    else if(nodePtr == parentNodePtr->left){
        parentNodePtr->left = childPtr;
    }
    else{
        parentNodePtr->right = childPtr;
    }
    Node* successorPtr = inSuccessor(nodePtr);
    Node* predPtr = inPredecessor(nodePtr);
    if(nodePtr->left_thread == 1){
        predPtr->right = successorPtr;
        leafRemoval_successful = true;
    }
    else if(nodePtr->right_thread == 1){
        successorPtr->left = predPtr;
        leafRemoval_successful = true;
    }
    delete nodePtr;
    nodePtr = nullptr;
    return leafRemoval_successful;
}

Node* TBST::findParentNode(Node* nodePtr){
        Node* traversingPtr = root->left;
        while(traversingPtr != root){
            //cout << traversingPtr->data << endl;
            if(traversingPtr->left == nodePtr ||
            traversingPtr->right == nodePtr)
                return traversingPtr;
            else
                traversingPtr = preorder_helper(traversingPtr);
            }
    return nullptr;
}

bool TBST::node_With_Two_Children_removal(Node* nodePtr){
    bool remove_success = false;
    Node* succ = nodePtr->right;
    while(succ->left_thread != 0){
        succ = succ->left;
    }
    nodePtr->data = succ->data;
    if(succ->left_thread == 0 && succ->right_thread == 0){
        remove_success = leafRemoval(succ);
    }
    else{
        remove_success = node_With_One_Child_removal(succ);
    }
    return remove_success;
}

void TBST::remove_all_even_values(){
    if(root->left != root){
        Node* traversingPtr = root->left;
        while(traversingPtr != root){
            if(traversingPtr->data % 2 == 0){
                //cout << traversingPtr->data << endl;
                Node* nodeToDelete = traversingPtr;
                traversingPtr = preorder_helper(traversingPtr);
                remove(nodeToDelete->data);
            }
            else{
                traversingPtr = preorder_helper(traversingPtr);
            }
        }
    }
    else{
        cout << "current tree is empty." << endl;
    }
}

bool TBST::contains(const int &value){
    Node* traversing_pointer;
    traversing_pointer = root->left;
    while(traversing_pointer->left_thread == 1){
        traversing_pointer = traversing_pointer->left;
    }
    while(traversing_pointer != root){
        if(traversing_pointer->data == value)
            return true;
        else
            traversing_pointer = inorder_helper(traversing_pointer);
    }
    return false;
}

Node* TBST::containsNode(const int &value){
    if(contains(value) == true){
        Node* traversing_pointer;
        traversing_pointer = root->left;
        while(traversing_pointer->left_thread == 1){
            traversing_pointer = traversing_pointer->left;
        }
        while(traversing_pointer != root){
            if(traversing_pointer->data == value){
                return traversing_pointer;
            }
            else
                traversing_pointer = inorder_helper(traversing_pointer);
        }
    }
    else{
        cout << "error retriving node" << endl;
    }
    return nullptr;
}

void TBST::display_preorder(){
    Node* traversingPtr = root->left;
    while(traversingPtr != root){
        cout << traversingPtr->data << endl;
        traversingPtr = preorder_helper(traversingPtr);
    }
}

Node* TBST::preorder_helper(Node* pointer){
    if(pointer->left_thread ==1){
        return pointer->left;
    }
    while(pointer->right_thread == 0){
        pointer = pointer->right;
    }
    return pointer->right;
}

Node* TBST::inSuccessor(Node* nodePtr){
    if(nodePtr->right_thread == 0){
        return nodePtr->right;
    }
    nodePtr = nodePtr->right;
    while(nodePtr->left_thread == 1){
        nodePtr = nodePtr->left;
    }
    return nodePtr;
}

Node* TBST::inPredecessor(Node* nodePtr){
    if(nodePtr->left_thread == 0)
        return nodePtr->left;
    nodePtr = nodePtr->left;
    while(nodePtr->right_thread == 1){
        nodePtr = nodePtr->right;
    }
    return nodePtr;
}

TBST& TBST::operator= (const TBST& Other) {
    root = new Node(Other.root->data);
    root->right_thread = 1;
    root->left_thread = 0;
    root->left = root;
    root->right = root;
    Node* traversingPtr = Other.root->left;
    while(traversingPtr != Other.root){
        if(contains(traversingPtr->data) == true)
            continue;
        else{
            add(traversingPtr->data);
        }
        traversingPtr = preorder_helper(traversingPtr);
    }
    return *this;
}