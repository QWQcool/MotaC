#include "public.h"
#include "hero.h"
#include <conio.h>

typedef struct sShop
{
    TBase base;
}TShop, * PShop;

int ShopBuy(void* herov)
{
    static int s_buyPos = 1;
    int IndexItem = 6;
    int isExit = 0;  //0¼ÌÐøÑ­»·£¬1ÍË³öÑ­»·
    int isBuy = 0;
    char* shopItem[1024] =
    {
        "",
        "5½ð±Ò:10Ñª",
        "5½ð±Ò:5¹¥",
        "5½ð±Ò:5·À",
        "5½ð±Ò:»ÆÔ¿³×",
        "5½ð±Ò:À¶Ô¿³×",
        "5½ð±Ò:ºìÔ¿³×"
    };
    PHero hero = (PHero)herov;
    printf("\033[2J\033[1;1H");
    for (int i = 1; i <= IndexItem; i++)
    {
        if(i == s_buyPos)printf("\033[91m%s\n\n\033[0m", shopItem[i]);
        else printf("%s\n\n", shopItem[i]);
    }
    printf("QÍË³ö B¹ºÂò WSÌôÑ¡ÎïÆ·\n");
    ShowHero();
    switch (_getch())
    {
    case 'W':
    case'w':
        s_buyPos--;
        if (s_buyPos <= 0)
        {
            s_buyPos = IndexItem - 1;
        }
        break;
    case'S':
    case's':
        s_buyPos++;
        if (s_buyPos > IndexItem)
        {
            s_buyPos = 1;
        }
        break;
    case'Q':
    case'q':
        isExit = 1;
        break;
    case'B':
    case'b':
        isBuy = 1;
        break;
    default:
        break;
    }
    if (isBuy)
    {
        switch (s_buyPos)
        {
        case 1:
            if (hero->gold >= 5)
            {
                hero->gold -= 5;
                hero->hp += 10;
            }
            else
            {
                printf("\n\033[91mwithout enough money\033[0m\n");
                Sleep(1000);
            }
            break;
        case 2:
            if (hero->gold >= 5)
            {
                hero->gold -= 5;
                hero->atk += 5;
            }
            else
            {
                printf("\n\033[91mwithout enough money\033[0m\n");
                Sleep(1000);
            }
            break;
        case 3:
            if (hero->gold >= 5)
            {
                hero->gold -= 5;
                hero->def += 5;
            }
            else
            {
                printf("\n\033[91mwithout enough money\033[0m\n");
                Sleep(1000);
            }
            break;
        case 4:
            if (hero->gold >= 5)
            {
                hero->gold -= 5;
                hero->yellow += 1;
            }
            else
            {
                printf("\n\033[91mwithout enough money\033[0m\n");
                Sleep(1000);
            }
            break;
        case 5:
            if (hero->gold >= 5)
            {
                hero->gold -= 5;
                hero->blue += 1;
            }
            else
            {
                printf("\n\033[91mwithout enough money\033[0m\n");
                Sleep(1000);
            }
            break;
        case 6:
            if (hero->gold >= 5)
            {
                hero->gold -= 5;
                hero->red += 1;
            }
            else
            {
                printf("\n\033[91mwithout enough money\033[0m\n");
                Sleep(1000);
            }
            break;
        default:
            break;
        }
        isBuy = 0;
    }
    return isExit;
}

static void Print(PBase self)
{
    PShop shop = (PShop)self;
    printf("\033[91m\033[%d;%dHµê\033[0m", (shop->base.x + 1), (shop->base.y + 1) * 2);

}

static int Collion(PBase self, void* herov)
{
    PShop shop = (PShop)self;
    PHero hero = (PHero)herov;
    if (shop->base.x == hero->base.x && shop->base.y == hero->base.y)
    {
        while (1)
        {
            if (ShopBuy(herov))break;
        }
        return 1;
    }
    return 0;
}

static void (ShopFreeCB)(void* that)
{
    free(that);
}

static int ShopSave(PBase self, const char* buf, int size)
{
    PShop shop = (PShop)self;
    int nret = sprintf(buf, "%d %d %d",
        shop->base.type, shop->base.x, shop->base.y
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
}


PBase CreateShop(int x, int y, int type, const char* buf)
{
    PShop shop = malloc(sizeof(TShop));
    shop->base.x = x;
    shop->base.y = y;
    shop->base.type = type;
    shop->base.scene = NULL;
    shop->base.Print = Print;
    shop->base.Collion = Collion;
    shop->base.release = ShopFreeCB;
    shop->base.Save = ShopSave;
    return (PBase)shop;
}