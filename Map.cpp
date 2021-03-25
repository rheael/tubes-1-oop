#include "Map.hpp"
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

void Map::setMapWildEngiAt(int x, int y, Engimon* e) {
    map[y][x].setWildEngimon(e);
}

char Map::getMapCharaAt(int x,int y) {
    return(map[y][x].getChara());
}

char Map::getMapTypeAt(int x,int y) {
    return(map[y][x].getType());
}

Engimon* Map::getMapWildEngiAt(int x, int y) {
    return(map[y][x].getWildEngimon());
}

/*Engimon&*/ void Map::spawnWildEngimon() {
    // User will input max spawned Engimon, probably on main
    int i=rand();
    int j=rand();
    // randomize the x and y first, if it is modulo something then spawn
    // after that, the tile used will be (i%12 and j%9) 
    if((i+j)%7==0) {
        int newX=i%12;
        int newY=j%9;
        if(!map[newY][newX].isOccupied()) {
            if(map[newY][newX].getType()=='-') { // the type of tile
                if(isAuthorized(newX,newY)) {
                    Engimon* wildEngi = new Charmamon();
                    cout << "There comes charmamon!" << endl; 
                    setMapCharaAt(newX, newY, 'f');
                    setMapWildEngiAt(newX, newY,wildEngi);
                }
            }
            else {
                if(isAuthorized(newX,newY)) {
                    Engimon* wildEngi = new Snommon();
                    cout << "There comes snommon!" << endl;
                    setMapCharaAt(newX, newY, 'i');
                    setMapWildEngiAt(newX, newY,wildEngi);
                }
            }
        }
    }
    // return *wildEngi
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
    if(isAuthorized(newX,newY) && (!map[newY][newX].isOccupied())) {
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

bool Map::isAuthorized(int col, int ro) {
    return (col>=0 && col<column && ro>=0 && ro<row);
}

// throw exception(?) if wildengi and player goes to the same tile
// dunno if its handled on the driver or here
void Map::randomizeWildEngimonMove() {
    int currentCol=rand()%12;
    int currentRo=rand()%9;
    Engimon* e=getMapWildEngiAt(currentCol, currentRo); // could be null
    int randomizer=rand();
    if(e!=NULL) {
        int i=rand()%(2)-1;
        int j=rand();
        if(i!=0) {
            int newCol=currentCol;
            int newRo=currentRo;
            if(j%2==0) {
                newCol=currentCol+i;
            }
            else {
                newRo=currentRo+i;
            }
            if(isWildAuthorized(e,newRo,newCol)) {
                setMapCharaAt(newCol, newRo,'f'); // engimon type later, maybe store the chara in engimon
                setMapCharaAt(currentCol, currentRo,' ');
                setMapWildEngiAt(newCol, newRo,e);
                setMapWildEngiAt(currentCol, currentRo, NULL);
            }
                cout << "the wild engimon has moved" << endl;
        }
    }
}

// if the wild engi is fire, ground, electric : only on grassland
// if the wild engi is water / ice : only on sea

bool Map::isGrassland(Engimon* e) {
    return (e->punyaElemen("water")) && (e->punyaElemen("ice"));
}

bool Map::isWater(Engimon* e) {
    return (e->punyaElemen("ground") && (e->punyaElemen("fire") && (e->punyaElemen("electric"))));
}

bool Map::isWildAuthorized(Engimon* e, int col, int ro) {
    if(!isGrassland(e) && isWater(e)) {
        return(isAuthorized(col,ro) && map[col][ro].getType()=='o'); 
    }
    else if(isGrassland(e) && !isWater(e)) {
        return(isAuthorized(col,ro) && map[col][ro].getType()=='-');
    }
    else { // compatible for both
        return(isAuthorized(col,ro));
    }
}

bool Map::isLevelMoreThan(Engimon* e,int level) {
    return(e->getLevel()>level);
}

// when engimon levels up, maybe just check whether it has gone to a level
// where it can be capitalized or not
// and then setChara with capitalized type of the engi

/* 
g++ map.cpp point.cpp driver_map.cpp engimon.cpp element.cpp skill.cpp -o drivermap1
./drivermap1 
*/