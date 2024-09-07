#ifndef _HERO_H_2024_5_13_
#define _HERO_H_2024_5_13_

#include "public.h"


typedef struct sHero
{
    TBase base;
	int level;
	int hp;
	int atk;
	int def;
	int gold;
	int exp;
	int yellow;
	int blue;
	int red;
	char name[1024];
}THero, * PHero;

PBase CreateHero(int x, int y, int type);

PHero GetHero();

int Hero_Init(PHero hero);

void ShowHero();

int Save_Hero();

int LoadHero(int type, int x, int y, char* HeroName, int level, int hp, int atk, int def, int gold, int exp, int yellow, int blue, int red);

//void LoadHero();

#endif
