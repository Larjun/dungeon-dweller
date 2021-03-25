#include <iostream>
#include "Attack.h"

using namespace std;

//constructors
Attack::Attack(){
    atkName = "";
    baseDmg = 0;
    dmgRed = 0;
    manaCost = 0;   
}
Attack::Attack(string name, int dmg, string type, double inc, int mCost){
    atkName = name;
    baseDmg = dmg;
    dmgRed = inc;
    manaCost = mCost;
    if (type == "Physical"){
        atkType = true;
    }
    else if (type == "Magic"){
        atkType = false;
    }
}

//attack name
void Attack::setAtkName(string name){
    atkName = name;
}
string Attack::getAtkName(){
    return atkName;
}

//base damage
void Attack::setBaseDmg(int dmg){
    baseDmg = dmg;
}
int Attack::getBaseDmg(){
    return baseDmg;
}

//attack type
void Attack::setAtkType(string type){
    if (type == "Physical"){
        atkType = true;
    }
    else if (type == "Magic"){
        atkType = false;
    }
}
bool Attack::getAtkType(){
    return atkType;
}

//damage reduction for defense/magic resistance of the enemy
void Attack::setDmgRed(double inc){
    dmgRed = inc;
}
double Attack::getDmgRed(){
    return dmgRed;
}

//mana cost for magic attacks
void Attack::setManaCost(int mCost){
    manaCost = mCost;
}
int Attack::getManaCost(){
    return manaCost;
}