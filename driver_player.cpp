#include "Player.hpp"
#include <iostream>
using namespace std;

int main() {
    // TEST 1
    Player *P = new Player();
    P->displayInventorySkill();
    P->displayInventoryEngimon();
    cout << "Aktif Engimon: " << P->getActiveEngimon()->getName() << endl;

    // TEST 2
    Gastromon *G = new Gastromon("Gastromon");
    P->addEngimonToInventory(G);
    P->displayInventoryEngimon();

    // TEST 3
    P->changeActiveEngimon();
    cout << "Aktif Engimon: " << P->getActiveEngimon()->getName() << endl;

    // TEST 4
    Squirtlmon *Sq = new Squirtlmon("Squirtlmon");
    P->addEngimonToInventory(Sq);
    P->learnSkill(Sq);
    P->learnSkill(G);
    G->showData();

    // TEST 5
    P->deleteEngimonFromInventory(G);
    P->displayInventoryEngimon();
    P->changeActiveEngimon();
    P->interactActiveEngimon();

    return 0;
}