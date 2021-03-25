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
    Rotomon*r = new Rotomon();
    ch->setLevel(31);
    sq->setLevel(31);
    ch1->setLevel(31);
    sq1->setLevel(31);
    r->setLevel(31);
    //Engimon a(*p->breedingSpesies(ch,ch1));
    //a.showData();

    p->breeding(ch1,r);
    // udah work
    p->changeActiveEngimon();
    p->getActiveEngimon()->showData();
    /*
    cout << "\n\n";
    if(ch->getElemen().isSama(ch1->getElemen())){
        cout << "sama jir" << endl;
    } else { cout << "ga" << endl;}
    */
    // ud work
    cout << "\n\n";
    Engimon*engi = new Engimon();
    engi = p->generateRandomChild("acim","acom","acem");
    engi->showData();

    delete p;
    delete ch;
    delete ch1;
    delete sq;
    delete sq1;
    delete r;
    delete engi;
    return 0;

    //charmamon x charmamon     v
    //squirtlmon x squirtlmon   v
    //spesies sama udah work
    //beda spesies adv beda udah work
    //beda spesies adv sama
}
