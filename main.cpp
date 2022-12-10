#include <iostream>
#include "Headers/Node.h"
#include "Headers/SearchTree.h"
#include "chrono"

using namespace std;

void inputException(int option){
    if (option < 0 || option > 6)
        throw invalid_argument("Opcao invalida!");
}

int menu(){

    int option;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Busca em largura" << endl;
    cout << "[2] Busca em profundidade" << endl;
    cout << "[3] Busca backtracking" << endl;
    cout << "[4] Busca gulosa" << endl;
    cout << "[5] Busca ordenada" << endl;
    cout << "[6] Busca A*" << endl;
    cout << "[0] Sair" << endl;
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

    auto* arv = new SearchTree("outputFile.txt");
    stack<Node*> teste;
    int option = menu();

    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;
    chrono::steady_clock::duration elapsed;

    switch(option){
        case 1:{
            start = chrono::steady_clock::now();

            teste = arv->breadthSearch();

            end = chrono::steady_clock::now();
            elapsed = end - start;
            break;
        }
        case 2:{
            start = chrono::steady_clock::now();

            teste = arv->deepFirstSearch();

            end = chrono::steady_clock::now();
            elapsed  = end - start;
            break;
        }
        case 3:{
            start = chrono::steady_clock::now();

            teste = arv->backtrackingSearch();

            end = chrono::steady_clock::now();
            elapsed  = end - start;
            break;
        }
        case 4:{
            start = chrono::steady_clock::now();

            teste = arv->greedySearch();

            end = chrono::steady_clock::now();
            elapsed  = end - start;
            break;
        }
        case 5:{
            start = chrono::steady_clock::now();

            teste = arv->uniformSearch();

            end = chrono::steady_clock::now();
            elapsed  = end - start;
            break;
        }
        case 6:{
            start = chrono::steady_clock::now();

            teste = arv->AStarSearch();

            end = chrono::steady_clock::now();
            elapsed  = end - start;
            break;
        }
        default:{
            start = chrono::steady_clock::now();
            end = chrono::steady_clock::now();
            elapsed = end - start;
            break;
        }
    }

    arv->printStack(teste);
    arv->printOpened();
    arv->printClosed();

    cout << endl << "TEMPO DE PROCESSAMENTO TOTAL: " <<  chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
    cout << "ns" << endl;

    delete arv;

    return 0;
}
