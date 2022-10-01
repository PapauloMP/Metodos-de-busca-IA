//
// Created by Marcos Paulo on 27/09/2022.
//
#include <iostream>
#include "../Headers/Node.h"
#include <cmath>
#include <iomanip>

Node::Node(int state, int rank, bool* origin, bool* destination){
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

    if(origin != nullptr && destination != nullptr) {
        for (int i = 0; i < 6; i++) {
            id += int((origin[i] * pow(2, i)) + (destination[i] * pow(2, i + 6)));
        }
    }

    if(id == 4032)
        std::cout << "No solução! (estado: " << state << ")" << std::endl;

    for (int i = 0; i < 6; ++i) {
        std::cout << this->origin[i];
    }
    std::cout << std::endl;
}
Node::~Node(){
    //delete [] origin;
    //delete [] destination;
};
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


void Node::setNextNodes(Node* node) {
    nextNodes.push_back(node);
    if(this->getRank() == node->getRank()) //nunca ocorre
        this->setNextWidth(node);
    else if(this->getRank() <= node->getRank())
        this->setNextDepth(node);
    else
        std::cout<< "ERRO: no de rank superior" << std::endl;
}

void Node::listNextNodes() {
    std::vector<Node*>::iterator it;

    for(it = nextNodes.begin(); it != nextNodes.end(); it++) {
        bool* origin = (*it)->getOrigin();
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

    /*std::cout << "Listando os proximos nos ao estado " << state << ":" << std::endl;
    for (int i = 0; i < nextNodes.size(); i++) {
        std::cout << "state: "<< std::setw(2) << nextNodes[i]->state << " - id: " << std::setw(4) << nextNodes[i]->id << " rank: " << nextNodes[i]->rank;
        std:: cout << " origin: ";
        for (int j = 0; j < 6; j++) {
            std::cout << nextNodes[i]->origin[j];
        }
        std:: cout << " destination: ";
        for (int j = 0; j < 6; j++) {
            std::cout << nextNodes[i]->destination[j];
        }
        std::cout << std::endl;
    }*/

}





