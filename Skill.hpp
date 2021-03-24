#ifndef __SKILL_HPP__
#define __SKILL_HPP__
using namespace std;
#include <string>
#include <iostream>
#include "Element.hpp"

class Skill{
private:
    string nama;
    int num_base_power;
    int mastery_level;
    Element elemen;

public:
    Skill();
    Skill(string nm, int nbp, int ml,int jmlel, string[]);
    Skill(const Skill&);
    ~Skill();
    int countSkillPower();
    string getnama();
    Element getelemen();
    friend bool operator==(Skill& s1, Skill& s2);
};

#endif