#ifndef TRABALHOIA_GRUPO9_SEARCHTREE_H
#define TRABALHOIA_GRUPO9_SEARCHTREE_H
#include "../Headers/Node.h"
#include <stack>
#include <fstream>

class SearchTree{
public:
    SearchTree(const std::string& outputFile);
    ~SearchTree();
    int getTotalStates() const{return totalStates;};
    Node* getRoot(){return root;};

    void build(Node* node);
    void printStack(std::stack<Node*>& solutionPath);
    void printOpened();
    void printClosed();
    bool search(int id, int rank);
    bool search(Node* node, int id, int rank);
    void free(Node* node);

    std::stack<Node*> breadthSearch();
    std::stack<Node*> deepFirstSearch();
    std::stack<Node*> backtrackingSearch();
    std::stack<Node*> greedySearch();
    std::stack<Node*> uniformSearch();
    std::stack<Node*> AStarSearch();



private:
    Node* root;
    std::ofstream outputFile;
    std::string edgeAttribute = "[color=red,penwidth=3.0] [fontsize=20]";
    int totalStates;

    std::stack<int> stackState;
    std::vector<int> listOpened;
    std::vector<int> listClosed;

    bool applyRule(int rule, bool* x, bool* y, int* isTemp);
    bool auxSearch (Node* node, int& id, int& rank);
    std::vector<int> solveTempState(int temp);
    void auxBacktracking(Node* node, std::vector<Node*>& searchResult, std::stack<Node*>& solutionPath, bool& solution);


};
#endif //TRABALHOIA_GRUPO9_SEARCHTREE_H
