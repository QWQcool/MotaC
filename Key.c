#include "public.h"
#include "hero.h"

typedef struct sKey
{
    TBase base;
}TKey, * PKey;


static void Print(PBase self)
{
    PKey key = (PKey)self;
    switch (self->type)
    {
    case 13:
        printf("\033[33m\033[%d;%dHÔ¿\033[0m", (key->base.x + 1), (key->base.y + 1) * 2);
        break;
    case 14:
        printf("\033[34m\033[%d;%dHÔ¿\033[0m", (key->base.x + 1), (key->base.y + 1) * 2);
        break;
    case 15:
        printf("\033[31m\033[%d;%dHÔ¿\033[0m", (key->base.x + 1), (key->base.y + 1) * 2);
        break;
    default:
        break;
    }
}

static int Collion(PBase self, void* herov)
{
    PKey key = (PKey)self;
    PHero hero = (PHero)herov;
    if (key->base.x == hero->base.x && key->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 13:
            hero->yellow++; //»ÆÔ¿³×Ôö¼Ó
            RemoveSceneItem(self);
            break;
        case 14:
            hero->blue++;
            RemoveSceneItem(self);
            break;
        case 15:
            hero->red++;
            RemoveSceneItem(self);
            break;
        default:
            printf("BUG£¡\n");
            return 1;
            break;
        }
    }
    return 0;
}

static void (KeyFreeCB)(void* that)
{
    free(that);
}

static int KeySave(PBase self, const char* buf, int size)
{
    PKey key = (PKey)self;
    int nret = sprintf(buf, "%d %d %d",
        key->base.type, key->base.x, key->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}

PBase CreateYellowKey(int x, int y, int type, const char* buf)
{
    PKey key = malloc(sizeof(TKey));
    key->base.x = x;
    key->base.y = y;
    key->base.type = type;
    key->base.scene = NULL;
    key->base.Print = Print;
    key->base.Collion = Collion;
    key->base.release = KeyFreeCB;
    key->base.Save = KeySave;
    return (PBase)key;
}

PBase CreateBlueKey(int x, int y, int type, const char* buf)
{
    PKey key = malloc(sizeof(TKey));
    key->base.x = x;
    key->base.y = y;
    key->base.type = type;
    key->base.scene = NULL;
    key->base.Print = Print;
    key->base.Collion = Collion;
    key->base.release = KeyFreeCB;
    key->base.Save = KeySave;
    return (PBase)key;
}

PBase CreateRedKey(int x, int y, int type, const char* buf)
{
    PKey key = malloc(sizeof(TKey));
    key->base.x = x;
    key->base.y = y;
    key->base.type = type;
    key->base.scene = NULL;
    key->base.Print = Print;
    key->base.Collion = Collion;
    key->base.release = KeyFreeCB;
    key->base.Save = KeySave;
    return (PBase)key;
}