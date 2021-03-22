// File Point.hpp

#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <iostream>

using namespace std;

class Point {
private:
    int x;
    int y;
    char type; // Berisi : - untuk Grassland atau o untuk Sea
    char chara; // Berisi : Player atau Engimon atau ' ' jika tidak ditempati
    static const char high[]; // Array simbol kapital
    static const char low[]; // Array simbol huruf kecil
    static const char grass[]; // Array simbol engimon grass
    static const char sea[]; // Array simbol engimon sea
public:
    // Ctor, cctor, dtor, operator assignment (Kayaknya yang perlu cuma ctor)
    Point();
    Point(int x, int y, char t);
    Point(const Point& other);
    //~Point();
    Point& operator=(const Point& other);

    // Getter
    int getX() const;
    int getY() const;
    char getType() const;
    char getChara() const;

    // Setter
    void setX(int x);
    void setY(int y);
    void setType(char t); // Kayaknya gaperlu, tipe tile gabisa berubah2 kan?
    void setChara(char c);

    // Boolean function
    bool isMember(const char arr[], char t, int size); // Mengembalikan true jika t merupakan anggota dari array of char arr
    bool isOccupied(); // Mengembalikan true jika tile tersebut ditempat Player / Engimon
    bool isGrassland(); // Mengembalikan true jika tile berjenis Grassland
    bool isSea(); // Mengembalikan true jika tile berjenis Sea
    bool isHighLevel(); // Mengembalikan true jika Engimon yang menempati tile berlevel tinggi
    bool isLowLevel(); // Mengembalikan true jika Engimon yang menempati tile berlevel rendah
    bool isGrassEngimon(char t); // Mengembalikan true jika Engimon yang menempati tile merupakan Grass Engimon
    bool isSeaEngimon(char t); // Mengembalikan true jika Engimon yang menempati tile merupakan Sea Engimon
    bool isBothEngimon(char t); // Mengembalikan true jika Engimon yang menempati tile merupakan Water/Ground Engimon
};

#endif