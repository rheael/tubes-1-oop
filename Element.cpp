#include <iostream>
using namespace std;
#include "Element.hpp"


Element :: Element(){
    jumlahel = 0;
    namael = new string[0];
    elmt = new int[0];
}

Element :: Element(int jmlel, string elem[]){
    jumlahel = jmlel;
    elmt = new int[5];
    namael = new string[jumlahel];
    int count = 0;
    for (int i = 0; i < jumlahel; i++)
    {
        if(elem[i]=="Fire"){
            elmt[0]=1;
            namael[count]=elem[i];
            count++;
        }
        else if (elem[i]=="Water"){
            elmt[1]=1;
            namael[count]=elem[i];
            count++;
        }
        else if (elem[i]=="Electric"){
            elmt[2]=1;
            namael[count]=elem[i];
            count++;
        }
        else if (elem[i]=="Ground"){
            elmt[3]=1;
            namael[count]=elem[i];
            count++;
        }
        else if (elem[i]=="Ice"){
            elmt[4]=1;
            namael[count]=elem[i];
            count++;
        }
    }
}

Element :: Element(const Element& el){
    jumlahel = el.jumlahel;
    namael = new string[jumlahel];
    for (int i = 0; i < jumlahel; i++)
    {
        this->namael[i] = el.namael[i];
    }
    elmt = new int[5];
    for (int i = 0; i < 5; i++)
    {
        this->elmt[i] = el.elmt[i];
    }
}

Element& Element::operator=(const Element& el){
    delete[] namael;
    delete[] elmt;
    this->jumlahel = el.jumlahel;
    namael = new string[jumlahel];
    elmt = new int[5];
    for (int i = 0; i < jumlahel; i++)
    {
        namael[i]=el.namael[i];
    }
    for (int i = 0; i < 5; i++)
    {
        elmt[i]=el.elmt[i];
    }
    return *this;
}

Element :: ~Element(){
    delete[] elmt;
    delete[] namael;
}

int Element::getjmlel(){
    return jumlahel;
}

void Element::getidxel(int arr[]){
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (elmt[i]==1)
        {
            arr[count]=i;
            count++;
        }
        
    }
    
}