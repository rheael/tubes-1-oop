//Include engimon
//Include element
//Include skill
#include "Engimon.hpp"
#include "Point.hpp"

#include <vector>
#include <iostream>
using namespace std;

class Player {
    private:
        // Point Position;
        // Engimon activeEngimon;
        Inventory<InventoryItem<Skill>> InventorySkill;
        Inventory<InventoryItem<Engimon>> InventoryEngimon;
        int nbInventory;
        int MAX_CAP;

    public:
        Player();
        void keAtas();
        void keBawah();
        void keKanan();
        void keKiri();
        Point getPosition();
        void setPosition(int X, int Y);
        Engimon getActiveEngimon();
        void changeActiveEngimon(Engimon newActiveEngimon);
        void interactActiveEngimon();
        void displayInventorySkill();
        void displayInventoryEngimon();
        void learnSkill(Engimon E, Skill S);
        void battle(Engimon musuh);
        int sumBasePowMastery(Engimon);
        void breeding(Engimon bapak, Engimon emak);
};

template <class T> //T bisa berupa Skill atau Engimon
class Inventory {
    private:
        int NB_ELMT;
        vector<InventoryItem<T>> List();
    public:
        Inventory() { 
            NB_ELMT = 0;
        }

        void addEngimon(T newItem) { //cek dulu udh penuh belom
            if (isExist(newItem)) {
                for (int i=0; i<NB_ELMT; i++) {
                    if (List[i].getItem() == newItem) {
                        List[i].setNbItem(List[i].getNbItem()+1);
                        break;
                    }
                }
            } else {
                List.push_back(newItem);
                NB_ELMT++;
            }
        }

        void deleteItem(T newItem) {
            if (isExist(newItem)) { // Mengecek apakah item ada di list
                for (int i=0; i<NB_ELMT; i++) { // Mencari letak item
                    if (List[i].getItem() == newItem) {
                        List[i].setNbItem(List[i].getNbItem()-1); // Mengurangi jumlahnya

                        if (List[i].getNbItem() == 0) { // Kalau ternyata jmlnya jd 0, kita hapus dari list
                            List.erase(List.begin()+i);
                            NB_ELMT--;
                        }

                        break;
                    }
                }
            } else {
                throw "Item yang ingin dihapus tidak ada\n";
            }
        }            

        bool isExist(T item) {
            bool found = false;
            for (int i=0; i<NB_ELMT; i++) {
                if (InventoryEngimon[i].getItem() == item) {
                    found = true;
                    break;
                }
            }
            return found;
        }

        int getNbElmt() {return NB_ELMT;}
};

template <class T>
class InventoryItem {
    private:
        T item;
        int nbItem;
    public:
        InventoryItem(T i, int ni) {
            item = i;
            nbItem = ni;
        }

        void setNbItem(int n) {nbItem = n;}
        
        T getItem() {return item;}

        int getNbItem() {return nbItem;}
};