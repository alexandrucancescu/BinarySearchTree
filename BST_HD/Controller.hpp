//
//  Controller.hpp
//  BST_HD
//
//  Created by Cancescu Alexandru on 21/06/16.
//  Copyright © 2016 Andu. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>

#include <vector>
#include <string>

#include "BinaryTree.hpp"

class Controller{
private:
    BinaryTree<int>& BST;
    Iterator<int> it=BST.iterator();
    std::string fName;
    
    void addElemFile(int i){
        BST.addElement(i);
    }
public:
    Controller(BinaryTree<int>& b,std::string fN): BST{b} , fName{fN} {
        loadFile();
    }
    
    
    void addElem(int i){
        BST.addElement(i);
        saveFile();
    }
    
    void print(){
        BST.print();
    }
    
    void update(int e,int eNew){
        BST.update(e, eNew);
        saveFile();
    }
    
    int find(int c){
        return BST.findElement(c);
    }
    
    void deleteElem(int i){
        if(BST.size()>1){
            BST.deleteElement(i);
            saveFile();
        }else if(BST.size()==1){
            BST.deleteElement(i);
            saveFile();
        }
    }
    
    int getFirst(){
        //Iterator<Motorcycle> it=BST.iterator();
        it.first();
        return it.element();
    }
    
    int getElement(){
        return it.element();
    }
    
    int getSize(){
        return int(BST.size());
    }
    
    int getNext(){
        it.next();
        return it.element();
    }
    
    void loadFile();
    void saveFile();
};

#endif /* Controller_hpp */
