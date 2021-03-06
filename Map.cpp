#include "Map.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

Map::Map() {
    char ch;
    Point** newmap=new Point*[row];
    countEngimon = 0;
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
    int i=(rand() % 12) + 1;
    int j=(rand() % 9) + 1;
    // randomize the x and y first, if it is modulo something then spawn
    // after that, the tile )used will be (i%12 and j%9) 
    // if((i+j)%7==0) {
        int newX=i;
        int newY=j;
        Engimon* wildEngi=NULL;
        if(!map[newY][newX].isOccupied()) {
            if(isAuthorized(newX,newY)) {
                // Add level randomizer, 
                int newLevel = (rand() % 20) + 1;
                if(map[newY][newX].getType()=='-') { // the type of tile
                    if(i%2==0 && !i%3==0 && !i%5==0 && !i%7==0 && !i%13==0) {
                        wildEngi = new Charmamon();
                        wildEngi->setLevel(newLevel);
                    }
                    if(i%3==0 && !i%5==0 && !i%7==0 && !i%13==0) {
                        wildEngi = new Pikamon(); // electric
                        wildEngi->setLevel(newLevel);
                    }
                    if(i%5==0 && !i%7==0 && !i%13==0) {
                        wildEngi = new Rumblemon(); // ground
                        wildEngi->setLevel(newLevel);
                    }
                    if(i%7==0 && !i%13==0) {
                        wildEngi = new Rotomon(); // fire and electric
                        wildEngi->setLevel(newLevel);
                    }
                    if(i%13==0) {
                        wildEngi = new Gastromon(); //water, ground
                        wildEngi->setLevel(newLevel);
                    }
                }
                else {
                    if(i%2==0 && !i%3==0) {
                        wildEngi = new Snommon(); // ice
                        wildEngi->setLevel(newLevel);
                    }
                    if(i%3==0) {
                        wildEngi = new Squirtlmon(); // water
                        wildEngi->setLevel(newLevel);
                    }
                    if(i%5==0) {
                        wildEngi = new Sealmon(); //ice, water
                        wildEngi->setLevel(newLevel);
                    }
                }
                if(wildEngi!=NULL) {
                    cout << "There comes " << wildEngi->getSpecies() << endl;
                    if (newLevel > 10) {
                        upperCase(wildEngi, newX, newY);
                    }
                    else {
                        setMapCharaAt(newX, newY, engimonChara(wildEngi));
                    }
                    setMapWildEngiAt(newX, newY,wildEngi);
                    countEngimon++;
                }
            }
        }
    // }
}

void Map::getMove(string move, char chara) {
    // if used for player, chara = P
    // coordinate with the player movement later
    // doesnt get called when the movement throws an exception
    int x=getPosition(chara).getX();
    int y=getPosition(chara).getY();
    int xEngi = getPosition('X').getX();
    int yEngi = getPosition('X').getY();
    Engimon* e = getMapWildEngiAt(xEngi,yEngi);
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
        setMapCharaAt(xEngi,yEngi,' ');
        setMapCharaAt(x,y,'X');
        setMapWildEngiAt(x,y,e);
        setMapWildEngiAt(xEngi, yEngi, NULL);
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
            if(isWildAuthorized(e,newCol,newRo)) {
                setMapCharaAt(newCol, newRo,engimonChara(e)); // engimon type later, maybe store the chara in engimon
                setMapCharaAt(currentCol, currentRo,' ');
                setMapWildEngiAt(newCol, newRo,e);
                setMapWildEngiAt(currentCol, currentRo, NULL);
            }
                cout << "The wild engimon " << e->getSpecies() << " has moved" << endl;
        }
    }
}

// if the wild engi is fire, ground, electric : only on grassland
// if the wild engi is water / ice : only on sea
bool Map::isFire(Engimon* e) {
    return (e->punyaElemen("Fire")); 
}

bool Map::isWater(Engimon* e) {
    return (e->punyaElemen("Water"));
}

bool Map::isIce(Engimon* e) {
    return (e->punyaElemen("Ice"));
}

bool Map::isElectric(Engimon* e) {
    return (e->punyaElemen("Electric"));
}

bool Map::isGround(Engimon* e) {
    return (e->punyaElemen("Ground"));
}

bool Map::isFireElectric(Engimon* e) {
    return(isFire(e) && isElectric(e));
}

bool Map::isWaterIce(Engimon* e) {
    return(isWater(e) && isIce(e));
}

bool Map::isWaterGround(Engimon* e) {
    return(isWater(e) && isGround(e));
}

bool Map::isGrassland(Engimon* e) {
    return  isFire(e) || (isElectric(e)) || (isGround(e)) || (isFireElectric(e)) || (isWaterGround(e));
}

bool Map::isSea(Engimon* e) {
    return (isWater(e) || isIce(e)) || (isWaterIce(e)) || (isWaterGround(e));
}

char Map::engimonChara(Engimon* e) {
    if (isLevelMoreThan(e,10)) {
        if(isWaterIce(e)) {
            return 'S';   
        }
        if(isFireElectric(e)) {
            return 'L';
        }
        if(isWaterGround(e)) {
            return 'N';
        }
        else {
            if(isWater(e)) {
                return 'W';
            }
            if(isGround(e)) {
                return 'G';
            }
            if(isFire(e)) {
                return 'F';
            }
            if(isIce(e)) {
                return 'I';
            }
            if(isElectric(e)) {
                return 'E';
            }
        }
    }
    else {
        if(isWaterIce(e)) {
            return 's';   
        }
        if(isFireElectric(e)) {
            return 'l';
        }
        if(isWaterGround(e)) {
            return 'n';
        }
        else {
            if(isWater(e)) {
                return 'w';
            }
            if(isGround(e)) {
                return 'g';
            }
            if(isFire(e)) {
                return 'f';
            }
            if(isIce(e)) {
                return 'i';
            }
            if(isElectric(e)) {
                return 'e';
            }
        }
    }
}

bool Map::isWildAuthorized(Engimon* e, int col, int ro) {
    if(!isGrassland(e) && isSea(e)) {
        return(isAuthorized(col,ro) && map[col][ro].getType()=='o'); 
    }
    else if(isGrassland(e) && !isSea(e)) {
        return(isAuthorized(col,ro) && map[col][ro].getType()=='-');
    }
    else { // compatible for both
        return(isAuthorized(col,ro));
    }
}

bool Map::isLevelMoreThan(Engimon* e,int level) {
    return(e->getLevel()>level);
}

void Map::upperCase(Engimon *e, int col, int ro) {
    if(isLevelMoreThan(e,10)) { // the level is merely an example
        setMapCharaAt(col,ro,toupper(engimonChara(e)));
    }
}

int Map::getCountEngimon() {
    return countEngimon;
}

void Map::decrementCountEngimon() {
    countEngimon--;
}

// Point Map::getEnemy() {
//     int x=getPosition('P').getX();
//     int y=getPosition('P').getY();
    // if (loc == "w") {
    //     p = map[x][y+1];
    // }
    // if (loc == "a") {
    //     p = map[x-1][y];
    // }
    // if (loc == "s") {
    //     p = map[x][y-1];
    // }
    // if (loc == "d") {
    //     p = map[x+1][y];
    // }
    // int xActEngi = getPosition('X').getX();
    // int yActEngi = getPosition('X').getY();
    // if (isAuthorized(x+1,y) && (x+1 != xActEngi && y != yActEngi)) {
    //     cout << "Here" << endl;
    //     if (getMapWildEngiAt(x+1,y) != NULL) {
    //         return map[y][x+1];
    //     }
    // }
    // else if (isAuthorized(x-1,y) && (x-1 != xActEngi && y != yActEngi)) {
    //     if (getMapWildEngiAt(x-1,y) != NULL) {
    //         return map[y][x-1];
    //     }
    // }
    // else if (isAuthorized(x,y+1) && (x != xActEngi && y+1 != yActEngi)) {
    //     if (getMapWildEngiAt(x,y+1) != NULL) {
    //         return map[y+1][x];
    //     }
    // }
    // else if (isAuthorized(x,y-1) && (x != xActEngi && y-1 != yActEngi)) {
    //     if (getMapWildEngiAt(x,y-1) != NULL) {
    //         return map[y-1][x];
    //     }
    // }
    // else {
    //     Point p = Point();
    //     p.setX(-1);
    //     p.setY(-1);
    //     return p;
    // }
// }

// int Map::getEnemyX() {
//     int x=getPosition('P').getX();
//     int xActEngi = getPosition('X').getX();
// }

// int Map::getEnemyY() {
//     int y=getPosition('P').getY();
//     int yActEngi = getPosition('X').getY();
// }

// int Map::getEnemy() {
    
// }

// when engimon levels up, maybe just check whether it has gone to a level
// where it can be capitalized or not
// and then setChara with capitalized type of the engi

/* 
g++ map.cpp point.cpp driver_map.cpp engimon.cpp element.cpp skill.cpp -o drivermap1
./drivermap1 
*/