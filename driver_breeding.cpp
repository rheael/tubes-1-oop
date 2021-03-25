#include "Player.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
    Charmamon mamon(); //bapak
    Squirtlmon squirt(); //emak
    /*
    string typeBapak = typeid(mamon).name();
    string typeAnak = typeid(mamon).name();
    string typeEmak = typeid(mamon).name();
    string tes = "Charmamon";

    if (typeBapak.find(tes) == std::string::npos) {
        cout << "found! " << tes << " ada di dalam " << typeBapak << endl;
    }
    */
    Player*p = new Player();
    Squirtlmon*ch = new Squirtlmon();
    Charmamon*ch1 = new Charmamon();
    Squirtlmon*sq = new Squirtlmon();
    //ch->setLevel(31);
    //sq->setLevel(31);
    //ch1->setLevel(31);

    p->getActiveEngimon()->setLevel(40);

    p->getActiveEngimon()->showData();
    p->battle(ch1);
    p->getActiveEngimon()->showData();
    delete p;
    delete ch;
    delete ch1;
    delete sq;
    //p->displayInventoryEngimon();

    // breedingnya belum bs detect spesies
    return 0;
}
