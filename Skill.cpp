#include <iostream>
using namespace std;
#include "Skill.hpp"

Skill :: Skill() {
    this->nama = "XXX";
    this->num_base_power=0;
    this->mastery_level=0;
    this->elemen = Element();
}

Skill::Skill(string nm, int nbp, int ml, int jmlel, string elem []){
    this->nama = nm;
    this->num_base_power=nbp;
    this->mastery_level=ml;
    this->elemen = Element(jmlel,elem);
}

Skill :: Skill(const Skill& skl){
    this->nama = skl.nama;
    this->num_base_power = skl.num_base_power;
    this->mastery_level = skl.mastery_level;
    this->elemen = skl.elemen;
}

Skill :: ~Skill(){
}

string Skill::getnama(){
    return (nama);
}


int Skill::countSkillPower(){
    return (num_base_power*mastery_level);
}


