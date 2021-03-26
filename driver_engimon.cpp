#include "Engimon.hpp"
#include <iostream>
using namespace std;

int main() {
    // TEST 1
    /*
    Charmamon *C1 = new Charmamon();
    C1->showData();

    // UDAH BISA :D
    Skill *S1 = new Skill();
    C1->operator<<(*S1);
    string a = C1->getSpecies();
    cout << a << endl;

    cout<<("----------------")<<endl;

    Squirtlmon C2;
    Skill S2;
    C2 << S2;
    C2.showData();
    */

    Engimon** daftarEngimon = new Engimon*[10];
    Charmamon C1("charmy");
    daftarEngimon[0] = &C1;
    daftarEngimon[0]->showData();

    string arr [] = {"Fire","Ground"};
    Skill a("Lava",10,1,1,arr);
    C1 << a;
    C1.showData();

    return 0;
}
