#include <iostream>
#include "Enemy.h"

using namespace std;

//constructors
Enemy::Enemy(){
    enemyName = "";
    enemyhp = 0;
    inithp = 0;
    defense = 0;
    magResistance = 0;
    atkStrength = 0;
    physAtkChance = 0;
    magAtkChance = 0;
    standbyChance = 0;
}
Enemy::Enemy(string name, int newhp, int def, int resist, int atkStrg, int physChance, int magChance, int stbyChance){
    enemyName = name;
    enemyhp = newhp;
    inithp = newhp;
    defense = def;
    magResistance = resist;
    atkStrength = atkStrg;
    physAtkChance = physChance;
    magAtkChance = magChance;
    standbyChance = stbyChance;
}
//name
void Enemy::setEnemyName(string name){
    enemyName = name;
}
string Enemy::getEnemyName(){
    return enemyName;
}

//hp
void Enemy::setEnemyhp(int newhp){
    enemyhp = newhp;
    inithp = newhp;
}
int Enemy::getEnemyhp(){
    return enemyhp;
}
void Enemy::removehp(int dmgTaken){
    enemyhp = enemyhp - dmgTaken;
}
void Enemy::restorehp(){ //restores the enemy hp after it is defeated so that enemy can reappear somewhere 
    enemyhp = inithp;
}

//defense
void Enemy::setDefense(int def){
    defense = def;
}
int Enemy::getDefense(){
    return defense;
}

//magic resistance
void Enemy::setMagResistance(int resist){
    magResistance = resist;
}
int Enemy::getMagResistance(){
    return magResistance;
}

//attack strength
void Enemy::setAtkStrength(int atkStrg){
    atkStrength = atkStrg;
}
int Enemy::getAtkStrength(){
    return atkStrength;
}

//physical attack chance
void Enemy::setPhysAtkChance(int physChance){
    physAtkChance = physChance;
}
int Enemy::getPhysAtkChance(){
    return physAtkChance;
}

//magical attack chance
void Enemy::setMagAtkChance(int magChance){
    magAtkChance = magChance;
}
int Enemy::getMagAtkChance(){
    return magAtkChance;
}

//standby chance - not used in this project by present for usage in the funture
void Enemy::setStandbyChance(int stbyChance){
    standbyChance = stbyChance;
}
int Enemy::getStandbyChance(){
    return standbyChance;
}