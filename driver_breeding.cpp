#include "Player.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
    Player*p = new Player();
    Charmamon*ch = new Charmamon();
    Charmamon*ch1 = new Charmamon();
    Squirtlmon*sq = new Squirtlmon();
    Squirtlmon*sq1 = new Squirtlmon();
    ch->setLevel(31);
    sq->setLevel(31);
    ch1->setLevel(31);
    sq1->setLevel(31);
    //Engimon a(*p->breedingSpesies(ch,ch1));
    //a.showData();

    p->breeding(sq,sq1);
    // udah work
    p->changeActiveEngimon();
    p->getActiveEngimon()->showData();

    delete p;
    delete ch;
    delete ch1;
    delete sq;
    delete sq1;
    return 0;

    //charmamon x charmamon     v
    //squirtlmon x squirtlmon   v
}
