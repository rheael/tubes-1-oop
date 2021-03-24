#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include <vector>
#include <iostream>
#include "InventoryItem.hpp"
using namespace std;

template <class T> //T bisa berupa Skill atau Engimon
class Inventory {
    private:
        int NB_ELMT;
        vector<InventoryItem<T>> List;
    public:
        Inventory() { 
            NB_ELMT = 0;
        }

        void addItem(T newItem) { //cek dulu udh penuh belom
            if (isExist(newItem)) {
                for (int i=0; i<NB_ELMT; i++) {
                    if (List[i].getItem() == newItem) {
                        List[i].setNbItem(List[i].getNbItem()+1);
                        break;
                    }
                }
            } else {
                List.push_back(InventoryItem<T>(newItem, 1));
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
                cout << "Item yang ingin dihapus tidak ada\n";
            }
        }            

        bool isExist(T item) {
            bool found = false;
            for (int i=0; i<NB_ELMT; i++) {
                if (List[i].getItem() == item) {
                    found = true;
                    break;
                }
            }
            return found;
        }

        int getNbElmt() {return NB_ELMT;}

        InventoryItem<T> getItemAtIdx(int idx) {
            return List[idx];
        }
};

#endif