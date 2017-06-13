//
//  tests.h
//  BST_HD
//
//  Created by Cancescu Alexandru on 22/06/16.
//  Copyright © 2016 Andu. All rights reserved.
//

#ifndef tests_h
#define tests_h

#include <iostream>
#include "BinaryTree.hpp"
#include "Controller.hpp"
#include <assert.h>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

void createTestFile(){
    remove("test");
    ofstream file("test.txt");
    file.close();
}

vector<int> getFile(){
    vector<int> v;
    std::ifstream fin("testCombo");
    while (!fin.eof()) {
        std::string i;
        getline(fin,i);
        if (fin.eof() || i=="") {
            break;
        }
        int val=stoi(i);
        v.push_back(val);
    }
    fin.close();
    return v;
}

void test(){
    mt19937 mt{ std::random_device{}() };
    uniform_int_distribution<> dist(0, 2000);
    
    vector<int> vect;
    BinaryTree<int> bst;
    
    createTestFile();
    Controller ctr{bst,"test"};
    
    int generateNr=40;
    int deleteNr  =32;
    
    //Adaug 2000 de numere generate random si in vectorul dinamic si in Arborele Binar prin
    //intermediul Controllerului
    cout<<"ADDING:"<<endl<<endl;
    for(int i=0;i<=generateNr;i++){
        int nr = dist(mt);
        vect.push_back(nr);
        cout<<nr<<endl;
        ctr.addElem(nr);
    }
    
    //Sortez vectorul
    sort(vect.begin(), vect.end());
    
    //Test pentru iteratorul arborelui. Verifica daca vectorul sortat are elementele in
    //aceasi ordine cu parcurgerea iteratorului in inordine
    assert(vect[0]==ctr.getFirst());
    for(int i=1;i<=generateNr;i++){
        assert(vect[i]==ctr.getNext());
    }
    
    cout<<endl<<"DELETING:"<<endl<<endl;
    for(int i=0;i<deleteNr;i++){
        int indx=dist(mt);
        indx%=(vect.size());
        
        int indxInt=int(indx);
        int elem=vect[indxInt];
        cout<<elem<<endl;
        
        vect.erase(vect.begin()+indx);
        
        ctr.deleteElem(elem);
    }
    
    assert(vect[0]==ctr.getFirst());
    for(int i=1;i<=generateNr-deleteNr;i++){
        assert(vect[i]==ctr.getNext());
    }
    
    remove("test");
    
    cout<<endl<<"Tests Done!"<<endl<<endl;
}

void testCombo(){
    
    //vector<int> vect=getFile();
    BinaryTree<int> bst;
    
    remove("testCombo");
    Controller ctr{bst,"testCombo"};
    
    ctr.addElem(1292);
    ctr.addElem(1681);
    ctr.addElem(721);
    ctr.addElem(424);
    ctr.addElem(867);
    ctr.addElem(1073);
    ctr.addElem(750);
//    ctr.addElem(600);
    //ctr.addElem(700);
    
    //ctr.deleteElem(555);
//    ctr.deleteElem(879);
//    ctr.deleteElem(1559);
//    ctr.deleteElem(366);
    
    
//    sort(vect.begin(), vect.end());
//    
//    assert(vect[0]==ctr.getFirst());
//    for(int i=1;i<=vect.size();i++)
//        assert(vect[i]==ctr.getNext());
//    
//    ctr.deleteElem(1217);
//    vect.erase(vect.begin()+1);
//    
//    assert(vect[0]==ctr.getFirst());
//    for(int i=1;i<=vect.size();i++)
//        assert(vect[i]==ctr.getNext());
}

#endif /* tests_h */
