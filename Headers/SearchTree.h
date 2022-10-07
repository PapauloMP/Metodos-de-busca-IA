//
// Created by Marcos Paulo on 27/09/2022.
//

#ifndef TRABALHOIA_GRUPO9_SEARCHTREE_H
#define TRABALHOIA_GRUPO9_SEARCHTREE_H
#include "../Headers/Node.h"
#include <stack>
#include <fstream>

class SearchTree{
public:
    SearchTree();
    ~SearchTree();
    int getTotalStates() const{return totalStates;};
    Node* getRoot(){return root;};
    //void insertNode(Node* anteriorState);
    void build(Node* node);
    void printStack();
    void printOpened();
    void printClosed();
    bool search(int id, int rank);
    std::vector<Node*> breadthSearch(std::ofstream& outputFile);




private:
    Node* root;
    int totalStates;
    std::stack<int> stackState;
    std::vector<int> listOpened;
    std::vector<int> listClosed;

    bool applyRule(int rule, bool* x, bool* y, int* isTemp);
    bool auxSearch (Node* node, int& id, int& rank);
    std::vector<int> solveTempState(int temp);


};
#endif //TRABALHOIA_GRUPO9_SEARCHTREE_H
