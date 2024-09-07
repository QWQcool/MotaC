#include "public.h"
#include "hero.h"


typedef struct sDoor
{
    TBase base;
}TDoor, *PDoor;


static void Print(PBase self)
{
    PDoor door = (PDoor)self;
    switch (self->type)
    {
    case 3:
        printf("\033[33m\033[%d;%dH门\033[0m", (door->base.x + 1), (door->base.y + 1) * 2);
        break;
    case 4:
        printf("\033[34m\033[%d;%dH门\033[0m", (door->base.x + 1), (door->base.y + 1) * 2);
        break;
    case 5:
        printf("\033[31m\033[%d;%dH门\033[0m", (door->base.x + 1), (door->base.y + 1) * 2);
        break;
    default:
        break;
    }
}

static int Collion(PBase self, void* herov)
{
    PDoor door = (PDoor)self;
    PHero hero = (PHero)herov;
    if (door->base.x == hero->base.x && door->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 3:
            if (hero->yellow > 0)
            {
                hero->yellow--; //黄钥匙减少
                RemoveSceneItem(self);
                return 0;
            }
            break;
        case 4:
            if (hero->blue > 0)
            {
                hero->blue--;
                RemoveSceneItem(self);
                return 0;
            }
            break;
        case 5:
            if (hero->red > 0)
            {
                hero->red--;
                RemoveSceneItem(self);
                return 0;
            }
            break;
        default:
            break;
        }
        printf("\033[14;1H 你需要钥匙!\n");
        Sleep(1000);
        return 1;
    }
    return 0;
}

static void (DoorFreeCB)(void* that)
{
    free(that);
}

static int DoorSave(PBase self, const char* buf, int size)
{
    PDoor door = (PDoor)self;
    int nret = sprintf(buf, "%d %d %d",
        door->base.type, door->base.x, door->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}

PBase CreateYellowDoor(int x, int y, int type, const char* buf)
{
    PDoor door = malloc(sizeof(TDoor));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    door->base.release = DoorFreeCB;
    door->base.Save = DoorSave;
    return (PBase)door;
}

PBase CreateBlueDoor(int x, int y, int type, const char* buf)
{
    PDoor door = malloc(sizeof(TDoor));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    door->base.release = DoorFreeCB;
    door->base.Save = DoorSave;
    return (PBase)door;
}

PBase CreateRedDoor(int x, int y, int type, const char* buf)
{
    PDoor door = malloc(sizeof(TDoor));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    door->base.release = DoorFreeCB;
    door->base.Save = DoorSave;
    return (PBase)door;
}