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
    P->displayInventorySkill();
    P->displayInventoryEngimon();

    // TEST 3
    P->changeActiveEngimon(G);
    cout << "Aktif Engimon: " << P->getActiveEngimon()->getName() << endl;

    return 0;
}