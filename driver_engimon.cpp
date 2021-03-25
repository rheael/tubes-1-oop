#include "Engimon.hpp"
#include <iostream>
using namespace std;

int main() {
    // TEST 1
    Charmamon *C1 = new Charmamon();
    C1->showData();

    // UDAH BISA :D
    Skill *S1 = new Skill();
    C1->operator<<(*S1);
    C1->showData();

    cout<<("----------------")<<endl;

    Squirtlmon C2;
    Skill S2;
    C2 << S2;
    C2.showData();
    return 0;
}