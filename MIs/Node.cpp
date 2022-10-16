//
// Created by Marcos Paulo on 27/09/2022.
//
#include <iostream>
#include "../Headers/Node.h"
#include <cmath>
#include <iomanip>

Node::Node(int state, int rank, const bool* origin, const bool* destination, int isTemp, int rule){
    this->state = state;
    this->rank = rank;
    this->origin = new bool[6];
    this->destination = new bool[6];
    for (int i = 0; i < 6; i++) {
        this->origin[i] = origin[i];
        this->destination[i] = destination[i];
    }
    nextWidth = nullptr;
    nextDepth = nullptr;
    parent = nullptr;
    this->temp = isTemp;
    this->rule = rule;

    if(origin != nullptr && destination != nullptr) {
        for (int i = 0; i < 6; i++) {
            id += int((origin[i] * pow(2, i)) + (destination[i] * pow(2, i + 6)));
        }
    }
    if(id == 4032)
        std::cout << "No solucao! (estado: " << state << ")" << std::endl;

}
Node::~Node(){
    delete [] origin;
    delete [] destination;
}
int Node::getState() const{
    return state;
}
int Node::getRank() const {
    return rank;
}
int Node::getId() const {
    return id;
}
bool* Node::getDestination(){
    return destination;
}
bool* Node::getOrigin() {
    return origin;
}
std::vector<Node *> Node::getNextNodes() {
    return nextNodes;
}
void Node::setNextDepth(Node* p){
    nextDepth = p;
}
void Node::setNextWidth(Node *p) {
    nextWidth = p;
}
Node* Node::getNextWidth() {
    return nextWidth;
}
Node* Node::getNextDepth() {
    return nextDepth;
}
Node *Node::getParent() {
    return parent;
}
int Node::getTemp() {
    return temp;
}
int Node::getRule() {
    return rule;
}
void Node::setNextNodes(Node* node) {
    nextNodes.push_back(node);
    auto size = nextNodes.size();
    node->parent = this;
    if(size >= 2)
        nextNodes[size - 2]->setNextWidth(node);
    if(this->getNextDepth() == nullptr && this->getRank() <= node->getRank())
        this->setNextDepth(node);

}

void Node::listNextNodes() {
    std::vector<Node*>::iterator it;
    std::cout << "Listando os proximos nos ao estado " << state << ":" << std::endl;

    for(it = nextNodes.begin(); it != nextNodes.end(); it++) {
        std::cout << "state: " << std::setw(2) << (*it)->state << " - id: " << std::setw(4) << (*it)->id << " rank: " << (*it)->rank;
        std:: cout << " origin: ";
        for (int i = 0; i < 6; i++) {
            std::cout << (*it)->origin[i];
        }
        std:: cout << " destination: ";
        for (int i = 0; i < 6; i++) {
            std::cout << (*it)->destination[i];
        }
        std::cout << std::endl;
    }
}








