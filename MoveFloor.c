#include "public.h"
#include "hero.h"

typedef struct sFloor
{
    TBase base;
}TFloor, * PFloor;



static void Print(PBase self)
{
    PFloor floor = (PFloor)self;
    switch (self->type)
    {
    case 18:
        printf("\033[33m\033[%d;%dH上\033[0m", (floor->base.x + 1), (floor->base.y + 1) * 2);
        break;
    case 19:
        printf("\033[34m\033[%d;%dH下\033[0m", (floor->base.x + 1), (floor->base.y + 1) * 2);
        break;
    default:
        break;
    }
}

static int Collion(PBase self, void* herov)
{
    PFloor floor = (PFloor)self;
    PHero hero = (PHero)herov;
    if (floor->base.x == hero->base.x && floor->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 18:
            //上楼
            //g_mapIndex++;
            HeroMoveFloor(g_mapIndex++);
            break;
        case 19:
            //下楼
            //g_mapIndex--;
            HeroMoveFloor(g_mapIndex--);
            break;
        default:
            break;
        }
        return 0;
    }
    return 0;
}

static int FloorSave(PBase self, const char* buf, int size)
{
    PFloor floor = (PFloor)self;
    int nret = sprintf(buf, "%d %d %d",
        floor->base.type, floor->base.x, floor->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}

static void (FloorFreeCB)(void* that)
{
    free(that);
}

PBase CreateUpStairFloor(int x, int y, int type, const char* buf)
{
    PFloor floor = malloc(sizeof(TFloor));
    floor->base.x = x;
    floor->base.y = y;
    floor->base.type = type;
    floor->base.scene = NULL;
    floor->base.Print = Print;
    floor->base.Collion = Collion;
    floor->base.release = FloorFreeCB;
    floor->base.Save = FloorSave;
    return (PBase)floor;
}

PBase CreateDownStairFloor(int x, int y, int type, const char* buf)
{
    PFloor floor = malloc(sizeof(TFloor));
    floor->base.x = x;
    floor->base.y = y;
    floor->base.type = type;
    floor->base.scene = NULL;
    floor->base.Print = Print;
    floor->base.Collion = Collion;
    floor->base.release = FloorFreeCB;
    floor->base.Save = FloorSave;
    return (PBase)floor;
}

int HeroMoveFloor(int beforeIndex)
{
    PHero hero = GetHero();
    int nowIndex = g_mapIndex;
    hero->base.scene = g_scene[nowIndex];
    // TODO　把Hero从当前场景移除
    for (int i = 0; i < g_scene[beforeIndex]->index; i++)
    {
        if (g_scene[beforeIndex]->bases[i] == hero)
        {
            g_scene[beforeIndex]->bases[i] = g_scene[beforeIndex]->bases[g_scene[beforeIndex]->index - 1];
            g_scene[beforeIndex]->index--;
            break;
        }
    }
    // TODO　把Hero添加到新场景
    g_scene[nowIndex]->bases[g_scene[nowIndex]->index++] = hero;
    //上下楼梯定位
    PBase downPos = NULL;
    PBase upPos = NULL;

    // 找到上下楼梯口的位置
    for (int i = 0; i < g_scene[nowIndex]->index; i++)
    {
        if (nowIndex < g_scene[beforeIndex]->indexScene && g_scene[nowIndex]->bases[i]->type == 18)
        {
            upPos = g_scene[nowIndex]->bases[i];
            break;
        }
        if (nowIndex > g_scene[beforeIndex]->indexScene && g_scene[nowIndex]->bases[i]->type == 19)
        {
            downPos = g_scene[nowIndex]->bases[i];
            break;
        }
    }
    //　检查楼梯口附近的空位置
    int dirS[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
    if (downPos != NULL)  //上楼梯，找下一层下楼的位置，把英雄放过去
    {
        for (int i = 0; i < 4; i++)
        {
            int xx = dirS[i][0] + downPos->x;
            int yy = dirS[i][1] + downPos->y;
            int bFind = 1;
            for (int j = 0; j < g_scene[nowIndex]->index; j++)
            {
                if (g_scene[nowIndex]->bases[j]->x == xx && g_scene[nowIndex]->bases[j]->y == yy)
                {
                    bFind = 0;
                    break;
                }
            }
            if (bFind)
            {
                SetHeroMoveFloorXY(xx, yy);
                break;
            }
        }
    }
    if (upPos != NULL)
    {
        for (int i = 0; i < 4; i++)
        {
            int xx = dirS[i][0] + upPos->x;
            int yy = dirS[i][1] + upPos->y;
            int bFind = 1;
            for (int j = 0; j < g_scene[nowIndex]->index; j++)
            {
                if (g_scene[nowIndex]->bases[j]->x == xx && g_scene[nowIndex]->bases[j]->y == yy)
                {
                    bFind = 0;
                    break;
                }
            }
            if (bFind)
            {
                SetHeroMoveFloorXY(xx, yy);
                break;
            }
        }
    }
    downPos = NULL;
    upPos = NULL;
}

