#include "Player.hpp"

Player::Player() {
    //Set posisi awal
    //Pilih engimonactive, default pilih yang pertama kali ye
    InventorySkill.Inventory();
    InventoryEngimon.Inventory();

    //Inisialisasi skill

    //Inisialisasi engimon


    nbInventory = InventorySkill.getNbElmt() + InventoryEngimon.getNbElmt();
    MAX_CAP = 20; // Ini disetnya ngasal
}

void Player::keAtas() {
    if (getPosition().getY()-1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok atas!";
    } else { 
        setPosition(getPosition().getX(), getPosition().getY()-1);
    }
}

void Player::keBawah() {
    if (getPosition().getY()+1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok bawah!";
    } else {
        setPosition(getPosition().getX(), getPosition().getY()+1);
    }
}

void Player::keKanan() {
    if (getPosition().getX()+1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok kanan!";
    } else {
        setPosition(getPosition().getX()+1, getPosition().getY());
    }
}

void Player::keKiri() {
    if (getPosition().getX()-1 == 0) { //Pokoknya nabrak atas
        throw "Kamu menabrak tembok kiri!";
    } else {
        setPosition(getPosition().getX()-1, getPosition().getY());
    }
}

Point Player::getPosition() {return Position;}

Engimon Player::getActiveEngimon() {return activeEngimon;}

void Player::changeActiveEngimon(Engimon newActiveEngimon) {
    activeEngimon = newActiveEngimon;
}

void Player::interactActiveEngimon() {
    // cout << activeEngimon.getJargon() << endl; 
}

void Player::displayInventorySkill() {
    cout << "Skill yang ada di dalam inventory:\n";
    for (int i=0; i<InventorySkill.getNbElmt(); i++) {
        cout << InventorySkill.List[i].item.nama << " (" << InventorySkill.List[i].nbItem << ")\n";
    }
}

void Player::displayInventoryEngimon() {
    cout << "Engimon yang ada di dalam inventory:\n";
    for (int i=0; i<InventorySkill.getNbElmt(); i++) {
        cout << InventoryEngimon.List[i].item.nama << " (" << InventoryEngimon.List[i].nbItem << ")\n";
    }
}

void Player learnSkill(Engimon E, Skill S) {
    // Cek apakah skill engimon udah 4
    // Cek apakah elemen engimon tersebut ada di prereq learn skill tsb
    // Kalo ada, skill engimon tidak bertambah, ngasih pesan "kamu udah punya skill ini"
    // Kalo gak ada, skill engimon bertambah
}