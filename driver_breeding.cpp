#include "Engimon.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
    Charmamon mamon();
    Squirtlmon squirt();
    string typeBapak = typeid(mamon).name();
    string typeAnak = typeid(mamon).name();
    string typeEmak = typeid(mamon).name();
    string tes = "Charmamon";
    // test jenisnya
    if(typeBapak == typeEmak && typeBapak == typeAnak){
        cout << typeBapak << '\n';
    } else {cout << "ga bs" << endl;}
    
    if (typeBapak.find(tes) != std::string::npos) {
        std::cout << "found!" << '\n';
    }
}
