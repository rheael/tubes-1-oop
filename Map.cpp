#include "Map.hpp"
#include "Point.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

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
            map[i][j].setX(i);
            map[i][j].setY(j); 
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
            if(map[i][j].getChara()!=' ') {
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
    map[x][y].setChara(chara);
}

char Map::getMapCharaAt(int x,int y) {
    return(map[x][y].getChara());
}

char Map::getMapTypeAt(int x,int y) {
    return(map[x][y].getType());
}

void Map::spawnWildEngimon() {
    // handle max spawned engimon
    int i=rand();
    int j=rand();
    // set chara at int i and j
    // new Engimon
    // the attribute and type is based on the randomized
}

void Map::getPlayerMove(char* move) {
    /*
    // coordinate with the player movement later
    // doesnt get called when the movement throws an exception
    if(strcmp(move,"w")) {
        setMapCharaAt(getPlayerPosition().getX()+1,getPlayerPosition().getY()));
    }
    if(strcmp(move,"a")) {
        // same as above but different increment/decrement
    }
    if(strcmp(move,"s")) {

    }
    if(move=="d") {

    } */
} 

Point Map::getPlayerPosition() {
    // coordinate with player?
    Point playerPosition;
    for(int i=0;i<row;i++) {
        for(int j=0;j<column;j++) {
            if(map[i][j].getChara()=='P') {
                playerPosition=map[i][j];
                break;
            }
        }
    }
    return playerPosition;
}

/* 
g++ map.cpp point.cpp driver_map.cpp -o drivermap1
./drivermap1 
*/