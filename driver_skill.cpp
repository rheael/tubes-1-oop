#include "Skill.hpp"
#include <iostream>
using namespace std;

int main() {
    // TEST 1
    Skill *S1 = new Skill();
    cout << S1->getnama() << endl;

    // TEST 2
    string *arr = new string[2];
    arr[0] = "Fire";
    arr[1] = "Ice";
    Skill *S2 = new Skill("Berenang", 100, 3, 2, arr);
    cout << S2->getnama() << endl;
    cout << S2->getelemen().getNameAtIdx(0) << endl;
    cout << S2->getelemen().getNameAtIdx(1) << endl;

    return 0;
}