#include "Player.hpp"

Player::Player() {
    //Set posisi awal
    Position = new Point();
    InventorySkill = new Inventory<Skill*>();
    InventoryEngimon = new Inventory<Engimon*>();

    //Inisialisasi inventory skill
    string *arr = new string[1];
    arr[0] = "Water";
    Skill *S1 = new Skill("Skill1",20,4,1,arr);
    InventoryItem<Skill*> *IS = new InventoryItem<Skill*>(S1, 1);
    InventorySkill->addItem(IS);

    //Inisialisasi engimon
    Charmamon *C = new Charmamon();
    InventoryItem<Engimon*> *CI = new InventoryItem<Engimon*>(C, 1);
    Pikamon *P = new Pikamon();
    InventoryItem<Engimon*> *PI = new InventoryItem<Engimon*>(P, 1);
    Rotomon *R = new Rotomon();
    InventoryItem<Engimon*> *RI = new InventoryItem<Engimon*>(R, 1);
    InventoryEngimon->addItem(CI);
    InventoryEngimon->addItem(PI);
    InventoryEngimon->addItem(RI);

    //Pilih activeEngimon pertama
    activeEngimon = InventoryEngimon->getItemAtIdx(0)->getItem();

    nbInventory = InventorySkill->getNbElmt() + InventoryEngimon->getNbElmt();
    MAX_CAP = 20; // Ini disetnya ngasal
}

void Player::keAtas() {
    if (getPosition()->getY()-1 == 0) { //Pokoknya nabrak atas
        cout << "Kamu menabrak tembok atas!";
    } else { 
        setPosition(getPosition()->getX(), getPosition()->getY()-1);
    }
}

void Player::keBawah() {
    if (getPosition()->getY()+1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok bawah!";
    } else {
        setPosition(getPosition()->getX(), getPosition()->getY()+1);
    }
}

void Player::keKanan() {
    if (getPosition()->getX()+1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok kanan!";
    } else {
        setPosition(getPosition()->getX()+1, getPosition()->getY());
    }
}

void Player::keKiri() {
    if (getPosition()->getX()-1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok kiri!";
    } else {
        setPosition(getPosition()->getX()-1, getPosition()->getY());
    }
}

Point* Player::getPosition() {return Position;}

Engimon* Player::getActiveEngimon() {return activeEngimon;}

void Player::changeActiveEngimon(Engimon* newActiveEngimon) {
    activeEngimon = newActiveEngimon;
}

void Player::interactActiveEngimon() {
    // cout << activeEngimon.getJargon() << endl; 
}

void Player::displayInventorySkill() {
    cout << "Skill yang ada di dalam inventory:\n";
    for (int i=0; i<InventorySkill->getNbElmt(); i++) {
        cout << InventorySkill->getItemAtIdx(i)->getItem()->getnama() << " (" << InventorySkill->getItemAtIdx(i)->getItem()->getnama() << ")\n";
    }
}

void Player::displayInventoryEngimon() {
    cout << "Engimon yang ada di dalam inventory:\n";
    for (int i=0; i<InventoryEngimon->getNbElmt(); i++) {
        cout << InventoryEngimon->getItemAtIdx(i)->getItem()->getName() << " (" << InventoryEngimon->getItemAtIdx(i)->getItem()->getName() << ")\n";
    }
}

void Player::learnSkill(Engimon *E, Skill S) {
    // Cek apakah skill engimon udah 4
    // Cek apakah elemen engimon tersebut ada di prereq learn skill tsb
    // Kalo ada, skill engimon tidak bertambah, ngasih pesan "kamu udah punya skill ini"
    // Kalo gak ada, skill engimon bertambah
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
    // int myElmAdvantage = ...
    // int enmElmAdvantage = ...

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
        InventoryEngimon.addEngimon(musuh);

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
    /*
    // iterate through all engimon's skill (butuh skill)
    for(int i=0; i<4;i++){ // max elm 4
        sum = sum + E.getSkill()[i].getNilaiNumerik() * 
        E.getSkill()[i].getMasteryLevel();
    }*/
    return sum;
}

void Player::breeding(Engimon& bapak, Engimon& emak){
    // cek level bapak emak
    bool cukupumur = false;
    if(bapak.getLevel() >= 30 && emak.getLevel()>=30){
        cukupumur = true;
    }

    if(cukupumur){ // sudah boleh kawin
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
        // bikin method buat nentuin elemen anak
        // Engimon* anak = new Engimon(namaAnak, bapak.getName(), emak.getName());

        // inherit skill
    }
}

void Player::decideChildElm(Engimon& bapak, Engimon& emak){

}