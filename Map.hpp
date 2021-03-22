// File Map.hpp

#ifndef _MAP_HPP
#define _MAP_HPP
#include "Point.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Map {
    private:
        const static int row=9;
        const static int column=12;
        Point** map;
        /*char* filename;*/
    public:
        Map();
        Point** getMap();
        void setMap();
        void displayMap();
        void setMapCharaAt(int,int,char);
        char getMapCharaAt(int,int);
        char getMapTypeAt(int,int);
        void spawnWildEngimon();
        void getPlayerMove(char*);
        Point getPlayerPosition();
};

#endif