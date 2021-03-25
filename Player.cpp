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
    if (getPosition()->getY()+1 == 12) { //Pokoknya nabrak atas
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
    if (getPosition()->getX()-1 == -1) { //Pokoknya nabrak kiri
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

void Player::learnSkill(Engimon *E, Skill *S) {
    // Cek apakah elemen engimon tersebut ada di prereq learn skill tsb
    // Kalo ada, skill engimon tidak bertambah, ngasih pesan "kamu udah punya skill ini"
    // Kalo gak ada, skill engimon bertambah
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

    Engimon* currentEngimon = getActiveEngimon();
    // find element advantage
    float myElmAdvantage = getAdvantage(currentEngimon,musuh);
    float enmElmAdvantage = getAdvantage(musuh,currentEngimon);

    int myPower = currentEngimon->getLevel() * myElmAdvantage +
                sumBasePowMastery(currentEngimon);

    int enemyPower = musuh->getLevel() * enmElmAdvantage +
                sumBasePowMastery(musuh);
    
    if(myPower>enemyPower){
        // print ascii win message
        cout << "menang" << endl;
        cout << "Your Power  : " << myPower << "\nEnemy Power : " << enemyPower << endl;
        cout << endl;
        // active engimon menerima exp
        // asumsi besarannya 35
        currentEngimon->addExp(35);
        
        // mendapatkan engimon lawan
        addEngimonToInventory(musuh);

        // mendapatkan random skill kompatibel dengan elemen musuh
        // mungkin dibikin generateRandomSkill based on engimon's element

    } else {
        // print ascii lose message
        printAsciiKalah();
        cout << "Your Power  : " << myPower << "\nEnemy Power : " << enemyPower << endl;
        cout << endl;
        // engimon akan mati
        currentEngimon->die();
        deleteEngimonFromInventory(currentEngimon);
        changeActiveEngimon();
        // player bs pilih command kek biasa
    }
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

Engimon* Player::breedingSpesies(Engimon* bapak, Engimon* emak){
    // kamus
    string typeBapak = typeid(bapak).name();
    string typeEmak = typeid(emak).name();
    
    string Char = "Charmamon";
    string Squirt = "Squirtlmon";
    string Pika = "Pikamon";
    string Rumble = "Rumblemon";
    string Sno = "Snommon";
    string Roto = "Rotomon";
    string Seal = "Sealmon";
    string Gastro = "Gastromon";

    // memberikan nama anak
    string namaAnak;
    cout << "Masukan nama buah hati dari " <<
        bapak->getName() << " dan " << emak->getName()
        << " : ";
    cin >> namaAnak;
    
    float advBapak = getAdvantage(bapak,emak);
    float advEmak = getAdvantage(emak,bapak);
    cout << "\nbapak : " << advBapak << "\nemak : " << advEmak << "\n\n";

    Engimon* child1 = new Engimon();
    // construct engimon baru (mesti nentuin elmnya dulu)
    // kasus i : elemen kedua parent sama
    // spesies & elm anak dipilih dari parent A atau B (pilih parent A)
    if(bapak->getElemen()==emak->getElemen()){
        // construct anak
        if (bapak->getSpecies()==Char){
            // tipe charmamon
            Charmamon *child = new Charmamon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
            //cout << child->getSpecies() << endl;
            //cout << child1->getSpecies() << endl << endl;
            //cout << "anaknye char" << endl;
            //delete child;
        } else if(bapak->getSpecies()==Squirt){
            // tipe squirtmon
            Squirtlmon *child = new Squirtlmon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        } else if(bapak->getSpecies()==Pika){
            // tipe pikamon
            Pikamon *child = new Pikamon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        } else if(bapak->getSpecies()==Rumble){
            // tipe rumblemon
            Rumblemon *child = new Rumblemon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        } else if(bapak->getSpecies()==Sno){
            // tipe snommon
            Snommon *child = new Snommon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        } else if(bapak->getSpecies()==Roto){
            // tipe rotomon
            Rotomon *child = new Rotomon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        } else if(bapak->getSpecies()==Seal){
            // tipe sealmon
            Sealmon *child = new Sealmon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        } else if(bapak->getSpecies()==Gastro){
            // tipe gastromon
            Gastromon *child = new Gastromon(namaAnak, bapak->getName(), emak->getName());
            child1 = child;
        }
    }
    else
    {
        // kasus ii & iii : elemen kedua parent berbeda maka 
        // anak akan memiliki elemen dan spesies dari 
        // elemen yang memiliki element advantage yang lebih tinggi.
        
        if(advBapak>advEmak){
            //diambil punya bapak
            // construct anak
            if (bapak->getSpecies()==Char){
                // tipe charmamon
                Charmamon *child = new Charmamon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
                //cout << child->getSpecies() << endl;
                //cout << child1->getSpecies() << endl << endl;
                //cout << "anaknye char" << endl;
                //delete child;
            } else if(bapak->getSpecies()==Squirt){
                // tipe squirtmon
                Squirtlmon *child = new Squirtlmon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(bapak->getSpecies()==Pika){
                // tipe pikamon
                Pikamon *child = new Pikamon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(bapak->getSpecies()==Rumble){
                // tipe rumblemon
                Rumblemon *child = new Rumblemon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(bapak->getSpecies()==Sno){
                // tipe snommon
                Snommon *child = new Snommon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(bapak->getSpecies()==Roto){
                // tipe rotomon
                Rotomon *child = new Rotomon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(bapak->getSpecies()==Seal){
                // tipe sealmon
                Sealmon *child = new Sealmon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(bapak->getSpecies()==Gastro){
                // tipe gastromon
                Gastromon *child = new Gastromon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            }
            
        } else if (advBapak < advEmak){
            //diambil punya emak
            // construct anak
            if (emak->getSpecies()==Char){
                // tipe charmamon
                Charmamon *child = new Charmamon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
                //cout << child->getSpecies() << endl;
                //cout << child1->getSpecies() << endl << endl;
                //cout << "anaknye char" << endl;
                //delete child;
            } else if(emak->getSpecies()==Squirt){
                // tipe squirtmon
                Squirtlmon *child = new Squirtlmon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(emak->getSpecies()==Pika){
                // tipe pikamon
                Pikamon *child = new Pikamon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(emak->getSpecies()==Rumble){
                // tipe rumblemon
                Rumblemon *child = new Rumblemon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(emak->getSpecies()==Sno){
                // tipe snommon
                Snommon *child = new Snommon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(emak->getSpecies()==Roto){
                // tipe rotomon
                Rotomon *child = new Rotomon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(emak->getSpecies()==Seal){
                // tipe sealmon
                Sealmon *child = new Sealmon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            } else if(emak->getSpecies()==Gastro){
                // tipe gastromon
                Gastromon *child = new Gastromon(namaAnak, bapak->getName(), emak->getName());
                child1 = child;
            }
        } else {
            // adv nya sama
            // construct anak
            if (typeBapak.find(Char) != std::string::npos &&
            typeEmak.find(Char) != std::string::npos){
                // tipe charmamon
                Charmamon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Squirt) != std::string::npos &&
            typeEmak.find(Squirt) != std::string::npos){
                // tipe squirtmon
                Squirtlmon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Pika) != std::string::npos &&
            typeEmak.find(Pika) != std::string::npos){
                // tipe pikamon
                Pikamon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Rumble) != std::string::npos &&
            typeEmak.find(Rumble) != std::string::npos){
                // tipe rumblemon
                Rumblemon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Sno) != std::string::npos &&
            typeEmak.find(Sno) != std::string::npos){
                // tipe snommon
                Snommon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Roto) != std::string::npos && 
            typeEmak.find(Roto) != std::string::npos){
                // tipe rotomon
                Rotomon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Seal) != std::string::npos &&
            typeEmak.find(Seal) != std::string::npos){
                // tipe sealmon
                Sealmon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            } else if(typeBapak.find(Gastro) != std::string::npos &&
            typeEmak.find(Gastro) != std::string::npos){
                // tipe gastromon
                Gastromon child(namaAnak, bapak->getName(), emak->getName());
                *child1 = child;
            }
        }
    }
    cout << child1->getSpecies() << endl;

    return child1;
}

void Player::inheritSkill(Engimon* bapak, Engimon* emak, Engimon* anak){
    ///// INHERIT SKILL /////
    Skill* skillAnak = new Skill();

    // selama skill belum full
    while(!anak->isSkillFull()){
        // jika skill sama
        if(getSkillbyMastery(bapak,anak)==getSkillbyMastery(emak,anak)){
            if(getSkillbyMastery(bapak,anak)->getMasteryLevel() > 
            getSkillbyMastery(emak,anak)->getMasteryLevel()){
                learnSkill(anak, getSkillbyMastery(bapak,anak));
            } else if(getSkillbyMastery(bapak,anak)->getMasteryLevel() < 
            getSkillbyMastery(emak,anak)->getMasteryLevel()){
                learnSkill(anak, getSkillbyMastery(emak,anak));
            } else { // mastery leve; sama
                Skill* temp = new Skill();
                temp = getSkillbyMastery(bapak,anak);
                temp->incrementMasteryLevel();
                learnSkill(anak, temp);
            }
        } else{ // skill beda
            if(getSkillbyMastery(bapak,anak)->getMasteryLevel() >= 
            getSkillbyMastery(emak,anak)->getMasteryLevel()){
                learnSkill(anak, getSkillbyMastery(bapak,anak));
            } else{
                learnSkill(anak, getSkillbyMastery(emak,anak));
            }
        }
    }
}

void Player::breeding(Engimon* bapak, Engimon* emak) {
    // construct berdasarkan spesies
    if(bapak->getLevel() >= 30 && emak->getLevel()>=30){
        Engimon* anak = new Engimon();
        anak = breedingSpesies(bapak,emak);
        inheritSkill(bapak,emak,anak);
        addEngimonToInventory(anak);
    }
}

Skill* Player::getSkillbyMastery(Engimon* E, Engimon* anak){
    Skill* skillAnak = new Skill();
    int max = 0;
    for(int i=0 ; i<4 ; i++){
        // cari skill dengan mastery level tertinggi
        int mastery = E->getAbility()[i].getMasteryLevel();
        if(!anak->punyaSkill(E->getAbility()[i]) && max < mastery){
            max = mastery;
            *skillAnak = E->getAbility()[i];
        }
    }
    return skillAnak;
}

float Player::getAdvantage(Engimon* user,Engimon* enemy){
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
    int jmla = user->nbEl();
    int arr[jmla];
    Element eluser = user->getElemen();
    eluser.getidxel(arr);
    int jmlb = enemy->nbEl();
    int arr2[jmlb];
    Element elenem = enemy->getElemen();
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

void Player::printAsciiKalah(){
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$'                 `$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$'                     `$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$$$'`$$$$$$$$$$$$$'`$$$$$$!                         !$$$$$$'`$$$$$$$$$$$$$'`$$$" << endl;
    cout << "$$$$  $$$$$$$$$$$  $$$$$$$                           $$$$$$$  $$$$$$$$$$$  $$$$" << endl;
    cout << "$$$$. `$' t' b$   $$$$$$$!         Y  O  U            !$$$$$$$  '$/ `/ `$' .$$$" << endl;
    cout << "$$$$$. !b  i  i .$$$$$$$$         L  O  S  E          $$$$$$$$. i  i  /! .$$$$$" << endl;
    cout << "$$$$$$   `--`--.$$$$$$$$$                             $$$$$$$$$.--'--'   $$$$$$" << endl;
    cout << "$$$$$$L        `$$$$$^^$$                             $$^^$$$$$'        J$$$$$$" << endl;
    cout << "$$$$$$$.   .'   ""~   $$$$$     $.                 .$   $$$   ~""   `.   .$$$$$$$$$" << endl;
    cout << "$$$$$$$$.  ;      .e$$$$$!     $$.             .$$   !$$$$$e,      ;  .$$$$$$$$" << endl;
    cout << "$$$$$$$$$   `.$$$$$$$$$$$$      $$$.         .$$$    $$$$$$$$$$$$.'   $$$$$$$$$" << endl;
    cout << "$$$$$$$$    .$$$$$$$$$$$$$!      $$`$$$$$$$$'$$     !$$$$$$$$$$$$$.    $$$$$$$$" << endl;
    cout << "$JT&yd$     $$$$$$$$$$$$$$$$.     $    $$    $    .$$$$$$$$$$$$$$$$     $by&TL$" << endl;
    cout << "                                  $    $$    $" << endl;
    cout << "                                  $.   $$   .$" << endl;
    cout << "                                  `$        $'" << endl;
    cout << "                                   `$$$$$$$$'" << endl;
    //cout << endl;
}
