/***************************************************************************
**
**   llama.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;

class Llama
{
//Private Variables For Holding Info About Llama Player
private:

//Location takes <x,y> coords
int x,y;
    
//Direction direction player facing
int dir;

//Counter of Llama's lives remaining
int hp;

//Pesos, count of points gathered by Llama
int pesos;

//Punishment, bad stuff happens. In terms of X amount of life lost
int punish;

public:

//Constructor
Llama(int _x,int _y,int _dir,int _hp,int _pesos):x(_x),y(_y),dir(_dir),hp(_hp),pesos(_pesos){}

//Get Methods
int getX() {return x;}
int getY() {return y;}
int getDir() {return dir;}
int getHP() {return hp;}
int getPesos() {return pesos;}
int getPunish() {return punish;}

//Set Methods
void setX(double newX){x=newX;}
void setY(double newY){y=newY;}
void setDir(double newDir){dir=newDir;}
void setHP(double newHP){hp=newHP;}
void setPesos(double newPesos){pesos=newPesos;}
void setPunish(double newPunish){punish=newPunish;}

};
