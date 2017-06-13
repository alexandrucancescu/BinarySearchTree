#include "BinaryTree.hpp"
#include "Controller.hpp"
#include "tests.h"
#include "ConsoleUI.h"

#include <iostream>
#include <assert.h>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    BinaryTree<int> BST{};
    
    remove("ints.txt");
    Controller ctr{BST,"ints.txt"};
    
    //Testing with a vector and the BST
    vector<int> vect={841,1528,903,1422,546,363};
    sort(vect.begin(),vect.end());
    
    ctr.addElem(841);
    ctr.addElem(1528);
    ctr.addElem(903);
    ctr.addElem(1422);
    ctr.addElem(546);
    ctr.addElem(363);
    
    assert(vect[0]==ctr.getFirst());
    for(int i=1;i<=5;i++){
        assert(vect[i]==ctr.getNext());
    }

    ctr.deleteElem(841);
    
    vect.erase(vect.begin()+2);
    
    assert(vect[0]==ctr.getFirst());
    for(int i=1;i<=4;i++){
        assert(vect[i]==ctr.getNext());
    }
    
    cout<<"All tests passed!\n";
    
    ConsoleUI(ctr);
    
    return 0;
}
