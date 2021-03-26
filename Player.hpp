#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// #include "Engimon.hpp"
#include "Point.hpp"
#include "Inventory.hpp"
#include "InventoryItem.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Player {
    private:
        Point* Position;
        Engimon* activeEngimon;
        Inventory<Skill*>* InventorySkill;
        Inventory<Engimon*>* InventoryEngimon;
        int nbInventory;
        int MAX_CAP;

    public:
        Player();
        void keAtas();
        void keBawah();
        void keKanan();
        void keKiri();
        Point* getPosition();
        void setPosition(int X, int Y);
        Engimon* getActiveEngimon();
        void changeActiveEngimon();
        void interactActiveEngimon();
        void addSkillToInventory(Skill* S);
        void addEngimonToInventory(Engimon* E);
        void deleteSkillFromIventory(Skill* S);
        void deleteEngimonFromInventory(Engimon* E);
        void displayInventorySkill();
        void displayInventoryEngimon();
        void learnSkill(Engimon* E, Skill* S);
        bool battle(Engimon* musuh);
        int sumBasePowMastery(Engimon*);
        Engimon* breedingSpesies(Engimon* bapak, Engimon* emak);
        void inheritSkill(Engimon* bapak, Engimon* emak, Engimon* anak);
        void breeding (Engimon* bapak, Engimon* emak);
        //void breeding (Engimon* bapak, Engimon* emak);
        Skill* getSkillbyMastery(Engimon*, Engimon*);
        float getAdvantage(Engimon*,Engimon*);
        Engimon* generateRandomChild(string namaAnak, string namaBapak, string namaEmak);
        void printAsciiKalah();
        void printAsciiMenang();
        Skill* getSkillAt(int n);
        Engimon* getEngimonAt(int n);
};

#endif