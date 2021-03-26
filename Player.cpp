#include "Player.hpp"
#include <string>

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
    C->setLevel(50);
    Pikamon *P = new Pikamon("Pikamon");
    P->setLevel(50);
    Rotomon *R = new Rotomon("Rotomon");
    R->setLevel(1);
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
    activeEngimon->talk();
    cout << "Now " << activeEngimon->getName() << " is the Active Engimon!" << endl;
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
            cout << E->getName() << " learned a new skill!" << endl;
        }
        //Cek apakah udh punya 4, kl penuh print "Engimon ini sudah memiliki 4 skill"
        //Kalo belum 4, skill engimon bertambah
    }
}


bool Player::battle(Engimon* musuh){

    Engimon* currentEngimon = getActiveEngimon();
    // find element advantage
    float myElmAdvantage = getAdvantage(currentEngimon,musuh);
    float enmElmAdvantage = getAdvantage(musuh,currentEngimon);

    int myPower = currentEngimon->getLevel() * myElmAdvantage +
                sumBasePowMastery(currentEngimon);

    int enemyPower = musuh->getLevel() * enmElmAdvantage +
                sumBasePowMastery(musuh);
    
    if(myPower>enemyPower){
        printAsciiMenang();
        cout << "Your Power  : " << myPower << "\nEnemy Power : " << enemyPower << endl;
        cout << endl;
        // active engimon menerima exp
        // asumsi besarannya 35
        currentEngimon->addExp(35);

        // mendapatkan engimon lawan
        addEngimonToInventory(musuh);
        
        // mendapatkan random skill kompatibel dengan elemen musuh
        addSkillToInventory(&musuh->getAbility()[0]);
        return true;

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
        return false;
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
    // cout << "\nbapak : " << advBapak << "\nemak : " << advEmak << "\n\n";

    Engimon* child1 = new Engimon();
    // construct engimon baru (mesti nentuin elmnya dulu)
    // kasus i : elemen kedua parent sama
    // spesies & elm anak dipilih dari parent A atau B (pilih parent A)
    if(bapak->getElemen().isSama(emak->getElemen())){
        // construct anak
        // cout << "case elemen sama" << endl;
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
        // cout << "\ncase elemen beda" << endl;
        // kasus ii & iii : elemen kedua parent berbeda maka 
        // anak akan memiliki elemen dan spesies dari 
        // elemen yang memiliki element advantage yang lebih tinggi.
        
        if(advBapak>advEmak){
            // cout << "bapak lebih gede dr emak woy" << endl;
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
                cout << "disini" << endl;
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
            
        } else if (advBapak<advEmak) { //bapak lebih kecil
            // cout << "emak lebih gede dr bapak woy" << endl;
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
            // construct anak yang beda dari parent
            // cout << "case adv sama" << endl;
            child1 = generateRandomChild(namaAnak,bapak->getName(),emak->getName());
            while(child1->getSpecies()==bapak->getSpecies() || child1->getSpecies()==emak->getSpecies()){
                child1 = generateRandomChild(namaAnak,bapak->getName(),emak->getName());
            }
        }
    }
    // cout << child1->getSpecies() << endl;

    return child1;
}

void Player::inheritSkill(Engimon* bapak, Engimon* emak, Engimon* anak){
    ///// INHERIT SKILL /////
    Skill* skillAnak = new Skill();

    // selama skill belum full
    while(!anak->isSkillFull()){
        // jika skill dimiliki kedua parent
        if(getSkillbyMastery(bapak,anak)->getnama()==getSkillbyMastery(emak,anak)->getnama()){
            if(getSkillbyMastery(bapak,anak)->getMasteryLevel() > 
            getSkillbyMastery(emak,anak)->getMasteryLevel()){
                anak->operator<<(*getSkillbyMastery(bapak,anak));
            } else if(getSkillbyMastery(bapak,anak)->getMasteryLevel() < 
            getSkillbyMastery(emak,anak)->getMasteryLevel()){
                anak->operator<<(*getSkillbyMastery(emak,anak));
            } else { // mastery level sama
                Skill* temp = new Skill();
                temp = getSkillbyMastery(bapak,anak);
                temp->incrementMasteryLevel();
                anak->operator<<(*temp);
            }
        } else{ // skill beda
            if(getSkillbyMastery(bapak,anak)->getMasteryLevel() >= 
            getSkillbyMastery(emak,anak)->getMasteryLevel()){
                anak->operator<<(*getSkillbyMastery(bapak,anak));
            } else{
                anak->operator<<(*getSkillbyMastery(emak,anak));
            }
        }
    }
}

void Player::breeding(Engimon* bapak, Engimon* emak) {
    // construct berdasarkan spesies
    if(bapak->getLevel() > 30 && emak->getLevel()>30){
        Engimon* anak = new Engimon();
        anak = breedingSpesies(bapak,emak);
        inheritSkill(bapak,emak,anak);
        addEngimonToInventory(anak);
        cout << "Congratulations!!! You get new " << anak->getSpecies() << endl;
        cout << anak->getName() << " added to inventory" << endl;
    }
    else
    {
        cout << "Level engimon kamu belum mencukupi";
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

Engimon* Player::generateRandomChild(string namaAnak, string namaBapak, string namaEmak){
    int random = rand() % 8 + 1; //angka 1 sampe 8
    Engimon* child1 = new Engimon();
    if(random==1){
        Charmamon *child = new Charmamon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==2){
        Squirtlmon *child = new Squirtlmon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==3){
        Pikamon *child = new Pikamon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==4){
        Rumblemon *child = new Rumblemon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==5){
        Snommon *child = new Snommon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==6){
        Rotomon *child = new Rotomon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==7){
        Sealmon *child = new Sealmon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    } else if(random==8){
        Gastromon *child = new Gastromon(namaAnak, namaBapak, namaEmak);
        child1 = child;
    }
    return child1;
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
    cout << "$$$$. `$' \\' \\$   $$$$$$$!          Y  O  U           !$$$$$$$  '$/ `/ `$' .$$$" << endl;
    cout << "$$$$$. !\\  i  i .$$$$$$$$          L  O  S  E         $$$$$$$$. i  i  /! .$$$$$" << endl;
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

void Player::printAsciiMenang(){
    cout << "        .--'''''''''--." << endl;
    cout << "     .'      .---.      '.   \\ \\ /\\ / / _ \\ \\ /\\ / /" << endl;
    cout << "    /    .-----------.    \\   \\ V  V / (_) \\ V  V /" << endl;
    cout << "   /        .-----.        \\  _\\_/__/______ \\__\\_/" << endl;
    cout << "   |       .-.   .-.       |  | | | |/ _ \\| | | |" << endl;
    cout << "   |      /   \\ /   \\       | | |_| | (_) | |_| |" << endl;
    cout << "    \\    | .-. | .-. |    /    \\__, |\\___/ \\__,_| " << endl;
    cout << "     '-._| | | | | | |_.-'      __/ |  (_)" << endl;
    cout << "         | '-' | '-' |        _____/  ___ _ __ " << endl;
    cout << "          \\___/ \\___/         \\ \\ /\\ / / | '_ \\" << endl;
    cout << "       _.-'  /   \\  `-._       \\ V  V /| | | | |" << endl;
    cout << "     .' _.--|     |--._ '.      \\_/\\_/ |_|_| |_|" << endl;
    cout << "     ' _...-|     |-..._ '" << endl;
    cout << "            |     |" << endl;
    cout << "            '.___.'" << endl;
}

Skill* Player::getSkillAt(int n) {
    return InventorySkill->getItemAtIdx(n).getItem();
}

Engimon* Player::getEngimonAt(int n) {
    return InventoryEngimon->getItemAtIdx(n).getItem();
}