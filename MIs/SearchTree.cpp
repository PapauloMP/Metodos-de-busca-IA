//
// Created by Marcos Paulo on 27/09/2022.
//
#include "../Headers/SearchTree.h"
#include <iostream>
#include <queue>
#include <algorithm>


SearchTree::SearchTree() {
    totalStates = 0;
    bool origin[6];
    bool destination[6];
    for (int i = 0; i < 6; ++i) {
        origin[i] = true;
        destination[i] = false;
    }
    root = new Node(totalStates++, 0, origin, destination, false, 0);
    //build(root);
}

SearchTree::~SearchTree() = default;

bool SearchTree::search(int id, int rank){
    return auxSearch(root, id, rank);
}

bool SearchTree::auxSearch(Node* node, int& id, int& rank){
    if(node == nullptr)
        return false;// arvore vazia
    else if(node->getId() == id && (node->getRank() + rank) % 2 == 0)
        return true;// chave encontrada
    if (auxSearch(node->getNextDepth(), id, rank))
        return true;
    else
        return auxSearch(node->getNextWidth(), id, rank);
}

void SearchTree::build(Node* node) {
    listClosed.push_back(node->getState());

    bool* orig = node->getOrigin();
    bool* dest = node->getDestination();
    int cont = 0;
    if (node->getId() == 4032) {
        std::cout << "No solucao!" << std::endl;
        return;
    }
    // verificar estagio temporario
    if (node->getTemp() == 0) {
        for (int i = 1; i <= 12; i++) {
            int isTemp = 0;

            bool origin[] = {orig[0], orig[1], orig[2], orig[3], orig[4], orig[5]};
            bool destination[] = {dest[0], dest[1], dest[2], dest[3], dest[4], dest[5]};
            std::cout << "Estado atual (destino):" << dest[0] << destination[1] << dest[2] << dest[3] << dest[4]
                      << dest[5] << std::endl;

            bool validRule;
            if (node->getRank() % 2 == 0) { // nivel par = ida
                std::cout << "Estado atual (destino):" << std::endl;
                for (int j = 0; j < 6; ++j) {
                    std::cout << dest[j];
                }
                std::cout << std::endl;
                validRule = applyRule(i, origin, destination, &isTemp);
            }
            else { // nivel ímpar = volta
                std::cout << "Estado atual (origem):" << std::endl;
                for (int j = 0; j < 6; ++j) {
                    std::cout << orig[j];
                }
                std::cout << std::endl;
                validRule = applyRule(i, destination, origin, &isTemp);
            }
            if (validRule) {
                std::cout << "Regra " << i << " aplicada!" << std::endl;
                Node *newNode = new Node(totalStates++, node->getRank() + 1, origin, destination, isTemp, i);
                if (!search(newNode->getId(), newNode->getRank())) {
                    listOpened.push_back(newNode->getState());
                    std::cout << "INSERINDO NO: " << newNode->getState() << "isTemp: " << isTemp << std::endl;
                    node->setNextNodes(newNode);
                    cont++;
                } else {
                    delete newNode;
                    totalStates--;
                }

            }
        }
    }
    else{
        std::cout << "ESTAGIO TEMPORARIO DO NO " << node->getState() << ": " << node->getTemp() << std::endl;
        std::vector<int> rules = solveTempState(node->getTemp());
        int isTemp = 0;
        int rule;

        for (int i = 0; i < rules.size(); i++) {

            rule = rules[i];
            std::cout << "REGRA: " << rule << std::endl;

            bool origin[] = {orig[0], orig[1], orig[2], orig[3], orig[4], orig[5]};
            bool destination[] = {dest[0], dest[1], dest[2], dest[3], dest[4], dest[5]};

            bool validRule;
            if (node->getRank() % 2 == 0) { // nivel par = ida
                std::cout << "Estado atual (destino):" << std::endl;
                for (int j = 0; j < 6; ++j) {
                    std::cout << dest[j];
                }
                std::cout << std::endl;
                validRule = applyRule(rule, origin, destination, &isTemp);
            }
            else { // nivel ímpar = volta
                std::cout << "Estado atual (origem):" << std::endl;
                for (int j = 0; j < 6; ++j) {
                    std::cout << orig[j];
                }
                std::cout << std::endl;
                validRule = applyRule(rule, destination, origin, &isTemp);
            }
            if (validRule) {
                std::cout << "Regra " << rule << " aplicada!" << std::endl;
                Node *newNode = new Node(totalStates++, node->getRank() + 1, origin, destination, isTemp, rule);
                if (!search(newNode->getId(), newNode->getRank())) {
                    listOpened.push_back(newNode->getState());
                    node->setNextNodes(newNode);
                    cont++;
                } else {
                    delete newNode;
                    totalStates--;
                }

            }
        }

    }

    if(cont == 0){
        std::cout << "No folha de estado invalido (estado: " << node->getState() << ")" << std::endl;
    }

}

bool SearchTree::applyRule(int rule, bool* x, bool* y, int* isTemp) {

    switch(rule) {
        case 1:
            if (x[1]) {    // levar filho vermelho
                if(!y[0] && (y[2] || y[4])) // garante que o filho nao fique sozinho com um pai que nao seja o dele
                    *isTemp = 1;
                x[1] = false;
                y[1] = true;
                return true;
            }
            break;
        case 2:
            if (x[3]){     // levar filho verde
                if(!y[2] && (y[0] || y[4]))
                    *isTemp = 2;
                x[3] = false;
                y[3] = true;
                return true;
            }
            break;
        case 3:
            if (x[5]){     // levar filho azul
                if(!y[4] && (y[0] || y[2]))
                    *isTemp = 3;
                x[5] = false;
                y[5] = true;
                return true;
            }
            break;
        case 4:
            if (x[0]){     // levar pai vermelho
                if(x[1] && (x[2] || x[4]))
                    *isTemp = 4;
                x[0] = false;
                y[0] = true;
                return true;
            }
            break;
        case 5:
            if (x[2]){     // levar pai verde
                if(x[3] && (x[0] || x[4]))
                    *isTemp = 5;
                x[2] = false;
                y[2] = true;
                return true;
            }
            break;
        case 6:
            if (x[4]){     // levar pai azul
                if(x[5] && (x[0] || x[2]))
                    *isTemp = 6;
                x[4] = false;
                y[4] = true;
                return true;
            }
            break;
        case 7:
            if (x[0] && x[1]){     // levar pai vermelho e filho vermelho
                x[0] = false;
                x[1] = false;
                y[0] = true;
                y[1] = true;
                return true;
            }
            break;
        case 8:
            if (x[2] && x[3]){     // levar pai verde e filho verde
                x[2] = false;
                x[3] = false;
                y[2] = true;
                y[3] = true;
                return true;
            }
            break;
        case 9:
            if (x[4] && x[5]){     // levar pai azul e filho azul
                x[4] = false;
                x[5] = false;
                y[4] = true;
                y[5] = true;
                return true;
            }
            break;
        case 10:
            if (x[5] && x[3]){     // levar filho azul e filho verde
                if((!y[4] && (y[0] || y[2])) && (!y[2] && (y[0] || y[4])))
                    return false;
                if(!y[4] && (y[0] || y[2]))
                    *isTemp = 3;
                if(!y[2] && (y[0] || y[4]))
                    *isTemp = 2;
                x[5] = false;
                x[3] = false;
                y[5] = true;
                y[3] = true;
                return true;
            }
            break;
        case 11:
            if (x[5] && x[1]){     // levar filho azul e filho vermelho
                if((!y[4] && (y[0] || y[2])) && (!y[0] && (y[2] || y[4])))
                    return false;
                if(!y[4] && (y[0] || y[2]))
                    *isTemp = 3;
                if(!y[0] && (y[2] || y[4]))
                    *isTemp = 1;
                x[5] = false;
                x[1] = false;
                y[5] = true;
                y[1] = true;
                return true;
            }
            break;
        case 12:
            if (x[3] && x[1]){     // levar filho verde e filho vermelho
                if((!y[2] && (y[0] || y[4])) && (!y[0] && (y[2] || y[4])))
                    return false;
                if(!y[2] && (y[0] || y[4]))
                    *isTemp = 2;
                if(!y[0] && (y[2] || y[4]))
                    *isTemp = 1;
                x[3] = false;
                x[1] = false;
                y[3] = true;
                y[1] = true;
                return true;
            }
            break;
    }
    return false;
}

void SearchTree::printStack() {
    std::cout << "Imprimindo lista de estados da solucao:" << std::endl;
    while(!stackState.empty()){
        if(stackState.top() != 0)
            std::cout << stackState.top() << "<-";
        else
            std::cout << stackState.top();
        stackState.pop();
    }
    std::cout << std::endl;
}

void SearchTree::printOpened() {
    std::cout << "Imprimindo lista de abertos:" << std::endl;
    for (int i = 0; i < listOpened.size(); i++) {
        std::cout << listOpened[i] << " ";
    }
    std::cout << std::endl;
}

void SearchTree::printClosed() {
    std::cout << "Imprimindo lista de fechados:" << std::endl;
    for (int i = 0; i < listClosed.size(); i++) {
        std::cout << listClosed[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> SearchTree::solveTempState(int temp) {

    std::vector<int> applicableRules;
    switch(temp) {
        case 1: {
            applicableRules.push_back(1);
            applicableRules.push_back(7);
            applicableRules.push_back(11);
            applicableRules.push_back(12);
            break;
        }
        case 2: {
            applicableRules.push_back(2);
            applicableRules.push_back(8);
            applicableRules.push_back(10);
            applicableRules.push_back(12);
            break;
        }
        case 3: {
            applicableRules.push_back(3);
            applicableRules.push_back(9);
            applicableRules.push_back(10);
            applicableRules.push_back(11);
            break;
        }
        case 4: {
            applicableRules.push_back(7);
            break;
        }
        case 5: {
            applicableRules.push_back(8);
            break;
        }
        case 6: {
            applicableRules.push_back(9);
            break;
        }
    }
    return applicableRules;
}

bool compareNodes(Node* x, Node* y){
    return x->getRank() < y->getRank();
}

std::vector<Node*> SearchTree::breadthSearch(std::ofstream& outputFile) {
    outputFile << "strict digraph buscaEmLargura {" << std::endl;
    outputFile << "\trankdir=\"TB\";" << std::endl;
    std::string edgeAttribute = "[color=red,penwidth=3.0] [fontsize = 20]";


    std::vector<Node*> searchResult;
    std::queue<Node*> queue;
    std::stack<Node*> solutionPath;
    searchResult.push_back(root);
    queue.push(root);

    bool solution = false;

    while(!solution && !queue.empty()){ //achar solucao com ponteiro para o pai?
        Node* node = queue.front();
        Node* anterior = node;
        queue.pop();
        build(node);
        for(Node* n : node->getNextNodes()){
            outputFile << "\t" << anterior->getState() << " -> " << n->getState() << ";" << std::endl;
            queue.push(n);
            searchResult.push_back(n);
            anterior = n;
            if(n->getId() == 4032) {
                solution = true;
                Node* x = n;
                while(x != nullptr) {
                    solutionPath.push(x);
                    if(x->getParent() != nullptr) {
                        outputFile << "\t" << x->getParent()->getState() << " -> " << x->getState() << " [label = R";
                        outputFile << x->getRule() << "] " << edgeAttribute << ";" << std::endl;
                    }
                    x = x->getParent();
                }
                break;
            }
        }
    }

    std::cout << "Imprimindo busca em largura: " << std::endl;
    for(Node* n : searchResult){
        std::cout << n->getState() << " ";
    }
    std::cout << std::endl;
    std::cout << "Imprimindo solucao: " << std::endl;
    while(!solutionPath.empty()) {
        std::cout << solutionPath.top()->getState() << " - " << "Destino:";
        for (int i = 0; i < 6; ++i) {
            std::cout << solutionPath.top()->getDestination()[i];
        }
        std::cout << std::endl;
        solutionPath.pop();
    }
    std::cout << std::endl;

    std::sort(searchResult.begin(), searchResult.end(), compareNodes);

    outputFile << "\t{rank = same";
    for(int i = 0; i < searchResult.size(); i++){
        //std::cout << searchResult[i]->getRank() << " ";
        if (i != 0){
            if(searchResult[i-1]->getRank() !=  searchResult[i]->getRank())
                outputFile << "};" <<  std::endl << "\t{rank = same";
        }
        outputFile << "; "<< searchResult[i]->getState();
    }


    outputFile << "}" << std::endl << "}";

    return searchResult;
}

