// File Map.hpp

#ifndef _MAP_HPP
#define _MAP_HPP
#include "Point.hpp"
#include "Engimon.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Map {
    private:
        const static int row=9;
        const static int column=12;
        // const static int limitSpawn user-defined;
        Point** map;
        /*char* filename;*/
    public:
        Map();
        Point** getMap();
        void setMap();
        void displayMap();
        void setMapCharaAt(int,int,char);
        // void setMapWildEngiAt(int, int, Engimon*);
        char getMapCharaAt(int,int);
        // Engimon* getMapWildEngiAt(int, int);
        char getMapTypeAt(int,int);
        void spawnWildEngimon();
        void getMove(string,char);
        Point getPosition(char);
        bool isAuthorized(char, int, int);
        void randomizeWildEngimonMove();
        // bool isWildAuthorized(Engimon*);
};

#endif