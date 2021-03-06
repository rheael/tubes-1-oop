#include "Map.hpp"
#include <iostream>

using namespace std;


int main() {
    Map m = Map();
    m.displayMap();
    int MaxSpawned;
    cout << "Enter max spawned engimon?" << endl;
    cin >> MaxSpawned;
    m.setMapCharaAt(0,0,'P');
    cout << "The player is located on:" << " " << m.getPosition('P').getX() << "," << m.getPosition('P').getY() << endl;
    string input;
    //int spawned = 0;
    while(input!="end") {
        cin >> input;
        // to make player move {
        if(input!="end") {
            try {
                m.getMove(input,'P');
                m.randomizeWildEngimonMove();
                m.spawnWildEngimon();
            } 
            catch (int x) {
                cout << "Invalid move!\n";
            }
        }
        m.displayMap();
    }
    return 0;
}