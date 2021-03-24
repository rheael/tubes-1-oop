#include "Player.hpp"

Player::Player() {
    //Inisialisasi awal
    MAX_CAP = 10; // Ini disetnya ngasal
    Position = new Point();
    InventorySkill = new Inventory<Skill*>();
    InventoryEngimon = new Inventory<Engimon*>();

    //Inisialisasi inventory skill
    string *prereqElmt = new string[1];
    prereqElmt[0] = "Ground";
    Skill *S1 = new Skill("Skill1",20,4,1,prereqElmt);
    addSkillToInventory(S1);

    //Inisialisasi inventory engimon
    Charmamon *C = new Charmamon("Charmamon");
    Pikamon *P = new Pikamon("Pikamon");
    Rotomon *R = new Rotomon("Rotomon");
    addEngimonToInventory(C);
    addEngimonToInventory(P);
    addEngimonToInventory(R);
    addEngimonToInventory(R);
    deleteEngimonFromInventory(R);

    //Pilih activeEngimon pertama
    activeEngimon = InventoryEngimon->getItemAtIdx(0).getItem(); // Kalo inisialisasi, pilih pertama aja

    nbInventory = InventorySkill->getNbElmt() + InventoryEngimon->getNbElmt();
}

void Player::keAtas() {
    if (getPosition()->getY()-1 == -1) { //Pokoknya nabrak atas
        cout << "Kamu menabrak tembok atas!";
    } else { 
        setPosition(getPosition()->getX(), getPosition()->getY()-1);
    }
}

void Player::keBawah() {
    if (getPosition()->getY()+1 == 12) { //Pokoknya nabrak bawah
        throw "Kamu menabrak tembok bawah!";
    } else {
        setPosition(getPosition()->getX(), getPosition()->getY()+1);
    }
}

void Player::keKanan() {
    if (getPosition()->getX()+1 == 9) { //Pokoknya nabrak kanan
        throw "Kamu menabrak tembok kanan!";
    } else {
        setPosition(getPosition()->getX()+1, getPosition()->getY());
    }
}

void Player::keKiri() {
    if (getPosition()->getX()-1 == -1) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok kiri!";
    } else {
        setPosition(getPosition()->getX()-1, getPosition()->getY());
    }
}

Point* Player::getPosition() {return Position;}

void Player::setPosition(int X, int Y) {
    Position->setX(X);
    Position->setY(Y);
}

Engimon* Player::getActiveEngimon() {return activeEngimon;}

void Player::changeActiveEngimon() {
    int idx;
    displayInventoryEngimon();
    cout << "Pilih nomor engimon yang ingin diaktifkan: ";
    cin >> idx;
    activeEngimon = InventoryEngimon->getItemAtIdx(idx-1).getItem();
}

void Player::interactActiveEngimon() {
    activeEngimon->talk();
}

void Player::addSkillToInventory(Skill* S) {
    if (nbInventory == MAX_CAP) {
        cout << "Inventory Anda sudah penuh!\n";
    } else {
        InventorySkill->addItem(S);
        nbInventory++;
    }
}

void Player::addEngimonToInventory(Engimon* E) {
    if (nbInventory == MAX_CAP) {
        cout << "Inventory Anda sudah penuh!\n";
    } else {
        InventoryEngimon->addItem(E);
        nbInventory++;
    }
}

void Player::deleteSkillFromIventory(Skill* S) {
    InventorySkill->deleteItem(S);
}

void Player::deleteEngimonFromInventory(Engimon* E) {
    InventoryEngimon->deleteItem(E);
}

void Player::displayInventorySkill() {
    cout << "Skill yang ada di dalam inventory:\n";
    for (int i=0; i<InventorySkill->getNbElmt(); i++) {
        cout << (i+1) << ". " << InventorySkill->getItemAtIdx(i).getItem()->getnama() << " (" << InventorySkill->getItemAtIdx(i).getNbItem() << ")\n";
    }
}

void Player::displayInventoryEngimon() {
    cout << "Engimon yang ada di dalam inventory:\n";
    for (int i=0; i<InventoryEngimon->getNbElmt(); i++) {
        cout << (i+1) << ". " << InventoryEngimon->getItemAtIdx(i).getItem()->getName() << " (" << InventoryEngimon->getItemAtIdx(i).getNbItem() << ")\n";
    }
}

void Player::learnSkill(Engimon *E) {
    displayInventorySkill();
    cout << E->getName() << " mau learn skill berapa nih? ";
    int idx;
    cin >> idx;

    // Cek apakah elemen engimon tersebut ada di prereq learn skill tsb
    // Kalo ada, skill engimon tidak bertambah, ngasih pesan "kamu udah punya skill ini"
    // Kalo gak ada, skill engimon bertambah
    Skill* S = InventorySkill->getItemAtIdx(idx-1).getItem();
    Skill* tempS;
    Skill valueS;
    tempS = S;
    valueS = *tempS;
    if (E->punyaSkill(valueS)) {
        cout << E->getName() << " sudah memiliki skill " << S->getnama() << endl;
    } else {
        //Cek apakah prereq elemennya sesuai dengan engimon, kl ga sesuai print "Gasesuai"
        bool found = false;
        for (int i=0; i<E->getElemen().getjmlel(); i++) {
            for (int j=0; j<S->getelemen().getjmlel(); j++) {
                if (E->getElemen().getNameAtIdx(i) == S->getelemen().getNameAtIdx(j)) {
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << E->getName() << " tidak bisa mempelajari skill " << S->getnama() << endl;
        } else {
            E->addNewSkill(valueS);
            deleteSkillFromIventory(S);
        }
        //Cek apakah udh punya 4, kl penuh print "Engimon ini sudah memiliki 4 skill"
        //Kalo belum 4, skill engimon bertambah
    }
}


void Player::battle(Engimon* musuh){
    // Bandingkan power musuh dan power engimon player
            
    // POWER :
    // level * element advantage
    // SUM(every skill's base power * Mastery level)
    // -------------------------- +

   // level = atribut level dari kelas engimon
   // element advantage = matriks dari kelas elemen
   // skill's base power = atribut dari kelas skill
   // mastery level = atribut dari kelas skill

   // mungkin bikin fungsi sum(base power * mastery lv)
   // print ascii keterangan menang/kalah

    Engimon* currentEngimon = getActiveEngimon();
    // find element advantage
    float myElmAdvantage = GetAdv(currentEngimon,musuh);
    float enmElmAdvantage = GetAdv(musuh,currentEngimon);

    int myPower = currentEngimon->getLevel() * myElmAdvantage +
                sumBasePowMastery(currentEngimon);

    int enemyPower = musuh->getLevel() * enmElmAdvantage +
                sumBasePowMastery(musuh);

    if(myPower>enemyPower){
        // print ascii win message

        // active engimon menerima exp
        // asumsi besarannya 35
        currentEngimon->addExp(35);
        
        // mendapatkan engimon lawan
        InventoryEngimon->addItem(musuh);

        // mendapatkan random skill kompatibel dengan elemen musuh
        // mungkin dibikin generateRandomSkill based on engimon's element

    } else if (myPower==enemyPower){
        // print ascii draw message
        // klo seri ngapain ya?

    } else{
        // print ascii lose message
        
        // engimon akan mati
        currentEngimon->die();

        // player bs pilih command kek biasa
    }

    // BELUM NANGANIN KASUS MULTIPLE ELEMENT ENGIMON
    // mungkin nanti dibikin method getAdvMultipleElmEngimon();
    // ato jadiin method overloading buat engimon dgn multiple elm

}

int Player::sumBasePowMastery(Engimon* E){
    int sum = 0;
    // iterate through all engimon's skill (butuh skill)
    for(int i=0; i<4;i++){ // max elm 4
        sum = sum + E->getSkill()[i].countSkillPower() * 
        E->getSkill()[i].countSkillPower();
    }
    return sum;
}

Engimon& Player::breedingSpesies(Engimon& bapak, Engimon& emak){
    // kamus
    string typeBapak = typeid(Engimon).name();
    string typeEmak = typeid(Engimon).name();
    
    string Char = "Charmamon";
    string Squirt = "Squirtlmon";
    string Pika = "Pikamon";
    string Rumble = "Rumblemon";
    string Sno = "Snomon";
    string Roto = "Roto";
    string Seal = "Sealmon";
    string Gastro = "Gastromon";
    
    // cek level bapak emak
    bool cukupumur = false;
    if(bapak.getLevel() >= 30 && emak.getLevel()>=30){
        cukupumur = true;
    }

    if(cukupumur){
        // level parent berkurang 30
        // mungkin nanti di kelas engimon bisa dibikin method level down
        bapak.levelDown(30);
        emak.levelDown(30);

        // memberikan nama anak
        string namaAnak;
        cout << "Masukan nama buah hati dari" <<
            bapak.getName() << "dan" << emak.getName()
            << " : ";
        cin >> namaAnak;

        // construct engimon baru (mesti nentuin elmnya dulu)
        // kasus i : elemen kedua parent sama
        // spesies & elm anak dipilih dari parent A atau B (pilih parent A)
        if(bapak.getElemen()==emak.getElemen()){
            // construct anak
            if (typeBapak.find(Char) != std::string::npos){
                // tipe charmamon
                Charmamon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Squirt) != std::string::npos){
                // tipe squirtmon
                Squirtlmon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Pika) != std::string::npos){
                // tipe pikamon
                Pikamon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Rumble) != std::string::npos){
                // tipe rumblemon
                Rumblemon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Sno) != std::string::npos){
                // tipe snommon
                Snommon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Roto) != std::string::npos){
                // tipe rotomon
                Rotomon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Seal) != std::string::npos){
                // tipe sealmon
                Sealmon child(namaAnak, bapak.getName(), emak.getName());
            } else if(typeBapak.find(Gastro) != std::string::npos){
                // tipe gastromon
                Gastromon child(namaAnak, bapak.getName(), emak.getName());
            }
        }
        // kasus ii & iii : elemen kedua parent berbeda maka 
        // anak akan memiliki elemen dan spesies dari 
        // elemen yang memiliki element advantage yang lebih tinggi.
        else
        {
            float advBapak = GetAdv(bapak,emak);
            float advEmak = GetAdv(emak,bapak);
            if(advBapak>advEmak){
                //diambil punya bapak
                // construct anak
                if (typeBapak.find(Char) != std::string::npos){
                    // tipe charmamon
                    Charmamon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Squirt) != std::string::npos){
                    // tipe squirtmon
                    Squirtlmon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Pika) != std::string::npos){
                    // tipe pikamon
                    Pikamon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Rumble) != std::string::npos){
                    // tipe rumblemon
                    Rumblemon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Sno) != std::string::npos){
                    // tipe snommon
                    Snommon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Roto) != std::string::npos){
                    // tipe rotomon
                    Rotomon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Seal) != std::string::npos){
                    // tipe sealmon
                    Sealmon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Gastro) != std::string::npos){
                    // tipe gastromon
                    Gastromon child(namaAnak, bapak.getName(), emak.getName());
                }
            } else if (advBapak < advEmak){
                // construct anak
                if (typeEmak.find(Char) != std::string::npos){
                    // tipe charmamon
                    Charmamon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Squirt) != std::string::npos){
                    // tipe squirtmon
                    Squirtlmon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Pika) != std::string::npos){
                    // tipe pikamon
                    Pikamon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Rumble) != std::string::npos){
                    // tipe rumblemon
                    Rumblemon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Sno) != std::string::npos){
                    // tipe snommon
                    Snommon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Roto) != std::string::npos){
                    // tipe rotomon
                    Rotomon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Seal) != std::string::npos){
                    // tipe sealmon
                    Sealmon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeEmak.find(Gastro) != std::string::npos){
                    // tipe gastromon
                    Gastromon child(namaAnak, bapak.getName(), emak.getName());
                }
            } else {
                // adv nya sama
                // construct anak
                if (typeBapak.find(Char) != std::string::npos &&
                typeEmak.find(Char) != std::string::npos){
                    // tipe charmamon
                    Charmamon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Squirt) != std::string::npos &&
                typeEmak.find(Squirt) != std::string::npos){
                    // tipe squirtmon
                    Squirtlmon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Pika) != std::string::npos &&
                typeEmak.find(Pika) != std::string::npos){
                    // tipe pikamon
                    Pikamon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Rumble) != std::string::npos &&
                typeEmak.find(Rumble) != std::string::npos){
                    // tipe rumblemon
                    Rumblemon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Sno) != std::string::npos &&
                typeEmak.find(Sno) != std::string::npos){
                    // tipe snommon
                    Snommon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Roto) != std::string::npos && 
                typeEmak.find(Roto) != std::string::npos){
                    // tipe rotomon
                    Rotomon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Seal) != std::string::npos &&
                typeEmak.find(Seal) != std::string::npos){
                    // tipe sealmon
                    Sealmon child(namaAnak, bapak.getName(), emak.getName());
                } else if(typeBapak.find(Gastro) != std::string::npos &&
                typeEmak.find(Gastro) != std::string::npos){
                    // tipe gastromon
                    Gastromon child(namaAnak, bapak.getName(), emak.getName());
                }
            }
        }
        
        ///// INHERIT SKILL /////
        for(int i=0 ; i<4 ; i++){
            if(bapak.getSkill()==emak.getSkill()){
                if(bapak.getSkill()->getMasteryLevel()==emak.getSkill()->getMasteryLevel()){
                    // maka skill yang di-inherit memiliki
                    // mastery level bernilai mastery level parent A + 1

                }
            }
        }
    }
}

Element Player::decideChildElm(Engimon& bapak, Engimon& emak){
    // udah work cara kek gini
    string typeBapak = typeid(Engimon).name();
    string typeEmak = typeid(Engimon).name();

    // kasus i : elemen kedua parent sama
    // spesies anak dipilih dari parent A atau B (pilih parent A)
    if(bapak.getElemen()==emak.getElemen()){
        return bapak.getElemen();
    }
    // kasus ii : elemen kedua parent berbeda maka 
    // anak akan memiliki elemen dan spesies dari 
    // elemen yang memiliki element advantage yang lebih tinggi.
    else
    {
        float advBapak = GetAdv(bapak,emak);
        float advEmak = GetAdv(emak,bapak);
        if(advBapak>advEmak){
            //diambil punya bapak

        }
    }
}