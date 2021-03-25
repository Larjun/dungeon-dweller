#include <iostream>
#include "Inventory.h"

using namespace std;

Inventory::Inventory(){
    healthPotions = 0;
    manaPotions = 0;
    scrapMetals = 0;
    keys = 0;
}
Inventory::Inventory(int h_potions, int m_potions, int metals){
    healthPotions = h_potions;
    manaPotions = m_potions;
    scrapMetals = metals;
    keys = 0;
}
        
//health potions
int Inventory::getHealthPotions(){
    return healthPotions;
}
void Inventory::addHealthPotions(int n){
    healthPotions = healthPotions + n;
}


//mana potions
int Inventory::getManaPotions(){
    return manaPotions;
}
void Inventory::addManaPotions(int n){
    manaPotions = manaPotions + n;
}


//scrap metals
int Inventory::getMetals(){
    return scrapMetals;
}
void Inventory::addMetals(int n){
    scrapMetals = scrapMetals + n;
}


//keys
int Inventory::getKeys(){
    return keys;
}
void Inventory::addKeys(){
    keys++;
}