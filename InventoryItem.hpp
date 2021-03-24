#ifndef __INVENTORYITEM_HPP__
#define __INVENTORYITEM_HPP__

#include <vector>
#include <iostream>
using namespace std;

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

#endif