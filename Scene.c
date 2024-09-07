#define _CRT_SECURE_NO_WARNINGS
#include "public.h"
#include "hero.h"
#include "Monster.h"
#include <conio.h>
#include <windows.h>

//PScene s_scene[1024] = { 0 };
static PBase s_removeBase = 0;
static int S_HeroMoveFloorX = -1;
static int S_HeroMoveFloorY = -1;

void UpdateScene(PScene scene)
{
    char c = _getch();
    PHero hero = GetHero();

    int dirX, dirY;
    dirX = dirY = 0;
    switch (c)
    {
    case 'w':dirX = -1; break;
    case 's':dirX = 1; break;
    case 'a':dirY = -1; break;
    case 'd':dirY = 1; break;
    case 'k':
        SaveAllScene();
        return;
    case 'l':
        Load_Init();
        return;
    default:
        break;
    }

    int oldX = hero->base.x;
    int oldY = hero->base.y;

    // 预测移动
    hero->base.x += dirX;
    hero->base.y += dirY;
    int bCollion = 0;
    // 判断是否碰撞
    for (int i = 0; i < scene->index; i++)
    {
        PBase base = scene->bases[i];
        if(base == hero)continue;

        int isCo1lion = base->Collion(base, hero);
        if(isCo1lion == 1)
        {
            bCollion = 1;
            break;
        }
    }
    //TOOD

    if(bCollion)
    {
        hero->base.x = oldX;
        hero->base.y = oldY;
    }

    if (S_HeroMoveFloorX != -1 && S_HeroMoveFloorY != -1)
    {
        hero->base.x = S_HeroMoveFloorX;
        hero->base.y = S_HeroMoveFloorY;
        S_HeroMoveFloorX = -1;
        S_HeroMoveFloorY = -1;
    }
}

int SaveAllScene()
{
    for (int i = 0; i < g_ShareMemory; ++i)
    {
        //PScene scene = g_scene[i];
        char scenebuf[1024];
        sprintf(scenebuf, ".\\scenes\\%d.scene.txt", i);
        FILE* pFile = fopen(scenebuf, "w");
        fprintf(pFile, "%d %d\n", i, g_scene[i]->index);
        for (int j = 0; j < g_scene[i]->index; j++)
        {
            PBase base = g_scene[i]->bases[j];
            char buf[1024] = { 0 };
            int size = base->Save(base, buf, sizeof(buf));
            fprintf(pFile, "%s\n", buf);
        }
        fclose(pFile);
    }
    printf("\033[15;1H SceneStyle存档成功!");
    Sleep(1000);

    return 1;
}

void PrintScene(PScene scene)
{
    printf("\033[2J");
    for (int i = 0; i < scene->index; i++)
    {
        PBase base = scene->bases[i];
        base->Print(base);
    }
    ShowHero();
    //隐藏光标
    printf("\033[?25l");
}

void RemoveSceneItem(PBase base)
{
    s_removeBase = base;
    for (int i = 0; i < g_scene[g_mapIndex]->index; i++)
    {
        if (g_scene[g_mapIndex]->bases[i] == s_removeBase)
        {
            g_scene[g_mapIndex]->bases[i] = g_scene[g_mapIndex]->bases[g_scene[g_mapIndex]->index - 1];
            g_scene[g_mapIndex]->index--;
            break;
        }
    }
    s_removeBase->release(s_removeBase);
}
//

void SetHeroMoveFloorXY(int x, int y)
{
    S_HeroMoveFloorX = x;
    S_HeroMoveFloorY = y;
}

int LoadGame()
{
    //释放之前的内存
    for (int i = 0; i < g_ShareMemory; ++i)
    {
        PScene scene = g_scene[i];
        for (int j = 0; j < scene->index; j++)
        {
            PBase base = scene->bases[j];
            base->release(base);
        }
        free(g_scene[i]);
        g_scene[i] = NULL;
    }
    free(GetHero());
    LoadSceneFile(g_scene);
}

int GetDirectory(char* path, int len)
{
    unsigned long size = GetCurrentDirectoryA(0, NULL);
    if (GetCurrentDirectoryA(len, path) == 0)
        return -1;
    return size;
}

//FindAllFiles("./","*.*")
void FindAllFiles(const char* dir, const char* extend)
{
    HANDLE hFind;
    WIN32_FIND_DATAA findData;
    LARGE_INTEGER size;
    char path[4096];
    sprintf(path, "%s/%s", dir, extend);
    hFind = FindFirstFileA(path, &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Failed to find first file!\n");
        return;
    }

    do
    {
        // 忽略"."和".."两个结果 
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
        {
            printf("%s %s", findData.cFileName, "\t<dir>\n");
        }
        else
        {
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            printf("%8lld bytes \t %s \n", size.QuadPart, findData.cFileName);
        }

    } while (FindNextFileA(hFind, &findData));
    FindClose(hFind);
}


typedef void(*FAddHp)(PHero hero, int hp);
typedef int(*FMonsterFright)(PMonster monster, PHero hero);
typedef int(*FMonsterFright_Show)(PMonster monster, PHero hero);
typedef void(*FRemoveSceneItem)(PBase self);

typedef struct sFunc
{
    FAddHp AddHp;
    FMonsterFright MonsterFright;
    FMonsterFright_Show MonsterFright_Show;
    FRemoveSceneItem RemoveSceneItem;
}TFunc, * PFunc;

TFunc s_funcs;
typedef int(*FGetModuleId)();
typedef void(*FRegFuncs)(PFunc funcs);
typedef struct sPluginNode_
{
    char path[1024];
    char name[128];
    HMODULE module;
    FCreateMaster CreateMaster;
    FGetModuleId GetModuleId;
    FRegFuncs  funcs;

}sPluginNode;

typedef struct sPlugin_
{
    sPluginNode* nodes[1024];
    int index;
}sPlugin;


sPlugin* GetAllPluginModule()
{
    char pathDir[1024] = "";
    int len = GetDirectory(pathDir, 1024);

    HANDLE hFind;
    WIN32_FIND_DATAA findData;
    LARGE_INTEGER size;
    char path[4096];
    sprintf(path, "%s\\plugins\\%s", pathDir, "*.dll");
    hFind = FindFirstFileA(path, &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Failed to find first file!\n");
        return NULL;
    }

    sPlugin* plugin = malloc(sizeof(sPlugin));
    memset(plugin, 0, sizeof(sPlugin));
    plugin->index = 0;
    do
    {
        // 忽略"."和".."两个结果 
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
        {
            //printf("%s %s", findData.cFileName, "\t<dir>\n");
        }
        else
        {
            sPluginNode* node = malloc(sizeof(sPluginNode));
            plugin->nodes[plugin->index++] = node;

            sprintf(node->path, "%s\\plugins\\%s", pathDir, findData.cFileName);
            sprintf(node->name, "%s", findData.cFileName);
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            //printf("%8ld bytes \t %s \n", size.QuadPart, findData.cFileName);
            // 加载模块
            HMODULE module = LoadLibraryA(node->path);
            // 获取模块中的导出函数
            FCreateMaster CreateMaster = (FCreateMaster)GetProcAddress(module, "CreateMaster");
            FGetModuleId GetModuleId = (FCreateMaster)GetProcAddress(module, "GetModuleId");
            FRegFuncs RegFuncs = (FRegFuncs)GetProcAddress(module, "RegFuncs");
            node->module = module;
            node->CreateMaster = CreateMaster;
            node->GetModuleId = GetModuleId;
            node->funcs = RegFuncs;
        }

    } while (FindNextFileA(hFind, &findData));
    FindClose(hFind);
    return plugin;
}


static void AddHp(PHero hero, int hp)
{
    hero->hp += hp;
}

void LoadAllModule()
{
    s_funcs.AddHp = AddHp;
    s_funcs.MonsterFright = MonsterFright;
    s_funcs.MonsterFright_Show = MonsterFright_Show;
    s_funcs.RemoveSceneItem = RemoveSceneItem;
    sPlugin* plugin = GetAllPluginModule();

    for (int i = 0; i < plugin->index; ++i)
    {
        sPluginNode* node = plugin->nodes[i];
        //node->CreateMaster
        RegCreateMaster(node->GetModuleId(), node->CreateMaster);

        node->funcs(&s_funcs);
    }


}