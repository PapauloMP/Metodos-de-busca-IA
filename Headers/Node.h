//
// Created by Marcos Paulo on 27/09/2022.
//

#ifndef TRABALHOIA_GRUPO9_NODE_H
#define TRABALHOIA_GRUPO9_NODE_H
#include <vector>

class Node{

public:
    Node(int state, int rank, const bool* origin, const bool* destination, int isTemp, int rule);
    ~Node();

    void setNextWidth(Node* p);
    void setNextDepth(Node* p);
    Node* getNextWidth();
    Node* getNextDepth();
    Node* getParent();
    int getState() const;
    bool* getOrigin();
    bool* getDestination();
    void listNextNodes();
    void setNextNodes(Node* node);
    std::vector<Node*> getNextNodes();
    int getRank() const;
    int getId() const;
    int getTemp();
    int getRule();


private:

    Node* nextWidth;
    Node* nextDepth;
    Node* parent;
    int state;
    int id{};
    int rank;
    int temp;
    /** origin e destination são dois vetores de seis posições, sendo cada uma específica para um único pinguim na ordem:
    [0] = pai vermelho / [1] = filho vermelho / [2] = pai verde / [3] = filho verde / [4] = pai azul / [5] = filho azul **/
    bool* origin;
    bool* destination;
    int rule;

public:
    std::vector<Node*> nextNodes;
};
#endif //TRABALHOIA_GRUPO9_NODE_H
