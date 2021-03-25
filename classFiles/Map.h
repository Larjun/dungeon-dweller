#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Map{
    private:
        string mapArr[5][25][25]; //1 is the level num, 2 is x axis, 3 is y axis
        int xpos;
        int ypos;

    public:
        Map();
        int readMap(int lvlNum, string mapFile);
        void printMap(int lvlNum);
        
        void resetPosition();
        void setPosition(int lvlNum);
        int getPositionX(int lvlNum);
        int getPositionY(int lvlNum);

        string getInfoAt(int lvlNum, int x, int y);
        void scan(int lvlNum);

        int moveUp(int lvlNum);
        int moveDown(int lvlNum);
        int moveLeft(int lvlNum);
        int moveRight(int lvlNum);

};

#endif