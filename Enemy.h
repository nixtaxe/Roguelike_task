#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
//#include <conio.h>
using namespace std;

class Enemy {
public:
    Enemy(string name, char tile, int level, int attack,
          int defense, int health, int xp);

    int attack();

    int takeDamage(int attack);

    //Getters
    void getPosition(int &x, int &y);

    string getName() { return _name; };

    char getTile() { return _tile; };

    char getMove(int playerX, int playerY);

    //Setters
    void setPosition(int x, int y);

private:
    string _name;
    char _tile;
    int _x;
    int _y;

    int _level;
    int _attack;
    int _defense;
    int _health;
    int _experienceValue;

    //vector <items>
};

