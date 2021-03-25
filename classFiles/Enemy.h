 #ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
using namespace std;
class Enemy{
    private:
        string enemyName;
        int enemyhp;
        int inithp;
        int defense;
        int magResistance;
        int atkStrength;
        int physAtkChance;
        int magAtkChance;
        int standbyChance; //not used in this project by present for usage in the funture
    
    public:
    //constructors
    Enemy();
    Enemy(string name, int newhp, int def, int resist, int atkStrg, int physChance, int magChance, int stbyChance);
    //name
    void setEnemyName(string name);
    string getEnemyName();

    //hp
    void setEnemyhp(int newhp);
    int getEnemyhp();
    void removehp(int dmgTaken);
    void restorehp();

    //defense
    void setDefense(int def);
    int getDefense();

    //magic resistance
    void setMagResistance(int resist);
    int getMagResistance();

    //attack strength
    void setAtkStrength(int atkStrg);
    int getAtkStrength();

    //physical attack chance
    void setPhysAtkChance(int physChance);
    int getPhysAtkChance();

    //magical attack chance
    void setMagAtkChance(int magChance);
    int getMagAtkChance();

    //standby chance
    void setStandbyChance(int stbyChance);
    int getStandbyChance();

     
};

#endif