#ifndef __ELEMENT_HPP__
#define __ELEMENT_HPP__
#include <iostream>
#include <string>
using namespace std;

class Element
{
protected:
    int jumlahel;
    string *namael;
    int *elmt;
public:
    Element();
    Element(int, string[]);
    Element(const Element&);
    Element& operator=(const Element&);
    ~Element();
    int getjmlel();
    void getidxel(int[]);
    string getNameAtIdx(int idx);
};

#endif