#include "Engimon.hpp"

#include <iostream>
#include <string>
using namespace std;

// -------------- BASE CLASS : ENGIMON ------------------
Engimon::Engimon(){
    this->name = "ZZZ";
    this->parent1name = "XXX";
    this->parent2name = "YYY";
    this->ability = new Skill[4];
    this->level = 0;
    this->exp = 0;
    this->cumulativeExp = 0;
    this->numAbility = 0;
}

Engimon::Engimon(string nama){
    this->name = nama;
    this->parent1name = "XXX";
    this->parent2name = "YYY";
    this->ability = new Skill[4];
    this->level = 0;
    this->exp = 0;
    this->cumulativeExp = 0;
    this->numAbility = 0;
}

Engimon::Engimon(string nama, string napar1, string napar2){
    this->name = nama;
    this->parent1name = napar1;
    this->parent2name = napar2;
    this->ability = new Skill[4];
    this->level = 0;
    this->exp = 0;
    this->cumulativeExp = 0;
    this->numAbility = 0;

}

Engimon::Engimon(const Engimon& other){
    this->name = other.name;
    this->parent1name = other.parent1name;
    this->parent2name = other.parent2name;
    this->ability = new Skill[4];
    for (int i = 0; i < 4; i++){
        this->ability[i] = other.ability[i];
    }
    this->level = other.level;
    this->exp = other.exp;
    this->cumulativeExp = other.cumulativeExp;
    this->numAbility = other.numAbility;
}

Engimon& Engimon::operator<<(const Skill& skil){
    if (this->numAbility <= 4 && this->punyaSkill(skil)){
        this->ability[numAbility] = skil;
    }
    return *this;
}

Engimon::~Engimon(){
    delete [] this->ability;
}

string Engimon::getName(){
    return this->name;
}

string Engimon::getParent1Name(){
    return this->parent1name;
}

string Engimon::getParent2Name(){
    return this->parent2name;
}

//string Engimon::getParent1Species(){};
//string Engimon::getParent2Species(){};
//void Engimon::talk(){};
//bool Engimon::punyaElemen(string){};

void Engimon::setName(string nama){
    this->name = nama;
}

void Engimon::levelUp(){
    while (this->exp > 100){
        this->level++;
        this->exp = this->exp - 100;
    }
}

void Engimon::addExp(int tambahan){
    this->exp = this->exp+tambahan;
    this->cumulativeExp = this->cumulativeExp+tambahan;
}

void Engimon::die(){ 
    if (this->cumulativeExp > maxExp){
        this->~Engimon();
    }
}

void Engimon::showData(){
    cout << "Level: "<<this->level << endl;
    cout << "Exp: " << this->exp << endl;
    cout << "Cumulative Exp: "<<this->cumulativeExp << endl;
    cout << "Skills: " ; 
    for (int i = 0; i < 4; i++)
    {
        string nama = ability[i].getnama();
        cout<<nama;
    }
    cout << endl;
    cout << "Parent's name: " << this->parent1name << ", "<<this->parent2name << endl;
}

bool Engimon::punyaSkill(Skill s){
    bool found = false;
    int i = 0;
    while (!found && i < this->numAbility){
        if (this->ability[i].getnama() == s.getnama()){
            found = true;
        }
        i++;
    }
    return found;
}

// -------DERIVED CLASS : FIRE ENGIMONS ----------------
string arr_fire [] = {"Fire"};
Skill a("Blaze",10,1,1,arr_fire);
Element fire(1,arr_fire);
const Element Charmamon:: elemen = fire;
const Skill Charmamon::uniqueSkill = a;
const string Charmamon::parentSpecies = "Charmamon";

Charmamon::Charmamon(): Engimon(){
    this->ability[0] = uniqueSkill;
}

Charmamon::Charmamon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
}

Charmamon::Charmamon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
}

Skill Charmamon::getuniqueSkill(){
    return uniqueSkill;
}

string Charmamon::getParent1Species(){
    return parentSpecies;
}

string Charmamon::getParent2Species(){
    return parentSpecies;
}

void Charmamon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Charmamon" << endl;
    cout << "Element: Fire" << endl;
    Engimon::showData();
    cout << "Parent's species: Charmamon" << endl;
}

void Charmamon::talk(){
    cout << "[" << this->name << "]: Chaaa!! Let's burn everything!!" << endl;
}

bool Charmamon::punyaElemen(string elem){
    return (elem == "Fire");
}

// -------DERIVED CLASS : WATER ENGIMONS ----------------
string arr_water [] = {"Water"};
Skill b("Torrent",10,1,1,arr_water);
Element water(1,arr_water);
const Element Squirtlmon:: elemen = water;
const Skill Squirtlmon::uniqueSkill = b;
const string Squirtlmon::parentSpecies = "Squirtlmon";

Squirtlmon::Squirtlmon(): Engimon(){
    this->ability[0] = uniqueSkill;
}

Squirtlmon::Squirtlmon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
}

Squirtlmon::Squirtlmon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
}

string Squirtlmon::getParent1Species(){
    return parentSpecies;
}

string Squirtlmon::getParent2Species(){
    return parentSpecies;
}

void Squirtlmon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Squirtlmon" << endl;
    cout << "Element: Water" << endl;
    Engimon::showData();
    cout << "Parent's species: Squirtlmon" << endl;
}

void Squirtlmon::talk(){
    cout << "[" << this->name << "]: Squii!! Splash splash!!" << endl;
}

bool Squirtlmon::punyaElemen(string elem){
    return (elem == "Water");
}

// -------DERIVED CLASS : ELECTRIC ENGIMONS ----------------
string arr_electric [] = {"Electric"};
Skill c("Static",10,1,1,arr_electric);
Element electric(1,arr_electric);
const Element Pikamon:: elemen = electric;
const Skill Pikamon::uniqueSkill = c;
const string Pikamon::parentSpecies = "Pikamon";

Pikamon::Pikamon(): Engimon(){
    this->ability[0] = uniqueSkill;
}

Pikamon::Pikamon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
}

Pikamon::Pikamon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
}

string Pikamon::getParent1Species(){
    return parentSpecies;
}

string Pikamon::getParent2Species(){
    return parentSpecies;
}

void Pikamon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Pikamon" << endl;
    cout << "Element: Electric" << endl;
    Engimon::showData();
    cout << "Parent's species: Pikamon" << endl;
}

void Pikamon::talk(){
    cout << "[" << this->name << "]: Pika Pika!!! Bzzzz" << endl;
}

bool Pikamon::punyaElemen(string elem){
    return (elem == "Electric");
}

// -------DERIVED CLASS : GROUND ENGIMONS ----------------
string arr_ground [] = {"Ground"};
Skill d("Sand Veil",10,1,1,arr_ground);
Element ground(1,arr_ground);
const Element Rumblemon:: elemen = ground;
const Skill Rumblemon::uniqueSkill = d;
const string Rumblemon::parentSpecies = "Rumblemon";

Rumblemon::Rumblemon(): Engimon(){
    this->ability[0] = uniqueSkill;
}

Rumblemon::Rumblemon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
}

Rumblemon::Rumblemon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
}

string Rumblemon::getParent1Species(){
    return parentSpecies;
}

string Rumblemon::getParent2Species(){
    return parentSpecies;
}

void Rumblemon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Rumblemon" << endl;
    cout << "Element: Ground" << endl;
    Engimon::showData();
    cout << "Parent's species: Rumblemon" << endl;
}

void Rumblemon::talk(){
     cout << "[" << this->name << "]: Rumble, rumble, attack!!!" << endl;
}

bool Rumblemon::punyaElemen(string elem){
    return (elem == "Ground");
}

// -------DERIVED CLASS : ICE ENGIMONS ----------------
string arr_ice [] = {"Ice"};
Skill e("Ice body",10,1,1,arr_ice);
Element ice(1,arr_ice);
const Element Snommon:: elemen = ice;
const Skill Snommon::uniqueSkill = e;
const string Snommon::parentSpecies = "Snommon";

Snommon::Snommon(): Engimon(){
    this->ability[0] = uniqueSkill;
}

Snommon::Snommon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
}

Snommon::Snommon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
}

string Snommon::getParent1Species(){
    return parentSpecies;
}

string Snommon::getParent2Species(){
    return parentSpecies;
}

void Snommon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Snommon" << endl;
    cout << "Element: Ice" << endl;
    Engimon::showData();
    cout << "Parent's species: Snommon" << endl;
}

void Snommon::talk(){
     cout << "[" << this->name << "]: Snow snowwy weee!!!" << endl;
}

bool Snommon::punyaElemen(string elem){
    return (elem == "Ice");
}

// -------DERIVED CLASS : ELECTROFIRE ENGIMONS ----------------
string arr_electrofire []= {"Fire", "Electric"};
Element electrofire(2,arr_electrofire);
Skill f("Levitate",10,1,2,arr_electrofire);
const Skill Rotomon::uniqueSkill = f;
const Element Rotomon:: elemen = electrofire;

Rotomon::Rotomon(): Engimon(){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Charmamon";
    this->parent2Species = "Pikamon";
}

Rotomon::Rotomon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Charmamon";
    this->parent2Species = "Pikamon";
}

Rotomon::Rotomon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Charmamon";
    this->parent2Species = "Pikamon";
}

Rotomon::Rotomon(string nama, string napar1, string napar2, string spec1, string spec2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
    this->parent1Species = spec1;
    this->parent2Species = spec2;
}

string Rotomon::getParent1Species(){
    return parent1Species;
}

string Rotomon::getParent2Species(){
    return parent2Species;
}

void Rotomon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Rotomon" << endl;
    cout << "Element: Fire, Electric" << endl;
    Engimon::showData();
    cout << "Parent's species: Rotomon" << endl;
}

void Rotomon::talk(){
     cout << "[" << this->name << "]: Rotom!! Kaboom!! " << endl;
}

bool Rotomon::punyaElemen(string elem){
    return (elem == "Fire" || elem == "Electric");
}

// -------DERIVED CLASS : ICE/WATER ENGIMONS ----------------
string arr_icewater[] = {"Ice", "water"};
Skill g("Thick fat", 10, 1, 2, arr_icewater);
Element icewater(2,arr_icewater);
const Skill Sealmon::uniqueSkill = g;
const Element Sealmon:: elemen = icewater;

Sealmon::Sealmon(): Engimon(){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Snommon";
    this->parent2Species = "Squirtlmon";
}

Sealmon::Sealmon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Snommon";
    this->parent2Species = "Squirtlmon";
}

Sealmon::Sealmon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Snommon";
    this->parent2Species = "Squirtlmon";
}

Sealmon::Sealmon(string nama, string napar1, string napar2, string spec1, string spec2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
    this->parent1Species = spec1;
    this->parent2Species = spec2;
}

string Sealmon::getParent1Species(){
    return parent1Species;
}

string Sealmon::getParent2Species(){
    return parent2Species;
}

void Sealmon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Sealmon" << endl;
    cout << "Element: Fire, Electric" << endl;
    Engimon::showData();
    cout << "Parent's species: Sealmon" << endl;
}

void Sealmon::talk(){
     cout << "[" << this->name << "]: Aye, aye, sealmon!!" << endl;
}

bool Sealmon::punyaElemen(string elem){
    return (elem == "Water" || elem == "Ice");
}

// -------DERIVED CLASS : WATER/GROUND ENGIMONS ----------------
string arr_waterground [] = {"Water", "Ground"};
Skill h("Sticky hold",10,1,2,arr_waterground);
Element waterground(2,arr_waterground);
const Skill Gastromon::uniqueSkill = h;
const Element Gastromon:: elemen = waterground;

Gastromon::Gastromon(): Engimon(){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Snommon";
    this->parent2Species = "Rumblemon";
}

Gastromon::Gastromon(string nama):Engimon(nama){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Snommon";
    this->parent2Species = "Rumblemon";
}

Gastromon::Gastromon(string nama, string napar1, string napar2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
    this->parent1Species = "Snommon";
    this->parent2Species = "Rumblemon";
}

Gastromon::Gastromon(string nama, string napar1, string napar2, string spec1, string spec2):Engimon(nama, napar1, napar2){
    this->ability[0] = uniqueSkill;
    this->parent1Species = spec1;
    this->parent2Species = spec2;
}

string Gastromon::getParent1Species(){
    return parent1Species;
}

string Gastromon::getParent2Species(){
    return parent2Species;
}

void Gastromon::showData(){
    cout << "Name: " << this->name << endl;
    cout << "Species: Gastromon" << endl;
    cout << "Element: Water, Ground" << endl;
    Engimon::showData();
    cout << "Parent's species: Gastromon" << endl;
}

void Gastromon::talk(){
     cout << "[" << this->name << "]: Gastro, gastro, let's go!! " << endl;
}

bool Gastromon::punyaElemen(string elem){
    return (elem == "Water" || elem =="Ground");
}