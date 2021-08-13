#include <iostream>
#include <cassert>
#include "tbst.h"

using namespace std;

//pre-condition: takes no variables
//post-condition: returns no variables
//purpose: asks user for N input, then 
void test1(){
    cout << "please enter how many nodes you want in your binary search tree" << endl;
    int num_of_nodes;
    cin >> num_of_nodes;
    TBST tree1(num_of_nodes);
    cout << "original tree" << endl;
    cout << tree1 << endl;
    TBST tree2(tree1);
    //tree2.display_preorder();
    tree2.remove_all_even_values();
    cout << "new tree" << endl;
    cout << tree2 << endl;
}

void test2(){
    TBST tree2(6);
    //tree2.add(1);
    tree2.add(4);
    //tree2.add(10);
    tree2.add(8);
    //tree2.add(2);
    tree2.add(3);
    tree2.add(5);
    //cout << tree2 << endl;
    //tree2.add(7);
    //tree2.add(9);
    //tree2.add(7);
    //tree2.add(15);
    //tree2.add(12);
    //tree2.add(16);
    //tree2.display_inorder();
    //cout << "displaying from method" << endl;
    //tree2.display_inorder();
    //tree2.remove(8);
    //tree2.remove(10);
    //cout << "new tree" << endl;
    //tree2.display_inorder();
    TBST tree3(tree2);
    //tree3.add(8);
    //tree3.display_preorder();
    tree3.remove(6);
    tree3.remove(4);
    tree3.remove(8);
    //tree3.remove_all_even_values();
    //TBST tree3(tree2);
    //cout << "\nnew tree" << endl;
    tree3.display_inorder();
    //cout << "\ndisplay preorder" << endl;
    //tree3.display_preorder();
}

int main(){
    test1();
    //test2();
    cout << "Tests done." << endl;
    return 0;

     //enable clang tidy: scl enable llvm-toolset-7.0 bash DO THIS EVERY TIME YOU LOGIN SSH LABS
  //run clang tidy: clang-tidy *.cpp -- -std=c++14
  //check version for clang tidy: clang-tidy --version
  //to allow access to .sh files, do: chmod a+rwx <sh file name>.sh
  //generate a output.txt file? 
  //  ./simplecompile.sh > output.txt 2>&1
  //  ./create-output.sh > output.txt 2>&1 
  //  ./check-code-coverage.sh > output.txt 2>&1
  //compiles with no errors or flags with following command: g++ -g -std=c++11 -Wall -Wextra -Wno-sign-compare *.cpp
  //to use valgrind, use command: valgrind --leak-check=full ./<executable>
  //if permission denied, use the chmod command
  //USE THIS COMMAND TO CHECK FOR MEMORY LEAKS: valgrind --leak-check=full ./a.out
  //valgrind --leak-check=full --track-origins=yes ./a.out
}