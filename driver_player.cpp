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
    string *prereqElmt = new string[1];
    prereqElmt[0] = "Ground";
    Skill *S2 = new Skill("Skill2",20,4,1,prereqElmt);
    Squirtlmon *Sq = new Squirtlmon("Squirtlmon");
    P->addEngimonToInventory(Sq);
    P->learnSkill(Sq,S2);
    P->learnSkill(G,S2);
    G->showData();

    // TEST 5
    P->deleteEngimonFromInventory(G);
    P->displayInventoryEngimon();
    P->changeActiveEngimon();
    P->interactActiveEngimon();

    return 0;
}