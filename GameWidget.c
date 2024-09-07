#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include "public.h"

int Show_Widget()
{
    static int s_selectPos = 1;
    int IndexItem = 4;
    int isExit = 0;  //0继续循环，1退出循环
    int isSelect = 0;
    char* shopItem[1024] =
    {
        "",
        "开始游戏",
        "读取存档",
        "关于游戏",
        "退出游戏"
    };
    printf("\033[2J\033[1;1H");
    printf("\033[%d;35H------------------------------", 10);
    for (int i = 1; i <= IndexItem; i++)
    {
        if (i == s_selectPos)printf("\033[%d;35H>\033[91m%s\n\n\033[0m",10+i*2, shopItem[i]);
        else printf("\033[%d;35H%s\n\n", 10+i*2,shopItem[i]);
    }
    printf("\033[%d;35HQ退出 B进入 WS挑选\n", 10+(IndexItem+1)*2);
    printf("\033[%d;35H------------------------------", 10 + (IndexItem + 2) * 2);
    printf("\033[?25l");
    switch (_getch())
    {
    case 'W':
    case'w':
        s_selectPos--;
        if (s_selectPos <= 0)
        {
            s_selectPos = IndexItem;
        }
        break;
    case'S':
    case's':
        s_selectPos++;
        if (s_selectPos > IndexItem)
        {
            s_selectPos = 1;
        }
        break;
    case'Q':
    case'q':
        exit(1);
        break;
    case'B':
    case'b':
        isSelect = 1;
        break;
    default:
        break;
    }
    if (isSelect)
    {
        switch (s_selectPos)
        {
        case 1:
            Game_Init();
            isExit = 1;
            break;
        case 2:
            Load_Init();

            isExit = 1;
            //TODO
            //存档选择，多个存档
            break;
        case 3:
            //TODO
            //自己的感悟与缘由
            break;
        case 4:
            exit(1);
            break;
        default:
            break;
        }
        isSelect = 0;
    }
    return isExit;
}
