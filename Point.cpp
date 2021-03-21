// File Point.cpp

#include <iostream>
#include <cctype>
#include "Point.hpp"

using namespace std;

const char Point::high[] = {'F','W','E','G','I','L','S','N','X'};
const char Point::low[] = {'f','w','e','g','i','l','s','n','x'};
const char Point::grass[] = {'F','E','G','L','N'};
const char Point::sea[] = {'W','I','S'};

// Ctor, cctor, dtor, operator assignment (Kayaknya yang perlu cuma ctor)
Point::Point(int x, int y, char t) {
    this->x = x;
    this->y = y;
    if (t == '-' || t == 'o') {
        this->type = t;
        this->chara = ' ';
    }
    // Asumsi bahwa spawn Player dan Active Engimon pertama kali selalu di Grassland
    else if (t == 'P' || toupper(t) == 'X') {
        this->type = '-';
        this->chara = t;
    }
    // Asumsi dia di Grassland pertama kali
    else if (isBothEngimon(t) || isGrassEngimon(t)) {
        this->type = '-';
        this->chara = t;
    }
    else if (isSeaEngimon(t)) {
        this->type = 'o';
        this->chara = t;
    }
}

Point::Point(const Point& other) {
    this->x = other.x;
    this->y = other.y;
    this->type = other.type;
    this->chara = other.chara;
}

Point::~Point() {
    cout << "Point (" << this->x << "," << this->y << ") destroyed" << endl;
}

Point& Point::operator=(const Point& other) {
    this->x = other.x;
    this->y = other.y;
    this->type = other.type;
    this->chara = other.chara;
    return *this;
}


// Getter
int Point::getX() const {
    return this->x;
}

int Point::getY() const {
    return this->y;
}

char Point::getType() const {
    return this->type;
}

char Point::getChara() const {
    return this->chara;
}


// Setter
void Point::setX(int x) {
    this->x = x;
}

void Point::setY(int y) {
    this->y = y;
}

// Kayaknya gaperlu, tipe tile gabisa berubah2 kan?
void Point::setType(char t) {
    this->type = t;
}

void Point::setChara(char c) {
    this->chara = c;
}


// Boolean function
bool Point::isMember(const char arr[], char t, int size) {
    // Hanya untuk pengecekan simbol (panjang array 8)
    bool found = false;
    int i = 0;
    while (!found && i < size) {
        if (arr[i] == t) {
            found = true;
        }
    }
    return found;
}

bool Point::isOccupied() {
    return this->chara != ' ';
}

bool Point::isGrassland() {
    return this->type == '-';
}

bool Point::isSea() {
    return this->type == 'o';
}

bool Point::isHighLevel() {
    return isMember(high,this->chara,9);
}

bool Point::isLowLevel() {
    return isMember(low,this->chara,9);
}

bool Point::isGrassEngimon(char t) {
    return isMember(grass,toupper(t),5);
}

bool Point::isSeaEngimon(char t) {
    return isMember(sea,toupper(t),3);
}

bool Point::isBothEngimon(char t) {
    return isGrassEngimon(t) && isSeaEngimon(t);
}