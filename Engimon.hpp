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
        void setName(string);
        int getLevel();
        //method overloading
        Engimon& operator=(const Engimon&);
        Engimon& operator<<(const Skill&);
        // method lainnya
        void levelUp();
        void addExp(int);
        void die(); // --------------------ini apakah iya?
        virtual void showData();
        virtual void talk()=0;
        virtual bool punyaElemen(string)=0;
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
