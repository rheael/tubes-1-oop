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
    Rumblemon*r = new Rumblemon();
    ch->setLevel(31);
    sq->setLevel(31);
    ch1->setLevel(31);
    sq1->setLevel(31);
    r->setLevel(31);
    //Engimon a(*p->breedingSpesies(ch,ch1));
    //a.showData();

    p->breeding(ch,ch1);
    // udah work
    p->changeActiveEngimon();
    p->getActiveEngimon()->showData();

    cout << "\n\n";
    if(ch->getElemen().isSama(ch1->getElemen())){
        cout << "sama jir" << endl;
    } else { cout << "ga" << endl;}

    delete p;
    delete ch;
    delete ch1;
    delete sq;
    delete sq1;
    return 0;

    //charmamon x charmamon     v
    //squirtlmon x squirtlmon   v
    //spesies sama udah work
    //beda spesies (bapak lebih gede)
}
