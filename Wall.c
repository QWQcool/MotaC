#include "public.h"
#include "hero.h"

typedef struct sWall
{
    TBase base;
}TWall,*PWall;


static void Print(PBase self)
{
    PWall wall = (PWall)self;
    printf("\033[107;37m\033[%d;%dH墙\033[0m", (wall->base.x + 1), (wall->base.y + 1) * 2); //占一个位 测试
}

static int Collion(PBase self,void* herov)
{
    PWall wall = (PWall)self;
    PHero hero = (PHero)herov;
    if (wall->base.x == hero->base.x && wall->base.y == hero->base.y)
    {
        return 1;
    }
    return 0;
}

static void (WallFreeCB)(void* that)
{
    free(that);
}

static int WallSave(PBase self, const char* buf, int size)
{
    PWall wall = (PWall)self;
    int nret = sprintf(buf, "%d %d %d",
        wall->base.type, wall->base.x, wall->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}

PBase CreateWall(int x, int y, int type, const char* buf)
{
    PWall wall = malloc(sizeof(TWall));
    wall->base.x = x;
    wall->base.y = y;
    wall->base.type = type;
    wall->base.scene = NULL;
    wall->base.Print = Print;
    wall->base.Collion = Collion;
    wall->base.release = WallFreeCB;
    wall->base.Save = WallSave;
    return (PBase)wall;
}