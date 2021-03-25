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
    Gastromon*g = new Gastromon();
    ch->setLevel(31);
    sq->setLevel(31);
    ch1->setLevel(31);
    sq1->setLevel(31);
    r->setLevel(31);
    g->setLevel(31);

    

    // tes getmastery
    string arr_fire [] = {"Fire"};
    Skill a("Silat",10,1,1,arr_fire);
    g->operator<<(a);

    p->breeding(g,r);
    // udah work
    p->changeActiveEngimon();
    p->getActiveEngimon()->showData();
    cout << "\n\n";
    g->showData();
    Skill b(*p->getSkillbyMastery(ch,g));
    //r->operator<<(b);
    r->showData();
    delete p;
    delete ch;
    delete ch1;
    delete sq;
    delete sq1;
    delete r;
    delete g;

    return 0;

    //charmamon x charmamon     v
    //squirtlmon x squirtlmon   v
    //spesies sama udah work
    //beda spesies adv beda udah work
    //beda spesies adv sama
}
