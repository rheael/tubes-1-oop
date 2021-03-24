#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Engimon.hpp"
#include "Element.hpp"
#include "Skill.hpp"
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
        void changeActiveEngimon(Engimon* newActiveEngimon);
        void interactActiveEngimon();
        void addSkillToInventory(Skill* S);
        void addEngimonToInventory(Engimon* E);
        void displayInventorySkill();
        void displayInventoryEngimon();
        void learnSkill(Engimon* E, Skill S);
        void battle(Engimon* musuh);
        int sumBasePowMastery(Engimon*);
        void breeding(Engimon& bapak, Engimon& emak);
        void decideChildElm(Engimon& bapak, Engimon& emak);
};

#endif