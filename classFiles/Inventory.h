#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
using namespace std;
class Inventory{
    private:
        int healthPotions;
        int manaPotions;
        int scrapMetals;
        int keys;
    
    public:
        Inventory();
        Inventory(int h_potions, int m_potions, int metals);
        
        //health potions
        int getHealthPotions();
        void addHealthPotions(int n);

        //mana potions
        int getManaPotions();
        void addManaPotions(int n);;

        //scrap metals
        int getMetals();
        void addMetals(int n);

        //keys
        int getKeys();
        void addKeys();

        //all adds are either +1 or -1

};

#endif