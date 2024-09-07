#pragma once
#include "public.h"
#include "Hero.h"
typedef struct sMonster
{
    TBase base;
    int hp;
    int atk;
    int def;
    int gold;
    int exp;
    char* name;
}TMonster, * PMonster;

int MonsterFright(PMonster monster, PHero hero);
int MonsterFright_Show(PMonster monster, PHero hero);
