//
//  Node.hpp
//  BST_HD
//
//  Created by Cancescu Alexandru on 01/06/16.
//  Copyright © 2016 Andu. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <iostream>

//Clasa Node implementeaza nodul din arbore.
//Pointerii rightN si leftN reprezinta fii.
//data reprezinta continutul nodului, sau cheia.
//upN ,am retinut si nodul parinte pentru usurinta in a implementa un ierator
template<class TElement>
class Node{
public:
    TElement data;
    Node* upN;
    Node* rightN;
    Node* leftN;
    //Constructorul. Initializeaza pointerii cu nullptr
    Node(TElement e): data{e} , rightN{nullptr} , leftN{nullptr} , upN{nullptr} {}
};

#endif /* Node_hpp */
