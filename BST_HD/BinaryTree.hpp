#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdio.h>
#include "Node.hpp"

class BinaryTreeException{
    std::string error;
public:
    BinaryTreeException(std::string e): error{e}{}
    std::string getError(){return error;}
};


template <class TElement>
class Iterator;

template <class TElement>
class BinaryTree{
private:
    //Pointer catre nodul radacina
    Node<TElement>* root;
    //Dimensiunea arborelui in functie de numarul de noduri
    size_t nodes;
    
    //Functia de adaugare recursiva
    void addLeaf(Node<TElement>*& currNode,Node<TElement>* newNode,Node<TElement>* upNode);
    
    //Functia returneaza recursiv nodul de cea mai mica valoare din arborele parametru
    Node<TElement>* findMin(Node<TElement>* node);
    
    //Functia returneaza recursiv nodul de cea mai mare valoare din arborele parametru
    Node<TElement>* findMax(Node<TElement>* node);
    
    //Functia returneaza recursiv pointer catre nodul cu valoarea data ca si parametru
    //din subarborele node.
    //Am ales sa dau ca si parametru un int deoarece arborele contine elemente de tip
    //TComparabil si obiectele pe care le stochez au definit operatorii < , > , <=, >=
    //in functie de int
    TElement findC(Node<TElement>* node,int c);
    
    //Returneaza pointer catre nodul care contine TElementul e din arborele node
    Node<TElement>* findNode(Node<TElement>* node,TElement e);
    
    //Sterge arborele
    void clear(Node<TElement>* n);
public:
    friend class Iterator<TElement>;
    //Constructor
    BinaryTree(): root{nullptr} , nodes{0}{}
    //Destructor
    ~BinaryTree(){clear(root);}
    
    void addElement(TElement const& e);
    void deleteElement(TElement const &e);
    
    //Functii de printare a intregului arbore
    void print(){
        iterate(root);
    }
    
    //Functia de iterare recursiva si printare a intregului arbore
    void iterate(Node<TElement>* node){
        if(node!=nullptr){
            iterate(node->leftN);
            std::cout<<node->data<<" ";
            iterate(node->rightN);
        }
    }
    
    void update(TElement const& e,TElement const&eNew);
    
    size_t size(){return nodes;}
    
    bool empty(){return root==nullptr;};
    
    Node<TElement>* getMin();
    
    TElement findElement(int compare);
    
    Iterator<TElement> iterator();
    
    Iterator<TElement>* iteratorP();
};

template<class TElement>
void BinaryTree<TElement>::clear(Node<TElement>* n){
    if(n!=nullptr){
        clear(n->rightN);
        clear(n->leftN);
        delete n;
    }
}

template<class TElement>
TElement BinaryTree<TElement>::findElement(int compare){
    return findC(root,compare);
}

template<class TElement>
TElement BinaryTree<TElement>::findC(Node<TElement>* node,int c){
    if(!(node->data < c) && !(node->data > c))
        return node->data;
    else
        if(node->data < c && node->rightN!=nullptr)
            return findC(node->rightN,c);
        else if(node->data > c && node->leftN!=nullptr)
            return findC(node->leftN,c);
    throw BinaryTreeException("The element does not exist!");
}

//Finds the node with the TElement e in the subtree node
template<class TElement>
Node<TElement>* BinaryTree<TElement>::findNode(Node<TElement>* node,TElement e){
    if(node->data == e)
        return node;
    if(e > node->data && node->rightN!=nullptr)
        return findNode(node->rightN,e);
    else if(e < node->data && node->leftN!=nullptr)
        return findNode(node->leftN,e);
    return nullptr;
}

template<class TElement>
void BinaryTree<TElement>::update(TElement const& e,TElement const&eNew){
    Node<TElement>* nd=findNode(root, e);
    if (nd==nullptr)
        throw BinaryTreeException("The element does not exists to be updated!");
    nd->data=eNew;
}

template<class TElement>
Node<TElement>* BinaryTree<TElement>::findMin(Node<TElement>* node){
    if(root==nullptr)
        return nullptr;
    if(root->leftN==nullptr && root->rightN==nullptr)
        return root;
    if(node->leftN!=nullptr)
        return findMin(node->leftN);
    return node;
}

template<class TElement>
Node<TElement>* BinaryTree<TElement>::findMax(Node<TElement>* node){
    if(root==nullptr)
        return nullptr;
    if(root->leftN==nullptr && root->rightN==nullptr)
        return root;
    if(node->rightN!=nullptr)
        return findMax(node->rightN);
    return node;
}

template<class TElement>
void BinaryTree<TElement>::deleteElement(TElement const &e){
    Node<TElement>* nd=findNode(root, e);
    if (nd==nullptr)
        throw BinaryTreeException("The element does not exists to be deleted!");
    Node<TElement>* parent=nd->upN;
    
    //Daca nodul e radacina
    if(nd==root){
        
        //Radacina nu are niciun fiu. Este singurul element din arbore
        if(nd->rightN==nullptr && nd->leftN==nullptr){
            root=nullptr;
        }
        
        //Radacina are doar un fiu, drept sau stang
        //Arborele devine subarborele drept sau stang
        else if((nd->rightN==nullptr && nd->leftN!=nullptr) || (nd->rightN!=nullptr && nd->leftN==nullptr)){
            if(nd->rightN==nullptr){
                root->leftN->upN=nullptr;
                root=root->leftN;
            }else{
                root->rightN->upN=nullptr;
                root=root->rightN;
            }
        }
        
        //Radacina are doi fii
        else if(nd->rightN!=nullptr && nd->rightN!=nullptr){
            
            //Nodul minim din sbarborele drept
            Node<TElement>* min=findMin(nd->rightN);
            
            //Parintele nodului minim din dreapta
            Node<TElement>* minP=min->upN;
            
            //inlocuiesc
            root->data=min->data;
            
            //sterg min
            if(minP->rightN==min){
                minP->rightN=min->rightN;
                if(min->rightN!=nullptr)
                    minP->rightN->upN=minP;
            }
            else{
                minP->leftN=min->rightN;
                if(min->rightN!=nullptr)
                    minP->leftN->upN=minP;
            }
        }
        
        nodes--;
        return;
    }
    
    //Daca e frunza sterg pointerul din parinte
    else if(nd->rightN==nullptr && nd->leftN==nullptr){
        if(parent->leftN == nd)
            parent->leftN=nullptr;
        if(parent->rightN == nd)
            parent->rightN=nullptr;
        nodes--;
    }
    
    //Nodul are doar un fiu. Indrept pointerul din tatal nodului spre fiul nodului
    else if((nd->rightN==nullptr && nd->leftN!=nullptr) || (nd->rightN!=nullptr && nd->leftN==nullptr)){
        //Fiul se afla in stanga sub nodul de sters
        if(nd->rightN==nullptr)
            //Nodul de sters e in partea dreapta sub tata
            if(parent->rightN==nd){
                parent->rightN=nd->leftN;
                nd->leftN->upN=parent;
            }
            //Nodul de sters e in partea stanga sub tata
            else{
                parent->leftN=nd->leftN;
                nd->leftN->upN=parent;
            }
        //Fiul se afla in dreapta sub nodul de sters
        else
            if(parent->rightN==nd){
                parent->rightN=nd->rightN;
                nd->rightN->upN=parent;
            }
            else{
                parent->leftN=nd->rightN;
                nd->rightN->upN=parent;
            }
        nodes--;
    }
    
    //Nodul are doi fii. Inlocuiesc TELement cu TElement cel mai mic din subarborele drept
    //Sterg cel mai mic element din subarborele drept
    else if(nd->rightN!=nullptr && nd->rightN!=nullptr){
        
        //Nodul minim din sbarborele drept
        Node<TElement>* min=findMin(nd->rightN);
        
        //Parintele nodului minim din dreapta
        Node<TElement>* minP=min->upN;
        
        //inlocuiesc
        if(parent->rightN==nd){
            parent->rightN->data=min->data;
        }else{
            parent->leftN->data=min->data;
        }
        
        //sterg min
        if(minP->rightN==min){
            minP->rightN=min->rightN;
            if(min->rightN!=nullptr)
                minP->rightN->upN=minP;
        }
        else{
            minP->leftN=min->rightN;
            if(min->rightN!=nullptr)
                minP->leftN->upN=minP;
        }
        nodes--;
    }
    
}

template<class TElement>
void BinaryTree<TElement>::addLeaf(Node<TElement>*& currNode,Node<TElement>* newNode,Node<TElement>* upNode){
    if(currNode==nullptr){
        newNode->upN=upNode;
        currNode=newNode;
        nodes++;
        return;
    }
    if(newNode->data > currNode->data)
        addLeaf(currNode->rightN , newNode,currNode);
    else
        addLeaf(currNode->leftN , newNode,currNode);
    
}

template<class TElement>
void BinaryTree<TElement>::addElement(TElement const& e){
    Node<TElement> *newNode=new Node<TElement>(e);
    if(root==nullptr){
        root=newNode;
        nodes++;
        return;
    }
    if(newNode->data > root->data)
        addLeaf(root->rightN, newNode,root);
    else
        addLeaf(root->leftN, newNode,root);
}

template<class TElement>
Node<TElement>* BinaryTree<TElement>::getMin(){
    return findMin(root);
}

template<class TElement>
Iterator<TElement> BinaryTree<TElement>::iterator(){
    return Iterator<TElement>{*this};
}

template<class TElement>
Iterator<TElement>* BinaryTree<TElement>::iteratorP(){
    return new Iterator<TElement>(*this);
}

template <class TElement>
class Iterator{
private:
    BinaryTree<TElement>& BST;
    Node<TElement>* lastVisit;
    Node<TElement>* currentNode;
    
    Iterator(BinaryTree<TElement>& bs): BST{bs}{
        first();
        lastVisit=nullptr;
    }
    
    Node<TElement>* begin(){
        return BST.findMin(BST.root);
    }
    
    Node<TElement>* end(){
        return BST.findMax(BST.root);
    }
public:
    friend class BinaryTree<TElement>;
    
    TElement element(){
        if(currentNode==nullptr){
            if(currentNode==begin())
                throw BinaryTreeException("The BinaryTree is empty!");
            else
                currentNode=begin();
        }
        return currentNode->data;
    }
    
    void first(){
        currentNode=begin();
    }
    
    void last(){
        currentNode=end();
    }
    
    bool nextValid(){
        return !(currentNode==end());
    }
    
    bool valid(){
        return !(currentNode==nullptr);
    }
    
    void print(){
        BST.print();
    }
    
    void next(){
        if(currentNode==nullptr || BST.root ==nullptr){
            throw BinaryTreeException("The BinaryTree is empty!");
        }
        if(currentNode==end())
            throw BinaryTreeException("Last Element!");
        bool flag=false;
        while(flag==false){
            if(currentNode->rightN != nullptr && lastVisit!= currentNode->rightN){
                lastVisit=currentNode;
                currentNode=BST.findMin(currentNode->rightN);
                flag=true;
            }
            else if(currentNode->upN != nullptr && currentNode==currentNode->upN->leftN){
                lastVisit=currentNode;
                currentNode=currentNode->upN;
                flag=true;
            }
            else if(currentNode->upN != nullptr && currentNode==currentNode->upN->rightN){
                lastVisit=currentNode;
                currentNode=currentNode->upN;
            }
        }
    }
    
    void prev(){
        if(currentNode==nullptr || BST.root ==nullptr){
            throw BinaryTreeException("The BinaryTree is empty!");
        }
        if(currentNode==begin())
            throw BinaryTreeException("First Element!");
        bool flag=false;
        while(flag==false){
            if(currentNode->rightN != nullptr && lastVisit!= currentNode->rightN){
                lastVisit=currentNode;
                currentNode=BST.findMin(currentNode->rightN);
                flag=true;
            }
            else if(currentNode->upN != nullptr && currentNode==currentNode->upN->leftN){
                lastVisit=currentNode;
                currentNode=currentNode->upN;
                flag=true;
            }
            else if(currentNode->upN != nullptr && currentNode==currentNode->upN->rightN){
                lastVisit=currentNode;
                currentNode=currentNode->upN;
            }
        }
    }
};

#endif /* BinaryTree_h */
