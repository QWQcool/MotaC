#include "public.h"
#include <stdio.h>
int Show_Widget();

int main()
{
    RegCreateMasterAll();
    LoadAllModule();
    while (1)
    {
        if (Show_Widget())break;
    };
    while (1)
    {
        PrintScene(g_scene[g_mapIndex]);
        UpdateScene(g_scene[g_mapIndex]);
    }
    for (int i = g_mapIndex; i < g_ShareMemory; i++)
    {
        free(g_scene[i]);
    }
    free(g_scene);
    return 0;
}

int Game_Init()
{
    g_ShareMemory = M_index;
    g_mapIndex = 0;
    g_scene = (PScene*)malloc(sizeof(PScene) * g_ShareMemory);
    Map_Init();
    for (int i = g_mapIndex; i < g_ShareMemory; i++)
    {
        g_scene[i] = CreateScene(Maps[i], mapX, mapY);
    }
}

int Load_Init()
{
    g_ShareMemory = M_index;
    g_scene = (PScene*)malloc(sizeof(PScene) * g_ShareMemory);
    LoadSceneFile();
    return 1;
}