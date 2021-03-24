// File driver_point.cpp

#include "Point.hpp"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

string printBool(bool b) {
    if (b == 1) {
        return "True";
    }
    else {
        return "False";
    }
}

int main() {
    Point *p1 = new Point();

    cout << "Detail Point: " << endl;
    cout << "x : " << (*p1).getX() << endl;
    cout << "y : " << (*p1).getY() << endl;
    cout << "type : " << (*p1).getType() << endl;
    cout << "chara : " << (*p1).getChara() << endl << endl;
    
    (*p1).setX(3);
    (*p1).setY(5);
    (*p1).setType('o');
    (*p1).setChara('w');

    cout << "Setting Point..." << endl << endl;
    cout << "Detail Point: " << endl;
    cout << "x : " << (*p1).getX() << endl;
    cout << "y : " << (*p1).getY() << endl;
    cout << "type : " << (*p1).getType() << endl;
    cout << "chara : " << (*p1).getChara() << endl << endl;

    cout << "Identifying Point:" << endl << endl;
    cout << "Is it Grassland tile? " << printBool((*p1).isGrassland()) << endl;
    cout << "Is it Sea tile? " << printBool((*p1).isSea()) << endl;
    cout << "Is is occupied? " << printBool((*p1).isOccupied()) << endl;
    cout << "Is it a Grass Engimon? " << printBool((*p1).isGrassEngimon()) << endl;
    cout << "Is it a Sea Engimon? " << printBool((*p1).isSeaEngimon()) << endl;
    cout << "Is the engimon high leveled? " << printBool((*p1).isHighLevel()) << endl;
    cout << "Is the engimon low leveled? " << printBool((*p1).isLowLevel()) << endl;

    return 0;
}