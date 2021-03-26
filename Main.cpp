// File Main.cpp

#include <iostream>
#include <string>

// Include file BEWARE OF REPETITION
// Included so far : map, point, engimon, skill, element
#include "Map.hpp"
#include "Player.hpp"

using namespace std;

void printHelp() {
    cout << "--------------------------- AVAILABLE COMMAND ---------------------------" << endl;
    cout << "1. Move up                         9. Talk to Active Engimon"<< endl;
    cout << "2. Move left                       10. Show map" << endl;
    cout << "3. Move down                       11. Show owned skill item" << endl;
    cout << "4. Move right                      12. Use skill item to Active Engimon" << endl;
    cout << "5. Show owned Engimon              13. Breed Engimons" << endl;
    cout << "6. Show Active Engimon             14. Battle Wild Engimon" << endl;
    cout << "7. Check Active Engimon detail     15. Help" << endl;
    cout << "8. Change Active Engimon           16. Quit" << endl;
    cout << endl << "Please insert the number." << endl << endl;
}

void printGreetings() {
    cout << "Welcome to Engimon Factory!!!" << endl;
    cout << "Min spawned Engimon available : 3" << endl;
    cout << "Max spawned Engimon available : 8" << endl;
    cout << "Enter max spawned engimon? ";
}

void generateWildEngimon() {
    cout << endl << "Please wait a moment" << endl;
    cout << "Spawning wild engimon..." << endl << endl;
}

void haveAGreatTime() {
    cout << endl << "Spawning complete!" << endl;
    cout << "Good luck and have fun!" << endl << endl;
    cout << "Player starter pack:" << endl;
}

void checkMaxSpawnedEngimon(int max) {
    string error = "Invalid number, please restart the game.";
    if (max < 3 || max > 8) {
        throw error;
    }
}

void startAscii(){

cout << "    █▀▀▄░░░░░░░░░░░▄▀▀█ " << endl;
cout << "░█░░░▀▄░▄▄▄▄▄░▄▀░░░█          W i l l y  W a n g k y   &   t  h  e" << endl;
cout << "░░▀▄░░░▀░░░░░▀░░░▄▀                            .__ " << endl;                      
cout << "░░░░▌░▄▄░░░▄▄░▐▀▀          ____   ____    ____ |__| _____   ____   ____ " << endl; 
cout << "░░░▐░░█▄░░░▄█░░▌▄▄▀▀▀▀█  _/ __ \\ /    \\  / ___\\|  |/     \\ /  _ \\ /    \\ " << endl;
cout << "░░░▌▄▄▀▀░▄░▀▀▄▄▐░░░░░░█  \\  ___/|   |  \\/ /_/  >  |  Y Y  (  <_> )   |  \\" << endl;
cout << "▄▀▀▐▀▀░▄▄▄▄▄░▀▀▌▄▄▄░░░█   \\___  >___|  /\\___  /|__|__|_|  /\\____/|___|  /" << endl;
cout << "█░░░▀▄░█░░░█░▄▀░░░░█▀▀▀    _____     \\//_____/ __       \\/            \\/ " << endl;
cout << "░▀▄░░▀░░▀▀▀░░▀░░░▄█▀     _/ ____\\____    _____/  |_  ___________ ___.__. " << endl;
cout << "░░░█░░░░░░░░░░░▄▀▄░▀▄    \\   __\\__  \\ _/ ___\\   __\\/  _ \\_  __ <   |  | " << endl;
cout << "░░░█░░░░░░░░░▄▀█░░█░░█    |  |   / __ \\\\  \\___|  | (  <_> )  | \\/\\___  | " << endl;
cout << "░░░█░░░░░░░░░░░█▄█░░▄▀    |__|  (____  /\\___  >__|  \\____/|__|   / ____| " << endl;
cout << "░░░█░░░░░░░░░░░████▀                \\/     \\/                   \\/      " << endl;
cout << "░░░▀▄▄▀▀▄▄▀▀▄▄▄█▀                                  b y    a n g r y m o n" << endl;
}

int main() {
    // KAMUS
    string input;
    int intInput;
    int maxWildEngi;
    int enemyX, enemyY;
    string direction;

    // Read map and make player
    Map m = Map();
    Player *P = new Player();
    m.setMapCharaAt(0,0,'P');
    m.setMapCharaAt(1,0,'X');
    printGreetings();

    // Check player input
    try {
        cin >> input;
        intInput = stoi(input);
        maxWildEngi = intInput;
        checkMaxSpawnedEngimon(maxWildEngi);
    }
    catch(string errorMessage) {
        cout << errorMessage << endl;
        return 0;
    }

    // Generate wild engimon
    generateWildEngimon();
    for (int i = 0; i < intInput; i++) {
        m.spawnWildEngimon();
    }
    cout << endl;
    m.displayMap();
    startAscii();
    // Starter pack
    haveAGreatTime();
    P->displayInventorySkill();
    P->displayInventoryEngimon();
    cout << "Active Engimon: " << P->getActiveEngimon()->getName() << endl << endl;
    
    printHelp();

    // Time to play!
    while (intInput != 16) {
        // Spawning new engimon if there aren't enough
        while (m.getCountEngimon() < 3) {
            m.spawnWildEngimon();
        }
        cout << endl << "Insert command: ";
        cin >> input;
        intInput = stoi(input);
        Engimon* actEngi = P->getActiveEngimon();
        switch(intInput) {
            case 1:
                try {
                    m.getMove("w",'P');
                }
                catch (int zero) {
                    cout << "Invalid move!" << endl << endl;
                }
                m.randomizeWildEngimonMove();
                m.displayMap();
                break;
            case 2:
                try {
                    m.getMove("a",'P');
                }
                catch (int zero) {
                    cout << "Invalid move!" << endl << endl;
                }
                m.randomizeWildEngimonMove();
                m.displayMap();
                break;
            case 3:
                try {
                    m.getMove("s",'P');
                }
                catch (int zero) {
                    cout << "Invalid move!" << endl << endl;
                }
                m.randomizeWildEngimonMove();
                m.displayMap();
                break;
            case 4:
                try {
                    m.getMove("d",'P');
                }
                catch (int zero) {
                    cout << "Invalid move!" << endl << endl;
                }
                m.randomizeWildEngimonMove();
                m.displayMap();
                break;
            case 5:
                P->displayInventoryEngimon();
                break;
            case 6:
                cout << "Active Engimon: " << P->getActiveEngimon()->getName() << endl;
                break;
            case 7:
                actEngi->showData();
                break;
            case 8:
                cout << endl;
                P->changeActiveEngimon();
                break;
            case 9:
                actEngi->talk();
                break;
            case 10:
                m.displayMap();
                break;
            case 11:
                P->displayInventorySkill();
                break;
            case 12:
                int skillAt;
                P->displayInventorySkill();
                cout << "Select skill item: ";
                cin >> skillAt;
                P->learnSkill(P->getActiveEngimon(),P->getSkillAt(skillAt-1));
                break;
            case 13:
                int engi1;
                int engi2;
                cout << "Which engimon do you want to breed?" << endl;
                cout << "Parent 1: ";
                cin >> engi1;
                cout << "Parent 2: ";
                cin >> engi2;
                P->breeding(P->getEngimonAt(engi1-1),P->getEngimonAt(engi2-1));
                break;
            case 14:
                cout << "Which enemy do you want to fight?" << endl;
                cout << "Please enter w/a/s/d." << endl;
                cout << "Enemy? ";
                cin >> direction;
                if (direction == "w") {
                    enemyX = m.getPosition('P').getX();
                    enemyY = m.getPosition('P').getY() - 1;
                }
                if (direction == "a") {
                    enemyX = m.getPosition('P').getX() - 1;
                    enemyY = m.getPosition('P').getY();
                }
                if (direction == "s") {
                    enemyX = m.getPosition('P').getX();
                    enemyY = m.getPosition('P').getY() + 1;
                }
                if (direction == "d") {
                    enemyX = m.getPosition('P').getX() + 1;
                    enemyY = m.getPosition('P').getY();
                }
                if (P->battle(m.getMapWildEngiAt(enemyX,enemyY))) {
                    m.setMapWildEngiAt(enemyX,enemyY,NULL);
                    m.setMapCharaAt(enemyX,enemyY,' ');
                    m.decrementCountEngimon();
                }
                break;
            case 15:
                printHelp();
                break;
            case 16:
                cout << "Thank you for playing~" << endl;
                break;
            default:
                cout << "Please insert the appropriate number" << endl;
        }
    }
    return 0;
}