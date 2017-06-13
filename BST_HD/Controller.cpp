//
//  Controller.cpp
//  BST_HD
//
//  Created by Cancescu Alexandru on 21/06/16.
//  Copyright © 2016 Andu. All rights reserved.
//

#include "Controller.hpp"
#include <fstream>

void Controller::loadFile(){
    std::ifstream fin(fName);
    while (!fin.eof()) {
        std::string i;
        getline(fin,i);
        if (fin.eof() || i=="") {
            break;
        }
        int val=stoi(i);
        addElemFile(val);
    }
    fin.close();
}

void Controller::saveFile(){
    std::ofstream fout(fName);
    
    Iterator<int> *itr=BST.iteratorP();
    
    if(itr->valid())
        fout<<itr->element()<<std::endl;
    while(itr->nextValid()){
        itr->next();
        fout<<itr->element()<<std::endl;
    }
    fout.close();
    
    delete itr;
}