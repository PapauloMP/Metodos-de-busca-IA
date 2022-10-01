//
// Created by Marcos Paulo on 27/09/2022.
//
#include "../Headers/SearchTree.h"
#include <iostream>


SearchTree::SearchTree() {
    totalStates = 0;
    bool origin[6];
    bool destination[6];
    for (int i = 0; i < 6; ++i) {
        origin[i] = true;
        destination[i] = false;
    }
    root = new Node(totalStates++, 0, origin, destination);
    build(root);
}

SearchTree::~SearchTree() {

}

void SearchTree::build(Node* node) {
    bool* orig = node->getOrigin();
    bool* dest = node->getDestination();
    int cont = 0;
    for (int i = 1; i <= 21; i++) {

        bool origin[] = {orig[0], orig[1], orig[2], orig[3], orig[4], orig[5]};
        bool destination[] = {dest[0], dest[1], dest[2], dest[3], dest[4], dest[5]};
        std::cout << "Teste:" << dest[0] << destination[1] << dest[2] << dest[3] << dest[4] << dest[5] << std::endl;
        if(node->getRank() % 2 == 0) {
            if (applyRule(i, origin, destination)) { // nivel par = ida
                std::cout << "Regra " << i << " aplicada!" << std::endl;
                Node *newNode = new Node(totalStates++, node->getRank() + 1, origin, destination);
                //verificar ciclo
                node->setNextNodes(newNode);
                cont++;
            }
        }
        else{
            if (applyRule(i, destination, origin)) { // nivel ímpar = volta
                std::cout << "Regra " << i << " aplicada2!" << std::endl;
                Node *newNode = new Node(totalStates++, node->getRank() + 1, origin, destination);
                //verificar ciclo
                node->setNextNodes(newNode);
                cont++;
            }
        }
    }

    if(cont == 0 && node->getId() != 4032){
        std::cout << "No folha de estado invalido (estado: " << node->getState() << ")" << std::endl;
    }

}

Node* SearchTree::getNode(int state) {

    int cont = 0;
    Node* node = root;
    while(cont != totalStates) {
        for (Node* auxNode = node; auxNode->getNextWidth() != nullptr; auxNode = auxNode->getNextWidth()) {
            if(auxNode->getState() == state){
                return auxNode;
            }
            cont++;
        }
        if(node->getNextDepth() == nullptr){
            for (Node* auxNode = node; auxNode->getNextWidth() != nullptr; auxNode = auxNode->getNextWidth()) {
                if(auxNode->getNextDepth() != nullptr){
                    node = auxNode->getNextDepth();
                    break;
                }
            }
        }

        node = root->getNextDepth();
    }

    return nullptr;
}

bool SearchTree::applyRule(int rule, bool* x, bool* y) {

    switch(rule) {
        case 1:
            if (x[1]) {    // levar filho vermelho
                std::cout << "X[1] = " << x[1] << std::endl;
                x[1] = false;
                y[1] = true;
                return true;
            }
        case 2:
            if (x[3]){     // levar filho verde
                x[3] = false;
                y[3] = true;
                return true;
            }
        case 3:
            if (x[5]){     // levar filho azul
                x[5] = false;
                y[5] = true;
                return true;
            }
        case 4:
            if (x[0]){     // levar pai vermelho
                x[0] = false;
                y[0] = true;
                return true;
            }
        case 5:
            if (x[2]){     // levar pai verde
                x[2] = false;
                y[2] = true;
                return true;
            }
        case 6:
            if (x[4]){     // levar pai azul
                x[4] = false;
                y[4] = true;
                return true;
            }
        case 7:
            if (x[0] && x[1]){     // levar pai vermelho e filho vermelho
                x[0] = false;
                x[1] = false;
                y[0] = true;
                y[1] = true;
                return true;
            }
        case 8:
            if (x[0] && x[3]){     // levar pai vermelho e filho verde
                x[0] = false;
                x[3] = false;
                y[0] = true;
                y[3] = true;
                return true;
            }
        case 9:
            if (x[0] && x[5]){     // levar pai vermelho e filho azul
                x[0] = false;
                x[5] = false;
                y[0] = true;
                y[5] = true;
                return true;
            }
        case 10:
            if (x[2] && x[1]){     // levar pai verde e filho vermelho
                x[2] = false;
                x[1] = false;
                y[2] = true;
                y[1] = true;
                return true;
            }
        case 11:
            if (x[2] && x[3]){     // levar pai verde e filho verde
                x[2] = false;
                x[3] = false;
                y[2] = true;
                y[3] = true;
                return true;
            }
        case 12:
            if (x[2] && x[5]){     // levar pai verde e filho azul
                x[2] = false;
                x[5] = false;
                y[2] = true;
                y[5] = true;
                return true;
            }
        case 13:
            if (x[4] && x[1]){     // levar pai azul e filho vermelho
                x[4] = false;
                x[1] = false;
                y[4] = true;
                y[1] = true;
                return true;
            }
        case 14:
            if (x[4] && x[3]){     // levar pai azul e filho verde
                x[4] = false;
                x[3] = false;
                y[4] = true;
                y[3] = true;
                return true;
            }
        case 15:
            if (x[4] && x[5]){     // levar pai azul e filho azul
                x[4] = false;
                x[5] = false;
                y[4] = true;
                y[5] = true;
                return true;
            }
        case 16: break;
        case 17: break;
        case 18: break;
        case 19: break;
        case 20: break;
        case 21: break;
    }
    return false;
}

