#include "Skill.hpp"  // ini butuh kelas skill :D
#include <iostream>
#include <string>
using namespace std;

class Engimon{
    private:
        int numAbility;
    protected:
        string name;
        string parent1name;
        string parent2name;
        Skill* ability;
        int level;
        int exp;
        int cumulativeExp;
        static const int maxExp = 5000;
    public:
        // ctor, cctor, dtor
        Engimon();
        Engimon(string nama);
        Engimon(string nama, string napar1, string napar2);
        Engimon(const Engimon&);
        Engimon(Element el);
        virtual ~Engimon();
        // getter, setter
        string getName();
        string getParent1Name();
        string getParent2Name();
        virtual string getParent1Species()=0;
        virtual string getParent2Species()=0;
        virtual Element getElemen()=0;
        void setName(string);
        int getLevel();
        Skill* getSkill();
        //method overloading
        Engimon& operator=(const Engimon&);
        Engimon& operator<<(const Skill&);
        // method lainnya
        void levelUp();
        void levelDown(int);
        void addExp(int);
        void die(); // --------------------ini apakah iya?
        virtual void showData();
        virtual void talk()=0;
        virtual bool punyaElemen(string)=0;
        virtual int nbEl()=0;
        bool punyaSkill(Skill);
};

class Charmamon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        static const string parentSpecies;
    public:
        // ctor, cctor, dtor
        Charmamon();
        Charmamon(string nama);
        Charmamon(string nama, string napar1, string napar2);
        //Charmamon(const Engimon&);
        //~Charmamon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Squirtlmon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        static const string parentSpecies;
    public:
        // ctor, cctor, dtor
        Squirtlmon();
        Squirtlmon(string nama);
        Squirtlmon(string nama, string napar1, string napar2);
        //Squirtlmon(const Engimon&);
        //~Squirtlmon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Pikamon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        static const string parentSpecies;
    public:
        // ctor, cctor, dtor
        Pikamon();
        Pikamon(string nama);
        Pikamon(string nama, string napar1, string napar2);
        //Pikamon(const Engimon&);
        //~Pikamon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Rumblemon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        static const string parentSpecies;
    public:
        // ctor, cctor, dtor
        Rumblemon();
        Rumblemon(string nama);
        Rumblemon(string nama, string napar1, string napar2);
        int getElem();
        //Rumblemon(const Engimon&);
        //~Rumblemon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Snommon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        static const string parentSpecies;
    public:
        // ctor, cctor, dtor
        Snommon();
        Snommon(string nama);
        Snommon(string nama, string napar1, string napar2);
        int getElem();
        //Snommon(const Engimon&);
        //~Snommon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Rotomon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        string parent1Species;
        string parent2Species;
    public:
        // ctor, cctor, dtor
        Rotomon();
        Rotomon(string nama);
        Rotomon(string nama, string napar1, string napar2);
        Rotomon(string nama, string napar1, string napar2, string spec1, string spec2);
        //Rotomon(const Engimon&);
        //~Rotomon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Sealmon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        string parent1Species;
        string parent2Species;
    public:
        // ctor, cctor, dtor
        Sealmon();
        Sealmon(string nama);
        Sealmon(string nama, string napar1, string napar2);
        Sealmon(string nama, string napar1, string napar2, string spec1, string spec2);
        //Sealmon(const Engimon&);
        //~Sealmon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

class Gastromon: public Engimon{
    protected:
        static const Element elemen;
        static const Skill uniqueSkill;
        string parent1Species;
        string parent2Species;
    public:
        // ctor, cctor, dtor
        Gastromon();
        Gastromon(string nama);
        Gastromon(string nama, string napar1, string napar2);
        Gastromon(string nama, string napar1, string napar2, string spec1, string spec2);
        //Gastromon(const Engimon&);
        //~Gastromon();
        //getter, setter
        Element getElemen();
        Skill getuniqueSkill();
        string getParent1Species();
        string getParent2Species();
        // method lain
        void showData();
        void talk();
        bool punyaElemen(string);
        int nbEl();
};

// Template isinya getAdv Battle
template <class T1, class T2>
float GetAdv(T1 user, T2 enemy){
    float table[5][5];
    table[0][0]=1;
    table[0][1]=0;
    table[0][2]=1;
    table[0][3]=0.5;
    table[0][4]=2;
    table[1][0]=2;
    table[1][1]=1;
    table[1][2]=0;
    table[1][3]=1;
    table[1][4]=1;
    table[2][0]=1;
    table[2][1]=2;
    table[2][2]=1;
    table[2][3]=0;
    table[2][4]=1,5;
    table[3][0]=1.5;
    table[3][1]=1;
    table[3][2]=2;
    table[3][3]=1;
    table[3][4]=0;
    table[4][0]=0;
    table[4][1]=1;
    table[4][2]=0.5;
    table[4][3]=2;
    table[4][4]=1;
    int jmla = user.nbEl();
    int arr[jmla];
    Element eluser = user.getElemen();
    eluser.getidxel(arr);
    int jmlb = enemy.nbEl();
    int arr2[jmlb];
    Element elenem = enemy.getElemen();
    elenem.getidxel(arr2);
    float maks = 0;
    for (int i = 0; i < jmla; i++)
    {
        for (int j = 0; j < jmlb; j++)
        {
            if(table[arr[i]][arr2[j]]>maks){
                maks = table[arr[i]][arr2[j]];
            }
        }
        
    }
    return maks;
}