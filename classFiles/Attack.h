#ifndef ATTACK_H
#define ATTACK_H
#include <iostream>
using namespace std;
class Attack{
    private:
        string atkName;
        int baseDmg;
        bool atkType; //Physical is True, Magical is False
        double dmgRed;
        int manaCost; //0 for all physical attacks
    
    public:
        Attack();
        Attack(string name, int dmg, string type, double inc, int mCost);

        //attack name
        void setAtkName(string name);
        string getAtkName();

        //base damage
        void setBaseDmg(int dmg);
        int getBaseDmg();

        //attack type
        void setAtkType(string type);
        bool getAtkType();

        //damage reduction for defense/magic resistance of the enemy
        void setDmgRed(double inc);
        double getDmgRed();

        //mana cost for magic attacks
        void setManaCost(int mCost);
        int getManaCost();

};
#endif