#include "public.h"
#include "hero.h"

typedef struct sPick
{
    TBase base;
}TPick, * PPick;


static void Print(PBase self)
{
    PPick pick = (PPick)self;
    switch (self->type)
    {
    case 16:
        printf("\033[91m\033[%d;%dH血\033[0m", (pick->base.x + 1), (pick->base.y + 1) * 2);
        break;
    case 17:
        printf("\033[93m\033[%d;%dH$\033[0m", (pick->base.x + 1), (pick->base.y + 1) * 2);
        break;
    case 20:
        printf("\033[93m\033[%d;%dH剑\033[0m", (pick->base.x + 1), (pick->base.y + 1) * 2);
        break;
    default:
        break;
    }
}

static int Collion(PBase self, void* herov)
{
    PPick pick = (PPick)self;
    PHero hero = (PHero)herov;
    if (pick->base.x == hero->base.x && pick->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 16:
            hero->hp += 5;
            RemoveSceneItem(self);
            break;
        case 17:
            hero->gold += 5;
            RemoveSceneItem(self);
            break;
        case 20:
            hero->atk += 20;
            RemoveSceneItem(self);
            break;
        default:
            break;
        }
        return 0;
    }
    return 0;
}

static void (PickFreeCB)(void* that)
{
    free(that);
}

static int PickSave(PBase self, const char* buf, int size)
{
    PPick pick = (PPick)self;
    int nret = sprintf(buf, "%d %d %d",
        pick->base.type, pick->base.x, pick->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}

PBase CreateHpPick(int x, int y, int type, const char* buf)
{
    PPick pick = malloc(sizeof(TPick));
    pick->base.x = x;
    pick->base.y = y;
    pick->base.type = type;
    pick->base.scene = NULL;
    pick->base.Print = Print;
    pick->base.Collion = Collion;
    pick->base.release = PickFreeCB;
    pick->base.Save = PickSave;
    return (PBase)pick;
}

PBase CreateMoneyPick(int x, int y, int type, const char* buf)
{
    PPick pick = malloc(sizeof(TPick));
    pick->base.x = x;
    pick->base.y = y;
    pick->base.type = type;
    pick->base.scene = NULL;
    pick->base.Print = Print;
    pick->base.Collion = Collion;
    pick->base.release = PickFreeCB;
    pick->base.Save = PickSave;
    return (PBase)pick;
}

PBase CreateSwordPick(int x, int y, int type, const char* buf)
{
    PPick pick = malloc(sizeof(TPick));
    pick->base.x = x;
    pick->base.y = y;
    pick->base.type = type;
    pick->base.scene = NULL;
    pick->base.Print = Print;
    pick->base.Collion = Collion;
    pick->base.release = PickFreeCB;
    pick->base.Save = PickSave;
    return (PBase)pick;
}

