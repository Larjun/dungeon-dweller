#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../classFiles/Attack.h"
#include "../classFiles/Player.h"
#include "../classFiles/Enemy.h"
#include "../classFiles/Inventory.h"
#include "../classFiles/Map.h"

using namespace std;

//---------------------NOTE TO GRADER---------------------
//This game is intended to be played with output.txt opened in the IDE for ease of navigation and information shown
//--------------------------------------------------------

int splitdriver(string instr, char delim, string arrName[], int l){ //split function from homework 4, exclusive to the driver
    int s = 0; //the number of splits counted
    string arrVal = ""; //the split points of instr
    
    if (instr.length() == 0){ //no. of splits is returned 0 is there is no string
        s = 0;
    }
    
    else { //if string exists
        
        instr = instr + delim; //a delim is added at the end to count all words
        
        for(int i = 0; i <= instr.length(); i++){
            if( instr[i] != delim){ //for every part of the string which is not delim, the array value is formed
                arrVal = arrVal + instr[i];
            }
              
            else if (arrVal != ""){ //if delim point is reached
                arrName[s] = arrVal; //the individual chars accumulated will form a string and will be added as and array value
                s++; //the next array value is selected for the for loop
                arrVal = ""; //arrVal is reset for the the for loop
            }
        }
    }
    
    return s; //the number of splits is returned
    
    //the array is not returned but can be called at will
}

int readEnemies(string enemyFile, Enemy enarr[6]){ //read and fills out the enemy array
    //opening file and testing if it is working
    ifstream myFile(enemyFile); //defining file variable and opening it
    
    if(!myFile.is_open()) { //if file is not open, return this value
        return 0;
    } else { //if file opens
        string line = "";
        int i = 0;

        while(getline(myFile, line) && i < 7) {
            string fileArr[8];
            splitdriver(line, ',', fileArr, 8);
            if (line != "") { //all enemy variables are defined
                enarr[i].setEnemyName(fileArr[0]);
                enarr[i].setEnemyhp(stoi(fileArr[1]));
                enarr[i].setDefense(stoi(fileArr[2]));
                enarr[i].setMagResistance(stoi(fileArr[3]));
                enarr[i].setAtkStrength(stoi(fileArr[4]));
                enarr[i].setPhysAtkChance(stoi(fileArr[5]));
                enarr[i].setMagAtkChance(stoi(fileArr[6]));
                enarr[i].setStandbyChance(stoi(fileArr[7]));
                i++;
            }
        }
        return 1;
    }
}

void mapMenu(int dungeonlevel) { //the menu when roaming around the map
    cout << "Select a numerical option, you are now roaming dungeon level " << dungeonlevel + 1 << endl;
    cout << "1. Move a step up" << endl;
    cout << "2. Move a step down" << endl;
    cout << "3. Move a step left" << endl;
    cout << "4. Move a step right" << endl;
    cout << "5. Use Item" << endl;
    cout << "6. Scan level for enemies" << endl;
    cout << "7. Move up a level" << endl;
    cout << "8. Move down a level" << endl;

}

void combatMenu(Player player, Enemy enemy[6], int enemyNum) { //the menu when in combat
    cout << player.getName() << "'s health: " << player.gethp() << " | Mana: " << player.getmp() << " | Armor: " << player.getap() << endl;
    cout << enemy[enemyNum].getEnemyName() << "'s health: " << enemy[enemyNum].getEnemyhp() << endl;
    cout << "==========< Chooe Your Move >==========" << endl;
    cout << "1. Slash" << endl;
    cout << "2. Pierce" << endl;
    cout << "3. Use Elemental Magic - 75mp" << endl;
    cout << "4. Use Pure Magic - 300mp" << endl;
    cout << "5. Rest" << endl;
    cout << "6. Use Item" << endl;    
}

void useItem(Inventory &invent, Player &player){ //the function to use an item
    // prompt to ask the player the item to use
    string itemOptStr;
    int itemOpt;
    cout << "Choose and item to use" << endl;
    cout << "1. Health Potion - " << invent.getHealthPotions() << endl;
    cout << "2. Mana Potion - " << invent.getManaPotions() << endl;
    cout << "3. Armor Scrap - " << invent.getMetals() << endl;
    getline(cin, itemOptStr); //the option will be input as a string
    if (itemOptStr != "") { // input is not empty
        itemOpt = stoi(itemOptStr); //the input string will be converted to integer for if statements
    }
    else {
        itemOpt = 0;
    }
    
    if(itemOpt == 1){ //health potion
        if(invent.getHealthPotions() > 0){ //if health potion count is more than 0
            player.restorehp();
            invent.addHealthPotions(-1);
            cout << "Your health has been restored." << endl;
        }else {
                cout << "You do not have enough health potions." << endl;
            }
                
    } else if(itemOpt == 2){ //mana potion
        if(invent.getManaPotions() > 0){ //if mana potion count is more than 0
            player.restoremp();
            invent.addManaPotions(-1);
            cout << "Your mana has been restored." << endl;
        }else {
            cout << "You do not have enough mana potions." << endl;
        }
    } else if(itemOpt == 3){ //armor scrap
        if(invent.getMetals() > 0){ //if player has metal
            player.restoreap();
            cout << "Your armor has been repaired." << endl;
            invent.addMetals(-1);
        }else {
            cout << "You do not have enough metal to repair armor." << endl;
        }
    }else {
        cout << "Invalid input." << endl;
    }
}

void pickup(int item, Inventory &invent){ // for picking up items
    if (item == 0){ //if health potion is picked up
        invent.addHealthPotions(1);
        cout << "You picked up a health potion ";
    } else if (item == 1){ //if mana potion is picked up
        invent.addManaPotions(1);
        cout << "You picked up a mana potion ";
    } else if (item == 2){ //if metal is picked up
        invent.addMetals(1);
        cout << "You picked up a scrap metal ";
    }
}

int combat (int enemyNum, Enemy enemy[6], Player &player, Inventory &invent){ //combat function when player is in combat
    srand(time(0)); //defining seed random
    string combatOptstr; //defining option input string
    int cmbtOpt; //defining option integer to be processed
    
    combatMenu(player, enemy, enemyNum);
    getline(cin, combatOptstr); //the option will be input as a string
    if (combatOptstr != "") { // input is not empty
        cmbtOpt = stoi(combatOptstr); //the input string will be converted to integer for if statement 
    }
    else {
        cmbtOpt = 0;
    }
    
    while (player.gethp() > 0 && enemy[enemyNum].getEnemyhp() > 0){ //if both players and enemy are alive
        
        while (cmbtOpt > 6 && cmbtOpt < 1){
            cout << "Invalid input, please re-enter move." << endl;
            combatMenu(player, enemy, enemyNum); 
            getline(cin, combatOptstr); //the option will be input as a string
            cmbtOpt = stoi(combatOptstr); //the input string will be converted to integer for if statement
        }

        if (cmbtOpt > 0 && cmbtOpt < 6) { //for inputs 1 to 5 are attacks
            int dmgDone = player.performAttack(cmbtOpt -1, enemy[enemyNum].getDefense(), enemy[enemyNum].getMagResistance());
            enemy[enemyNum].removehp(dmgDone);
        } else if (cmbtOpt == 6) { // for using items (option 6)
            useItem(invent, player);
        }

        if (enemy[enemyNum].getEnemyhp() > 0) { // if enemy is not dead, they can do their attack
            int eneMove = rand() % 10 + 1; //randomizing enemy move
            int dmgTaken; //define damage taken by player
            if (eneMove <= enemy[enemyNum].getPhysAtkChance()) { //if enemy does physical attack
                if (player.getap() > 0){ //if player has armor, damage taken is reduced
                    dmgTaken = enemy[enemyNum].getAtkStrength() * 0.65;
                    player.removeap();
                    player.newhp(dmgTaken);
                    cout << "The " << enemy[enemyNum].getEnemyName() << " did a physical attack and dealt " << dmgTaken << " damage and you lost a piece of armor." << endl;
                } else { 
                    dmgTaken = enemy[enemyNum].getAtkStrength() * 1.25;
                    player.newhp(dmgTaken);
                    cout << "The " << enemy[enemyNum].getEnemyName() << " did a physical attack and dealt " << dmgTaken << " damage." << endl;
                }

            } else if (eneMove <= enemy[enemyNum].getMagAtkChance()) { //if enemy does magic attack, player armor is not involved
                dmgTaken = enemy[enemyNum].getAtkStrength() * 1.75;
                    player.newhp(dmgTaken);
                    cout << "The " << enemy[enemyNum].getEnemyName() << " did a magic attack and dealt " << dmgTaken << " damage." << endl;

            } else { //if enemy rested
                cout << "The " << enemy[enemyNum].getEnemyName() << " rested and did no damage" << endl;
            }
            cout << endl;

            if (player.gethp() > 0){ //if player and enemy are not dead
                combatMenu(player, enemy, enemyNum);
                getline(cin, combatOptstr); //the option will be input as a string
                if (combatOptstr != "") { // input is not empty
                    cmbtOpt = stoi(combatOptstr); //the input string will be converted to integer for if statement 
                }
                else {
                    cmbtOpt = 0;
                }
            }
        }
    }
    
    if (enemy[enemyNum].getEnemyhp() <= 0) { //if enemy dies
        enemy[enemyNum].restorehp();
        return 1;
    } else if (player.gethp() <= 0) { //if player dies
        if(enemyNum != 5){ //if the player dies to an enemy who isn't a boss, the enemy's health will be restored as enemy position will be reset.
            enemy[enemyNum].restorehp();
        }
        return 0;
    }

    // in the combat function 1 is returned if player wins and 0 is returned if player dies
}

void printMap (int lvlNum, Map map, Player player, Inventory invent, int kills, int deaths){ //printing map as an output
    int score = ((200 * kills) + (75 * (invent.getHealthPotions() + invent.getManaPotions())) + (50 * invent.getMetals()) - (400 * deaths)); //computing player score
    if (score < 0) { //minimum score is 0
        score = 0;
    } 
    
    ofstream mapFile("../files/output.txt"); //creates a file called output.txt
    //adding basic stats to the output file
    mapFile << player.getName() << "'s health: " << player.gethp() << endl;
    mapFile << player.getName() << "'s mana: " << player.getmp() << endl;
    mapFile << player.getName() << "'s armor: " << player.getap() << endl;
    mapFile << "Number of keys collected: " << invent.getKeys() << endl;
    mapFile << "Kill Count: " << kills << endl;
    mapFile << "Score: " << score << endl;
    //printing out the map
    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 25; y++){
            if (map.getInfoAt(lvlNum, x, y) != "k") {
                mapFile << " " << map.getInfoAt(lvlNum, x, y);
            } else if (map.getInfoAt(lvlNum, x, y) == "k") {
                mapFile << " " << "i";
            }
        }
        mapFile << endl;
    }
    mapFile.close(); //closing the file after adding data
}

void victory (Player player, int kills, int deaths, Inventory invent){
    int score = ((200 * kills) + (75 * (invent.getHealthPotions() + invent.getManaPotions())) + (50 * invent.getMetals()) - (400 * deaths)); //computing player score
    if (score < 0) { //minimum score is 0
        score = 0;
    } 

    ofstream mapFile("../files/output.txt"); //creating/overwriting output file  
    mapFile << player.getName() << " escaped the dungeon with " << kills << " kills, " << deaths << " deaths, and a score of " << score << "." << endl << endl; //showing kills

    mapFile << "YYYYYYY       YYYYYYY                                     WWWWWWWW                           WWWWWWWW iiii" << endl;
    mapFile << "Y:::::Y       Y:::::Y                                     W::::::W                           W::::::W iiii"  << endl;                 
    mapFile << "Y:::::Y       Y:::::Y                                     W::::::W                           W::::::Wi::::i"  << endl;                
    mapFile << "Y::::::Y     Y::::::Y                                     W::::::W                           W::::::W" << endl;                       
    mapFile << "YYY:::::Y   Y:::::YYYooooooooooo   uuuuuu    uuuuuu        W:::::W           WWWWW           W:::::Wiiiiiiinnnn  nnnnnnnn"  << endl; 
    mapFile << "   Y:::::Y Y:::::Y oo:::::::::::oo u::::u    u::::u         W:::::W         W:::::W         W:::::W i:::::in:::nn::::::::nn"  << endl;
    mapFile << "    Y:::::Y:::::Y o:::::::::::::::ou::::u    u::::u          W:::::W       W:::::::W       W:::::W   i::::in::::::::::::::nn" << endl;
    mapFile << "     Y:::::::::Y  o:::::ooooo:::::ou::::u    u::::u           W:::::W     W:::::::::W     W:::::W    i::::inn:::::::::::::::n"<< endl;
    mapFile << "      Y:::::::Y   o::::o     o::::ou::::u    u::::u            W:::::W   W:::::W:::::W   W:::::W     i::::i  n:::::nnnn:::::n"<< endl;
    mapFile << "       Y:::::Y    o::::o     o::::ou::::u    u::::u             W:::::W W:::::W W:::::W W:::::W      i::::i  n::::n    n::::n"<< endl;
    mapFile << "       Y:::::Y    o::::o     o::::ou::::u    u::::u              W:::::W:::::W   W:::::W:::::W       i::::i  n::::n    n::::n"<< endl;
    mapFile << "       Y:::::Y    o::::o     o::::ou:::::uuuu:::::u               W:::::::::W     W:::::::::W        i::::i  n::::n    n::::n"<< endl;
    mapFile << "       Y:::::Y    o:::::ooooo:::::ou:::::::::::::::uu              W:::::::W       W:::::::W        i::::::i n::::n    n::::n"<< endl;
    mapFile << "    YYYY:::::YYYY o:::::::::::::::o u:::::::::::::::u               W:::::W         W:::::W         i::::::i n::::n    n::::n"<< endl;
    mapFile << "    Y:::::::::::Y  oo:::::::::::oo   uu::::::::uu:::u                W:::W           W:::W          i::::::i n::::n    n::::n"<< endl;
    mapFile << "    YYYYYYYYYYYYY    ooooooooooo       uuuuuuuu  uuuu                 WWW             WWW           iiiiiiii nnnnnn    nnnnnn"<< endl;

    mapFile << endl << "Thank you for playing my very first game and congratulations on completing it" << endl;
    mapFile << "--------------------------------- \\(^ w ^)/ ----------------------------------";
    mapFile.close(); //closing file
}
/*funtion to form the enemy list will be read and an array will be filled with enemy objects to be called at will. It will be read from a file*/

/*funtion to load the maps and write new ones to help move down level*/

int main(){
    // ----------------------- Initializing -----------------------
    int killcount = 0;
    int deathcount = 0;
    srand(time(0));

    //adding player name and creating player object
    string playerName;
    cout << "Enter Your Name: ";
    getline(cin, playerName);
    Player player = Player(playerName, 2000, 1000, 5);
    player.readAttack("../files/attacks.txt"); 

    //creating inventory object
    Inventory invent = Inventory();

    //creating enemy object and array and updating it with enemies.txt
    Enemy enemy[6];
    readEnemies("../files/enemies.txt", enemy);
    
    //creating map object and reading all map files
    Map map = Map();
    int lvl = 0;
    map.readMap(0, "../files/lvl1map.txt");
    map.readMap(1, "../files/lvl2map.txt");
    map.readMap(2, "../files/lvl3map.txt");
    map.readMap(3, "../files/lvl4map.txt");
    map.readMap(4, "../files/lvl5map.txt");
    map.resetPosition();

    // ----------------------- Menu Driver -----------------------
    printMap(lvl, map, player, invent, killcount, deathcount);
    string mapOptionstr; //defining option input string
    int mapOption; //defining option integer to be processed
    
    mapMenu(lvl);
    getline(cin, mapOptionstr); //the option will be input as a string
    if(mapOptionstr != "") { //if empty string is not empty
        mapOption = stoi(mapOptionstr); //the input string will be converted to integer for if statement
    }
    else {
        mapOption = 0;
    }

    while (invent.getKeys() != 5){ //while winning condition is not reached
        
        if(mapOption == 1) { //move up
            string infront = map.getInfoAt(lvl, map.getPositionX(lvl) - 1, map.getPositionY(lvl)); //scanning the tile the player wants to move to
            if (infront == "i"){ //if item is found, it is randomized and picked up and the user then moves up
                int item = rand() % 3;
                pickup(item, invent);
                map.moveUp(lvl);
                cout << "and you moved up." << endl;

            } else if (infront == "m"){ //if enemy is found
                int monster = rand() % 5; //monster is randomized and combat function is done
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){ //if player dies 
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){ //if player wins
                    map.moveUp(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved up" << endl;
                }

            } else if (infront == "d"){ //if boss is found, enemy is 5 instead of a random number
                int monster = 5;
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){
                    map.moveUp(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved up." << endl;
                }
            } else if (infront == "k"){ //if key is found
                invent.addKeys();
                cout << "Congratulations! You found a key, so you can move up a level." << endl;
                map.moveUp(lvl);
            } else {
                int move = map.moveUp(lvl);
                if(move == 0){
                    cout << "You cannot move, there is a wall infront of you." << endl;
                } else{
                    cout << "You moved up" << endl;
                }
            }
        } 
        else if(mapOption == 2) { //move down 
            string infront = map.getInfoAt(lvl, map.getPositionX(lvl) + 1, map.getPositionY(lvl)); //scanning the tile the player wants to move to
            if (infront == "i"){ //if item is found //if item is found, it is randomized and picked up and the user then moves up
                int item = rand() % 3;
                pickup(item, invent);
                map.moveDown(lvl);
                cout << "and you moved down." << endl;

            } else if (infront == "m"){ //if enemy is found
                int monster = rand() % 5;  //monster is randomized and combat function is done
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){ //if player dies
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){ //if player wins
                    map.moveDown(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved down" << endl;
                }

            } else if (infront == "d"){ //if boss is found, enemy is 5 instead of a random number
                int monster = 5;
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){
                    map.moveDown(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved down." << endl;
                }
            } else if (infront == "k"){ //if key is found
                invent.addKeys();
                map.moveDown(lvl);
                cout << "Congratulations! You found a key, so you can move up a level." << endl;
            } else {
                int move = map.moveDown(lvl);
                if(move == 0){
                    cout << "You cannot move, there is a wall infront of you." << endl;
                } else{
                    cout << "You moved down" << endl;
                }
            }
        } 
        else if(mapOption == 3) { //move left
            string infront = map.getInfoAt(lvl, map.getPositionX(lvl), map.getPositionY(lvl) + 1); //scanning the tile the player wants to move to
            if (infront == "i"){ //if item is found //if item is found, it is randomized and picked up and the user then moves up
                int item = rand() % 3; //monster is randomized and combat function is done
                pickup(item, invent);
                map.moveLeft(lvl);
                cout << "and you moved left." << endl;

            } else if (infront == "m"){ //if enemy is found
                int monster = rand() % 5;
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){ //if player dies 
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){ //if player wins
                    map.moveUp(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved left" << endl;
                }

            } else if (infront == "d"){ //if boss is found, enemy is 5 instead of a random number
                int monster = 5;
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){
                    map.moveLeft(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved left." << endl;
                }
            } else if (infront == "k"){ //if key is found
                invent.addKeys();
                map.moveLeft(lvl);
                cout << "Congratulations! You found a key, so you can move up a level." << endl;
            } else {
                int move = map.moveLeft(lvl);
                if(move == 0){
                    cout << "You cannot move, there is a wall infront of you." << endl;
                } else{
                    cout << "You moved left" << endl;
                }
            }
        } 
        else if(mapOption == 4) { //move right
            string infront = map.getInfoAt(lvl, map.getPositionX(lvl), map.getPositionY(lvl) + 1); //scanning the tile the player wants to move to
            if (infront == "i"){ //if item is found //if item is found, it is randomized and picked up and the user then moves up
                int item = rand() % 3; //monster is randomized and combat function is done
                pickup(item, invent);
                map.moveRight(lvl);
                cout << "and you moved right." << endl;

            } else if (infront == "m"){ //if enemy is found
                int monster = rand() % 5;
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){ //if player dies
                    deathcount++; 
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){ //if player wins
                    map.moveRight(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved right" << endl;
                }

            } else if (infront == "d"){ //if boss is found, enemy is 5 instead of a random number
                int monster = 5;
                cout << "You encountered a " << enemy[monster].getEnemyName() << "!" << endl; 
                int outcome = combat(monster, enemy, player, invent);
                if(outcome == 0){
                    deathcount++;
                    cout << "You died! You shall respawn at the start of the level" << endl;
                    map.setPosition(lvl);
                    player.restorehp();
                    player.restoremp();

                } else if (outcome == 1){
                    map.moveRight(lvl);
                    killcount++;
                    cout << "You defeated the " << enemy[monster].getEnemyName() << ", and you moved right." << endl;
                }
            } else if (infront == "k"){ //if key is found
                invent.addKeys();
                map.moveRight(lvl);
                cout << "Congratulations! You found a key, so you can move up a level." << endl;
            } else {
                int move = map.moveRight(lvl);
                if(move == 0){
                    cout << "You cannot move, there is a wall infront of you." << endl;
                } else{
                    cout << "You moved right" << endl;
                }
            }
        } 
        else if(mapOption == 5) { //use item
            useItem(invent, player);
        }
        else if(mapOption == 6) { //scan for enemies and items
            map.scan(lvl);
        }
        else if(mapOption == 7) { //move a level up
            if (lvl == 4){ //if the player is in level 5
                cout << "You are in the highest level of the dungeon." << endl;
            }
            else if(lvl == invent.getKeys()){ //if player does not have enough eys
                cout << "You do not have enough keys to go up a level." << endl;
            }else{ //if player has enough keys
                lvl++;
                cout << "You moved up a level." << endl;
                map.resetPosition();
            }
        }
        else if(mapOption == 8) { //move a level down
            if(lvl == 0){ //if player is in the lowest level
                cout << "You are in the lowest level." << endl;
            }else{
                lvl--;
                cout << "You moved down a level." << endl;
                map.resetPosition();
            }
        }
        else { //if invalid input
            cout << "Invalid input, re-enter your option." << endl;
        }

        //print map function is done again
        printMap(lvl, map, player, invent, killcount, deathcount);
        cout << endl;

        if(invent.getKeys() != 5) {
            mapMenu(lvl);
            getline(cin, mapOptionstr); //the option will be input as a string
            if(mapOptionstr != "") {
                mapOption = stoi(mapOptionstr); //the input string will be converted to integer for if statement
            }
            else {
                mapOption = 0;
            }
        }
    }

    if (invent.getKeys() == 5){ //if all keys are found, winning condition is met
        victory(player, killcount, deathcount, invent); //victory function is done
        cout << "You win!" << endl;
    }
}