#include "Map.hpp"
#include <iostream>

using namespace std;

int main() {
    Map m = Map();
    m.displayMap();
    cout << "The player is located on:" << " " << m.getPlayerPosition().getX() << "," << m.getPlayerPosition().getY() << endl;
    return 0;
}