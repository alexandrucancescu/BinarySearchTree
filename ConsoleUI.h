//
//  ConsoleUI.h
//  BST_HD
//
//  Created by Cancescu Alexandru on 24/06/16.
//  Copyright © 2016 Andu. All rights reserved.
//

#include <iostream>
#include "BinaryTree.hpp"
#include "Controller.hpp"
#include "tests.h"

#ifndef ConsoleUI_h
#define ConsoleUI_h

using namespace std;

void printMenu(){
    cout<<endl<<"1.Add"<<endl;
    cout<<"2.Delete"<<endl;
    cout<<"3.Update"<<endl;
    cout<<"4.First"<<endl;
    cout<<"5.Next"<<endl;
    cout<<"6.Elem"<<endl;
    cout<<"7.Print all inorder"<<endl;
    cout<<"8.Run Tests"<<endl;
}

void ConsoleUI(Controller& ctr){
    int cmd;
    while(true){
        printMenu();
        cout<<"CMD: ";
        cin>>cmd;
        if(cmd==1){
            cout<<endl<<"TElement: ";
            int elem;
            cin>>elem;
            ctr.addElem(elem);
        }
        if(cmd==2){
            cout<<endl<<"TElement: ";
            int elem;
            cin>>elem;
            ctr.deleteElem(elem);
        }
        if(cmd==3){
            int elem;
            int elemNew;
            cout<<endl<<"TElement: ";
            cin>>elem;
            cout<<endl<<"Update: ";
            cin>>elemNew;
            ctr.deleteElem(elem);
        }
        if(cmd==4){
            cout<<endl<<ctr.getFirst()<<endl;
        }
        if(cmd==5){
            cout<<endl<<ctr.getNext()<<endl;
        }
        if(cmd==6){
            cout<<endl<<ctr.getElement()<<endl;
        }
        if(cmd==7){
            cout<<endl;
            ctr.print();
            cout<<endl;
        }
        if(cmd==8){
            cout<<endl<<"Input how many tests to run and the program will generate random numbers";
            cout<<" and add them in the BST and a STL vector then assert the sorted vector=BST.iterator";
            cout<<endl<<endl<<"How many:";
            int i;
            cin>>i;
            for(int j=0;j<i;j++)
                test();
        }
    }
}


#endif /* ConsoleUI_h */
