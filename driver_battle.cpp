#include "Player.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
    Player*p = new Player();
    Snommon*ch = new Snommon();
    Rotomon*ch1 = new Rotomon();
    Squirtlmon*sq = new Squirtlmon();
    //ch->setLevel(31);
    //sq->setLevel(31);
    //ch1->setLevel(31);

    p->getActiveEngimon()->setLevel(40);
    //ch->setLevel(20);
    p->getActiveEngimon()->showData();
    cout <<"\n";

    p->battle(ch);
    p->displayInventoryEngimon();
    p->getActiveEngimon()->showData();
    p->displayInventorySkill();
    delete p;
    delete ch;
    delete ch1;
    delete sq;
    //p->displayInventoryEngimon();
    return 0;
}
