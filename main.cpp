#include <iostream>
#include "Headers/Node.h"
#include "Headers/SearchTree.h"
#include "chrono"

using namespace std;
//int argc, char** argv
int main() {

    auto start = chrono::steady_clock::now();

    auto* arv = new SearchTree();
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


    ofstream outputFile("texte.txt");

    arv->printStack();
    arv->printOpened();
    arv->printClosed();

    vector<Node*> teste = arv->breadthSearch(outputFile);
//    cout << "Imprimindo busca em largura: " << endl;
//    for(Node* n : teste){
//        cout << n->getState() << endl;
//    }


    auto end = chrono::steady_clock::now();
    auto elapsed  = end - start;

    cout << endl << "TEMPO DE PROCESSAMENTO TOTAL: " <<  chrono::duration_cast<chrono::nanoseconds>(elapsed).count() << "ns" << endl;

    return 0;
}
