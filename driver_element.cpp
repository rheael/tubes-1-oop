#include <iostream>
using namespace std;
#include "Element.hpp"
#include <string>

int main() {
    // TEST 1 Element()
    Element *a = new Element();
    int jml1 = (*a).getjmlel();
    cout<<jml1<<endl;
    for (int i = 0; i < jml1; i++)
    {
        string nama = (*a).getNameAtIdx(i);
        cout<<nama<<endl;
    }
    
    // TEST 2 Element (jml, array[])
    string arr[] = {"Fire", "Ground"};
    Element c(2,arr);
    int jml2 = c.getjmlel();
    cout<<jml2<<endl;
    for (int i = 0; i < jml2; i++)
    {
        string nama = (c).getNameAtIdx(i);
        cout<<nama<<endl;
    }

    // TEST 3 Element (&el)
    Element d(c);
    int jml3 = c.getjmlel();
    cout<<jml3<<endl;
    for (int i = 0; i < jml3; i++)
    {
        string nama = (d).getNameAtIdx(i);
        cout<<nama<<endl;
    }

    // TEST 4 operator=
    Element *e = new Element();
    *e=d;
    int jml4 = c.getjmlel();
    cout<<jml4<<endl;
    for (int i = 0; i < jml4; i++)
    {
        string nama = (*e).getNameAtIdx(i);
        cout<<nama<<endl;
    }

    // TEST 5 operator==
    // Sama
    cout<<(*e==d);
    // Beda
    string array[] = {"Water, Ice"};
    string array2[] = {"Ground", "Fire"};
    Element pertama(2,array);
    Element kedua(2,array2);
    cout<<(pertama==kedua);

}