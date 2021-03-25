#include <iostream>
#include <fstream>
#include <string>
#include "Map.h"

using namespace std;

int splitMap(string instr, char delim, string arrName[], int l){ //split function from homework 4
    //arrName[l]; //defining the array and the length of it
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

//Default constructor
Map::Map(){
    for (int z = 0; z < 5; z++){
        for (int x = 0; x < 25; x++){
            for (int y = 0; y < 25; y++){
                mapArr[z][x][y] = "";
            }
        }
        
    }
}

int Map::readMap(int lvlNum, string mapFile){
    //opening file and testing if it is working
    ifstream myFile(mapFile); //defining file variable and opening it
    
    
    if(!myFile.is_open()) { //if file is not open, return this value
        return 0; 
    } else { //if file opens
        string line = "";
        int x = 0;
        int y = 0;

        while(getline(myFile, line)) {
            string fileArr[25];
            splitMap(line, ',', fileArr, 25);
            if (line != "") {
                while (y < 25){ //every column has a letter
                    mapArr[lvlNum][x][y] = fileArr[y];
                    y++;
                }
                y = 0;
                x++; //moving to the next row after column is filled 
            }
        }
        return 1;
    }
}

void Map::printMap(int lvlNum){
    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 25; y++){
            cout << mapArr[lvlNum][x][y];
        }
        cout << endl;
    }
}

//---------------------------------
void Map::resetPosition(){ //resets position of player in all levels to 1.
    for (int i = 0; i < 5; i++){
        mapArr[i][1][1] = "h";
    }
    xpos = 1;
    ypos = 1;
}


void Map::setPosition(int lvlNum){ //sets position of a player in a speific level to one and replaces the previous position with a p
    mapArr[lvlNum][1][1] = "h";
    mapArr[lvlNum][xpos][ypos] = "p";
    xpos = 1;
    ypos = 1;
}
int Map::getPositionX(int lvlNum){
    return xpos;

}

int Map::getPositionY(int lvlNum){
    return ypos;
}

//---------------------------------

string Map::getInfoAt(int lvlNum, int x, int y){ //returns value at a specific point
    return mapArr[lvlNum][x][y];
}
void Map::scan(int lvlNum){ //counts monsters and items
    int mcount = 0;
    int icount = 0;
    for (int x = 0; x < 25; x++){
        for (int y = 0; y < 25; y++){
            if(mapArr[lvlNum][x][y] == "m"){
                mcount ++;
            }else if(mapArr[lvlNum][x][y] == "i"){
                icount ++;
            }
        }
    }

    cout << "-----In this level:-----" << endl;
    if(mcount != 0){
        cout << mcount << " monster(s) haven't been encountered." << endl;
    } else {
        cout << "All monsters in this level have been defeated." << endl;
    }
    if(icount != 0){
        cout << icount << " item(s) haven't been found." << endl;
    } else {
        cout << "All items in this level have been picked up." << endl;
    }
}

//---------------------------------

int Map::moveUp(int lvlNum){
    if(mapArr[lvlNum][xpos-1][ypos] != "w"){
        mapArr[lvlNum][xpos][ypos] = "p";
        mapArr[lvlNum][xpos-1][ypos] = "h";
        xpos = xpos - 1;
        return 1;
    } else{
        return 0;
    }
}
int Map::moveDown(int lvlNum){
    if(mapArr[lvlNum][xpos+1][ypos] != "w"){
        mapArr[lvlNum][xpos][ypos] = "p";
        mapArr[lvlNum][xpos+1][ypos] = "h";
        xpos = xpos + 1;
        return 1;
    } else{
        return 0;
    }
}
int Map::moveLeft(int lvlNum){
    if(mapArr[lvlNum][xpos][ypos-1] != "w"){
        mapArr[lvlNum][xpos][ypos] = "p";
        mapArr[lvlNum][xpos][ypos-1] = "h";
        ypos = ypos - 1;
        return 1;
    } else{
        return 0;
    }
}
int Map::moveRight(int lvlNum){
    if(mapArr[lvlNum][xpos][ypos+1] != "w"){
        mapArr[lvlNum][xpos][ypos] = "p";
        mapArr[lvlNum][xpos][ypos+1] = "h";
        ypos = ypos + 1;
        return 1;
    } else{
        return 0;
    }
}