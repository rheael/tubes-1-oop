#include "Map.hpp"
#include "Point.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

// to - do : spawn engimons
// determine max spawned engimon (based on player's input, maybe on main)
// display based on capitalized or not
// exception handling etc

Map::Map() {
    char ch;
    Point** newmap=new Point*[row];
    for (int i = 0; i < row; i++){
        newmap[i] = new Point[column];
    }
    this->map=newmap;
    fstream fin("map.txt", fstream::in);
    for(int i=0;i<row;i++) {
        for(int j=0;j<column;j++) {
            fin >> ch;
            map[i][j].setY(i);
            map[i][j].setX(j); 
            // define the type based on the i and j, the field has its own constant size
            if((j<6 && i<=5) || (i>5)) {
                map[i][j].setType('-');
            }
            else {
                map[i][j].setType('o');
            }
            if(ch!='-' && ch!='o') {
                map[i][j].setChara(ch);
            }
        }
    }
}

void Map::displayMap() {
    cout << "--- MAP ---\n\n";
    for(int i=0;i<row;i++) {
        for(int j=0;j<column;j++) {
            if(map[i][j].isOccupied()) {
                cout << map[i][j].getChara();
            }
            else {
                cout << map[i][j].getType();
            }
        }
        cout << '\n';
    }
}

void Map::setMapCharaAt(int x, int y, char chara) {
    map[y][x].setChara(chara);
}

char Map::getMapCharaAt(int x,int y) {
    return(map[y][x].getChara());
}

char Map::getMapTypeAt(int x,int y) {
    return(map[y][x].getType());
}

void Map::spawnWildEngimon() {
    // handle max spawned engimon
    int i=rand();
    int j=rand();
    // set chara at int i and j
    // new Engimon
    // the attribute and type will probably be based on the randomized integer
}

void Map::getMove(string move, char chara) {
    // if used for player, chara = P
    // coordinate with the player movement later
    // doesnt get called when the movement throws an exception
    int x=getPosition(chara).getX();
    int y=getPosition(chara).getY();
    int newX,newY;
    if(move=="w") {
        newX=x;
        newY=y-1;
    }
    if(move=="a") {
        newX=x-1;
        newY=y;
    }
    if(move=="s") {
        newX=x;
        newY=y+1;
    }
    if(move=="d") {
        newX=x+1;
        newY=y;
    }
    if(isAuthorized(chara,newX,newY)) {
        setMapCharaAt(newX,newY,chara);
        setMapCharaAt(x,y,' ');
    }
    else {
        throw newX, newY;  // exception?
    }
} 

Point Map::getPosition(char chara) {
    // position of engimon 
    // position of Player (P)
    Point charaPosition;
    for(int i=0;i<row;i++) {
        for(int j=0;j<column;j++) {
            if(map[i][j].getChara()==chara) {
                charaPosition=map[i][j];
                break;
            }
        }
    }
    return charaPosition;
}

bool Map::isAuthorized(char chara, int i, int j) {
    /* determine whether the char can access the map or not */
    /* later for engimon */
    return(map[i][j].getType()!=' ');
}

/* 
g++ map.cpp point.cpp driver_map.cpp -o drivermap1
./drivermap1 
*/