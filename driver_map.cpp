#include "Map.hpp"
#include <iostream>

using namespace std;

int main() {
    Map m = Map();
    m.displayMap();
    cout << "The player is located on:" << " " << m.getPosition('P').getX() << "," << m.getPosition('P').getY() << endl;
    string input;
    while(input!="end") {
        cin >> input;
        // to make player move {
        try {
            (m.getMove(input,'P'));
            m.spawnWildEngimon();
        } 
        catch (int x) {
            cout << "Invalid move!\n";
        }
        //m.spawnWildEngimon();
        m.displayMap();
    }
    return 0;
}