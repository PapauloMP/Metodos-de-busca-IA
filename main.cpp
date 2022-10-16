#include <iostream>
#include "Headers/Node.h"
#include "Headers/SearchTree.h"
#include "chrono"

using namespace std;
//int argc, char** argv
void inputException(int option){
    if (option != 1 && option != 2 && option != 3)
        throw invalid_argument("Opcao invalida!");
}

int menu(){

    int option;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Busca em largura" << endl;
    cout << "[2] Busca em profundidade" << endl;
    cout << "[3] Busca backtracking" << endl;
    cout << "Digite uma opcao: ";

    cin >> option;
    getchar();

    try{
        inputException(option);
    }catch(invalid_argument& e){
        std::cout << e.what() << std::endl;
        menu();
    }

    return option;

}

int main() {

    auto start = chrono::steady_clock::now();

    auto* arv = new SearchTree("texte0.txt");
    /*Node* n = arv->getRoot();
    arv->build(n);
    n->listNextNodes();
    Node* n2 = n->nextNodes[8];
    arv->build(n2);
    n2->listNextNodes();
    Node* n3 = n2->nextNodes[0];
    arv->build(n3);
    n3->listNextNodes();
    Node* n4 = n3->nextNodes[1];
    arv->build(n4);
    n4->listNextNodes();
    Node* n5 = n4->nextNodes[0];
    arv->build(n5);
    n5->listNextNodes();
    Node* n6 = n5->nextNodes[2];
    arv->build(n6);
    n6->listNextNodes();
    Node* n7 = n6->nextNodes[0];
    arv->build(n7);
    n7->listNextNodes();
    Node* n8 = n7->nextNodes[0];
    arv->build(n8);
    n8->listNextNodes();
    Node* n9 = n8->nextNodes[0];
    arv->build(n9);
    n9->listNextNodes();
    Node* n10 = n9->nextNodes[1];
    arv->build(n10);
    n10->listNextNodes();*/

    stack<Node*> teste;

    int option = menu();
    switch(option){
        case 1: teste = arv->breadthSearch();break;
        case 2: teste = arv->deepFirstSearch();break;
        case 3: teste = arv->backtrackingSearch();break;

    }

    arv->printStack(teste);
    arv->printOpened();
    arv->printClosed();

    delete arv;

    auto end = chrono::steady_clock::now();
    auto elapsed  = end - start;

    cout << endl << "TEMPO DE PROCESSAMENTO TOTAL: " <<  chrono::duration_cast<chrono::nanoseconds>(elapsed).count() << "ns" << endl;

    return 0;
}
