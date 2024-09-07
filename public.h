#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#define _CRT_SECURE_NO_WARNINGS
// 包含必要的标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

// 基础结构体定义
typedef struct sBase TBase;

// 基础结构体指针类型定义
typedef struct sBase(*PBase);

// 打印函数指针类型定义
typedef int (*FPrint)(PBase self);

// 碰撞检测函数指针类型定义
typedef int (*FCollion)(PBase  self, void* hero);
// 释放资源函数指针类型定义
typedef void (*FRelease)(void* that);
// 保存状态函数指针类型定义
typedef int (*FSave)(PBase  self, const char* buf, int size);

// 基础结构体定义
typedef struct sBase
{
    int x;
    int y;
    int type;
    struct sScene* scene;
    FPrint Print;
    FCollion Collion;
    FRelease release;
    FSave  Save;
} BaseStruct;

// 创建主角的函数指针类型定义
typedef PBase(*FCreateMaster)(int x, int y, int type, const char* buf);

// 注册创建函数
void RegCreateMaster(int index, FCreateMaster cb);

// 注册所有创建函数
void RegCreateMasterAll();

// 定义一个指向sScene结构体的指针类型TScene和一个函数指针类型PScene
typedef struct sScene
{
    PBase bases[1024]; // 场景中的游戏对象数组
    int index; // 索引
    int indexScene; // 场景索引
} TScene, (*PScene);

// 全局变量定义
int g_ShareMemory;  // 分配给g_scene的共享内存数量
int g_mapIndex; // 地图索引
PScene* g_scene; // 场景指针数组

// 从文件中填充数组
void fillArrayFromFile(const char* filename, int index);
// 初始化地图
int Map_Init();

// 创建场景
PScene CreateScene(int* maps, int w, int h);

// 打印场景
void PrintScene(PScene scene);

// 更新场景
void UpdateScene(PScene scene);

// 游戏初始化
int Game_Init();
// 加载初始化
int Load_Init();

// 新旧保存机制
int SaveAllScene(); // 新保存所有场景
int LoadSceneFile(); // 加载场景文件

// 游戏中触发的事件
// 加载游戏
int LoadGame();
// 移除场景项
void RemoveSceneItem(PBase base);
// 英雄移动到指定楼层
void SetHeroMoveFloorXY(int x, int y);
int HeroMoveFloor(int beforeIndex);

// 加载DLL相关模块
void LoadAllModule();


// 声明一系列创建不同类型游戏对象的函数，它们都接受位置(x, y)和类型(type)作为参数，并返回一个指向sBase结构体的指针
PBase CreateWall(int x, int y, int type,const char* buf);
PBase CreateHero(int x, int y, int type, const char* buf);
PBase CreateYellowDoor(int x, int y, int type, const char* buf);
PBase CreateBlueDoor(int x, int y, int type, const char* buf);
PBase CreateRedDoor(int x, int y, int type, const char* buf);

PBase CreateGreenSlime(int x, int y, int type, const char* buf);
PBase CreateRedSlime(int x, int y, int type, const char* buf);
PBase CreateBlackSlime(int x, int y, int type, const char* buf);
PBase CreateBlueBat(int x, int y, int type, const char* buf);
PBase CreateBigBat(int x, int y, int type, const char* buf);
PBase CreateBlueMagic(int x, int y, int type, const char* buf);
PBase CreateSkeleton(int x, int y, int type, const char* buf);

PBase CreateYellowKey(int x, int y, int type, const char* buf);
PBase CreateBlueKey(int x, int y, int type, const char* buf);
PBase CreateRedKey(int x, int y, int type, const char* buf);
PBase CreateHpPick(int x, int y, int type, const char* buf);
PBase CreateMoneyPick(int x, int y, int type, const char* buf);
PBase CreateUpStairFloor(int x, int y, int type, const char* buf);
PBase CreateDownStairFloor(int x, int y, int type, const char* buf);
PBase CreateSwordPick(int x, int y, int type, const char* buf);
PBase CreateShop(int x, int y, int type, const char* buf);
#endif
