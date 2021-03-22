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
        m.getMove(input,'P');
        m.displayMap();
    }
    return 0;
}