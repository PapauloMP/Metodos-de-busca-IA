//
// Created by Marcos Paulo on 27/09/2022.
//

#ifndef TRABALHOIA_GRUPO9_SEARCHTREE_H
#define TRABALHOIA_GRUPO9_SEARCHTREE_H
#include "../Headers/Node.h"

class SearchTree{
public:
    SearchTree();
    ~SearchTree();
    Node* getNode(int state);
    //void insertNode(Node* anteriorState);
    void build(Node* node);
    int getTotalStates() const{return totalStates;};
    Node* getRoot(){return root;};



private:
    Node* root;
    int totalStates;
    bool applyRule(int rule, bool* x, bool* y);


};
#endif //TRABALHOIA_GRUPO9_SEARCHTREE_H
