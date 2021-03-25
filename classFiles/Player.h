#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Attack.h"
using namespace std;

class Player{
    private:
        string plname; //player name
        int hp; //health point
        int mp; //mana point
        int ap; //armor point
        Attack attacks[5];

    public:
        Player();
        Player(string newName, int newHealth, int newMana, int newArmor);

        string getName();
        void setName(string newName);

        //health functions
        int gethp();
        void newhp(int dmgTaken);
        void restorehp();

        //mana functions
        int getmp();
        void newmp(int manaUsed);
        void restoremp();

        //armor functions
        int getap();
        void removeap(); //either +1 or -1
        void restoreap();

        //attack functions
        int readAttack(string attackFile);
        void showAttack();
        int performAttack(int attackNum, int def, int res); //this will compute the damage dealt as well as the new base damage

};
#endif