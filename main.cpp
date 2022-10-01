#include <iostream>
#include "Headers/Node.h"
#include "Headers/SearchTree.h"
#include "chrono"

using namespace std;

int main() {

    auto start = std::chrono::steady_clock::now();
    //Node* node = new Node(33, 0, nullptr, nullptr, nullptr);
    //Node* node1 = new Node(22, 1, nullptr, nullptr, node);

   // std::cout << "Node state: " << n[0]->getState() << std::endl;
    auto* arv = new SearchTree();
    cout << "State: " << arv->getTotalStates() << endl;
    Node* n = arv->getRoot();
    n->listNextNodes();
    Node* n2 = n->nextNodes[14];
    arv->build(n2);
    n2->listNextNodes();


    auto end = chrono::steady_clock::now();
    auto elapsed  = end - start;

    cout << endl << "TEMPO DE PROCESSAMENTO TOTAL: " <<  chrono::duration_cast<chrono::nanoseconds>(elapsed).count() << "ns" << endl;

    return 0;
}
