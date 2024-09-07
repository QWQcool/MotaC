#include "public.h"
#include "hero.h"
#include "Monster.h"
//typedef struct sMonster
//{
//    TBase base;
//    int hp;
//    int atk;
//    int def;
//    int gold;
//    int exp;
//    char* name;
//}TMonster, * PMonster;
//
//int MonsterFright(PMonster monster, PHero hero);
//int MonsterFright_Show(PMonster monster, PHero hero);

static void Print(PBase self)
{
    PMonster monster = (PMonster)self;
    
    switch (self->type)
    {
    //6绿头怪 7红头怪 8黑头怪 9蓝蝙蝠 10大蝙蝠 11蓝法师 12骷髅人
    case 6:
        printf("\033[96m\033[%d;%dH史\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    case 7:
        printf("\033[91m\033[%d;%dH史\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    case 8:
        printf("\033[90m\033[%d;%dH史\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    case 9:
        printf("\033[34m\033[%d;%dH蝙\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    case 10:
        printf("\033[94m\033[%d;%dH蝙\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    case 11:
        printf("\033[35m\033[%d;%dH法\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    case 12:
        printf("\033[37m\033[%d;%dH骷\033[0m", (monster->base.x + 1), (monster->base.y + 1) * 2);
        break;
    default:
        break;
    }

}

static int Collion(PBase self, void* herov)
{
    PMonster monster = (PMonster)self;
    PHero hero = (PHero)herov;
    if (monster->base.x == hero->base.x && monster->base.y == hero->base.y)
    {
        //6绿头怪 7红头怪 8黑头怪 9蓝蝙蝠 10大蝙蝠 11蓝法师 12骷髅人
        if (MonsterFright(monster, hero))
        {
            RemoveSceneItem(self);
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

static void (MonsterFreeCB)(void* that)
{
    free(that);
}

static int MonsterSave(PBase self, const char* buf, int size)
{
    PMonster monster = (PMonster)self;
    //int nret = sprintf(buf, "%d,%d,%d,%s,%d,%d,%d,%d,%d",
    //    monster->base.type, monster->base.x, monster->base.y,monster->name,monster->hp,monster->atk,monster->def,monster->gold,monster->exp
    //);
    int nret = sprintf(buf, "%d %d %d",
        monster->base.type, monster->base.x, monster->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}

//6绿头怪 7红头怪 8黑头怪 9蓝蝙蝠 10大蝙蝠 11蓝法师 12骷髅人
PBase CreateGreenSlime(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 30;
    monster->atk = 5;
    monster->def = 15;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "绿色史莱姆";
    return (PBase)monster;
}

PBase CreateRedSlime(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 25;
    monster->atk = 15;
    monster->def = 5;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "红色史莱姆";
    return (PBase)monster;
}

PBase CreateBlackSlime(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 30;
    monster->atk = 25;
    monster->def = 10;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "黑色史莱姆";
    return (PBase)monster;
}

PBase CreateBlueBat(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 25;
    monster->atk = 15;
    monster->def = 0;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "蓝色蝙蝠";
    return (PBase)monster;
}

PBase CreateBigBat(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 40;
    monster->atk = 20;
    monster->def = 0;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "大蝙蝠";
    return (PBase)monster;
}

PBase CreateBlueMagic(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 50;
    monster->atk = 25;
    monster->def = 5;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "蓝色法师";
    return (PBase)monster;
}

PBase CreateSkeleton(int x, int y, int type)
{
    PMonster monster = malloc(sizeof(TMonster));
    monster->base.x = x;
    monster->base.y = y;
    monster->base.type = type;
    monster->base.scene = NULL;
    monster->base.Print = Print;
    monster->base.Collion = Collion;
    monster->base.release = MonsterFreeCB;
    monster->base.Save = MonsterSave;
    monster->hp = 50;
    monster->atk = 30;
    monster->def = 25;
    monster->gold = 5;
    monster->exp = 5;
    monster->name = "骷髅人";
    return (PBase)monster;
}

int MonsterFright_Show(PMonster monster, PHero hero)
{
    int H_damage = hero->atk - monster->def;
    int M_damage = monster->atk - hero->def;
    if (H_damage <= 0)H_damage = 1;
    if (M_damage <= 0)M_damage = 1;
    while (monster->hp>0 && hero->hp>0)
    {
        printf("\033[1;65H                       ");
        printf("\033[2;65H      ");
        printf("\033[3;65H        ");
        printf("\033[4;65H        ");
        printf("\033[5;65H      ");
        printf("\033[6;65H      ");

        printf("\033[1;65H英雄:%s",hero->name);
        printf("\033[2;65H血量:%d", hero->hp);
        printf("\033[3;65H攻击力:%d", hero->atk);
        printf("\033[4;65H防御力:%d", hero->def);
        printf("\033[5;65H经验:%d", hero->exp);
        printf("\033[6;65H金币:%d", hero->gold);

        printf("\033[1;35H                       ");
        printf("\033[2;35H                       ");
        printf("\033[3;35H                       ");
        printf("\033[4;35H                       ");
        printf("\033[5;35H                       ");
        printf("\033[6;35H                       ");

        printf("\033[1;35H怪物名称:%s", monster->name);
        printf("\033[2;35H血量:%d", monster->hp);
        printf("\033[3;35H攻击力:%d", monster->atk);
        printf("\033[4;35H防御力:%d", monster->def);
        printf("\033[5;35H经验:%d", monster->exp);
        printf("\033[6;35H金币:%d", monster->gold);
        //TODO 根据英雄等级，英雄可以拥有一个暴击值概率翻倍伤害
        hero->hp -= M_damage;
        monster->hp -= H_damage;
        Sleep(200);
    }
    //printf("\033[10;35H红钥匙:%d", s_hero->red);
    if (hero->hp > 0)
    {
        return 1;
    }
    else
    {
        printf("你输掉了游戏");
        //TODO 输掉游戏相关
    }

}

int MonsterFright(PMonster monster, PHero hero) 
{
    printf("\033[1;35H怪物名称:%s", monster->name);
    printf("\033[2;35H血量:%d", monster->hp);
    printf("\033[3;35H攻击力:%d", monster->atk);
    printf("\033[4;35H防御力:%d", monster->def);
    printf("\033[5;35H经验:%d", monster->exp);
    printf("\033[6;35H金币:%d", monster->gold);
    printf("\033[7;35H摁y 开始战斗 摁n 躲开战斗");
    char YorN = _getch();
    int isFright = 0;
    switch (YorN)
    {
    case'y':
    case'Y':
        isFright = 1;
        break;
    case'n':
    case'N':
        isFright = 0;
        break;
    default:
        break;
    }
    if (isFright)
    {
        //printf("\033[2J");
        int isWin = MonsterFright_Show(monster, hero);
        if (isWin)return 1;
    }
    return 0;
}