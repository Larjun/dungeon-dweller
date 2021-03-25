#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Attack.h"

using namespace std;

int splitPlayer(string instr, char delim, string arrName[], int l){ //split function from homework 4
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

string multiplydmg (int multiplyer){ //string returns for each damage multiple
    if (multiplyer == 1){
        return "an ineffective.";
    } else if (multiplyer == 2){
        return "an okay hit.";
    } else if (multiplyer == 3){
        return "a critical hit!";
    }
}

//Constructor
Player::Player(){
    plname = "";
    hp = 0;
    mp = 0;
    ap = 0;
}
Player::Player(string newName, int newHealth, int newMana, int newArmor){
    plname = newName;
    hp = newHealth;
    mp = newMana;
    ap = newArmor;
}

//Player name
string Player::getName(){
    return plname;
}     

void Player::setName(string newName){
    plname = newName;
}


//Health functions
int Player::gethp(){
    return hp;
}
void Player::newhp(int dmgTaken){
    hp = hp - dmgTaken;
}
void Player::restorehp(){
    hp = 2000;
}

//Mana functions
int Player::getmp(){
    return mp;
}
void Player::newmp(int manaUsed){
    mp = mp - manaUsed;
}
void Player::restoremp(){
    mp = 1000;
}

//Armor functions
int Player::getap(){
    return ap;
}
void Player::removeap(){
    ap = ap - 1;
}
void Player::restoreap(){
    ap = 5;
}

//Attack functions
int Player::readAttack(string attackFile){
    //opening file and testing if it is working
    ifstream myFile(attackFile); //defining file variable and opening it
    
    if(!myFile.is_open()) { //if file is not open, return this value
        return 0;
    } else { //if file opens
        string line = "";
        int i = 0;

        while(getline(myFile, line)) {
            string fileArr[5];
            splitPlayer(line, ',', fileArr, 5);
            if (line != "") { //sets each array string as the required data
                attacks[i].setAtkName(fileArr[0]);
                attacks[i].setBaseDmg(stoi(fileArr[1]));
                attacks[i].setAtkType(fileArr[2]);
                attacks[i].setDmgRed(stod(fileArr[3]));
                attacks[i].setManaCost(stoi(fileArr[4]));
                i++;
            }
        }
        return 1;
    }
}

void Player::showAttack(){ //shows attacks from attack array
    cout << "----- Choose your move -----" << endl;
    cout << "1. " << attacks[0].getAtkName() << ": " << attacks[0].getManaCost() << "mp." << endl;
    cout << "2. " << attacks[1].getAtkName() << ": " << attacks[1].getManaCost() << "mp." << endl; 
    cout << "3. " << attacks[2].getAtkName() << ": " << attacks[2].getManaCost() << "mp." << endl; 
    cout << "4. " << attacks[3].getAtkName() << ": " << attacks[3].getManaCost() << "mp." << endl; 
    cout << "5. " << attacks[4].getAtkName() << ": " << attacks[4].getManaCost() << "mp." << endl; 
}
int Player::performAttack(int attackNum, int def, int res) {
    srand(time(0));
    int damage = 0;
    int multiplyer = rand() % 3 + 1;
    if (attackNum == 0 || attackNum == 1){ //for physical attack
        damage = (attacks[attackNum].getBaseDmg() - (attacks[attackNum].getDmgRed() * def)) * multiplyer;
        if (damage > 0) { //if damage is done
            cout << "You performed " << attacks[attackNum].getAtkName() << " and did " << damage << " damage. It was " << multiplydmg(multiplyer) << endl;
        } else { //if no damage is done or damage is negative
            damage = 0;
            cout << "You performed " << attacks[attackNum].getAtkName() << " and did no damage." << endl;
        }
         

    } else if (attackNum == 2 || attackNum == 3) { //for magic attacks
        if (mp - attacks[attackNum].getManaCost() >= 0) { //if there is enough mana to perform the attack
            damage = (attacks[attackNum].getBaseDmg() - (attacks[attackNum].getDmgRed() * res)) * multiplyer;
            mp = mp - attacks[attackNum].getManaCost();
            if (damage > 0) { //if damage is done
                cout << "You performed " << attacks[attackNum].getAtkName() << " and did " << damage << " damage. It was " << multiplydmg(multiplyer) << endl;
            } else { //if no damage is done or damage is negative
                damage = 0;
                cout << "You performed " << attacks[attackNum].getAtkName() << " and did no damage." << endl;
            } 
            cout << "You lost " << attacks[attackNum].getManaCost() << " mana." << endl;
        } else { //if inadequate mana
            damage = 0;
            cout << "You attempted to perform " << attacks[attackNum].getAtkName() << " but had insufficient mana, so the attack failed and did not damage." << endl;
        }

    } else if (attackNum == 4) { //for rest
        if (mp - attacks[attackNum].getManaCost() > 1000){
            mp = 1000;
        } else {
            mp = mp - attacks[attackNum].getManaCost();
        }
        cout << "You rested and gained " << -attacks[attackNum].getManaCost() << " mana." << endl;

    }
    return damage; //damage is returned
} //this will compute the damage dealt as well as the new base damage