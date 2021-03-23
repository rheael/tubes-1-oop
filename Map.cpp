#include "Map.hpp"
#include "Point.hpp"
// #include "Engimon.hpp"
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
    // handle max spawned engimon, user?
    /*int i=rand();
    int j=rand();
    // randomize the x and y first, if it is modulo something then spawn
    // after that, the tile used will be (i%12 and j%9) 
    // know the tile,
    if((i+j)%7) {
        int newX=i%12;
        int newY=j%9;
        bool engimonSpawned = false;
        if(i%2==0) {
            if(map[newX][newY].getType()=='-') { // also the type of tile
                Engimon* wildEngi= new Charmamon("Wildcharm"); // w/ parameters?
                setMapCharaAt(newX, newY, 'f');
            }
            else {
                Engimon* wildEngi = new Snommon("Wildsnom"); // w/ parameters
                setMapCharaAt(newX, newY, 'i');
            }
        }
    }*/
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
        throw(0);
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

bool Map::isAuthorized(char chara, int col, int ro) {
    /* determine whether the char can access the map or not */
    /* later for engimon */
    return(col>=0 && col<column && ro>=0 && ro<row);
    // compatible tile with engimons
}

/* 
g++ map.cpp point.cpp driver_map.cpp -o drivermap1
./drivermap1 
*/