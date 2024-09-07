#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#define _CRT_SECURE_NO_WARNINGS
// ������Ҫ�ı�׼��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

// �����ṹ�嶨��
typedef struct sBase TBase;

// �����ṹ��ָ�����Ͷ���
typedef struct sBase(*PBase);

// ��ӡ����ָ�����Ͷ���
typedef int (*FPrint)(PBase self);

// ��ײ��⺯��ָ�����Ͷ���
typedef int (*FCollion)(PBase  self, void* hero);
// �ͷ���Դ����ָ�����Ͷ���
typedef void (*FRelease)(void* that);
// ����״̬����ָ�����Ͷ���
typedef int (*FSave)(PBase  self, const char* buf, int size);

// �����ṹ�嶨��
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

// �������ǵĺ���ָ�����Ͷ���
typedef PBase(*FCreateMaster)(int x, int y, int type, const char* buf);

// ע�ᴴ������
void RegCreateMaster(int index, FCreateMaster cb);

// ע�����д�������
void RegCreateMasterAll();

// ����һ��ָ��sScene�ṹ���ָ������TScene��һ������ָ������PScene
typedef struct sScene
{
    PBase bases[1024]; // �����е���Ϸ��������
    int index; // ����
    int indexScene; // ��������
} TScene, (*PScene);

// ȫ�ֱ�������
int g_ShareMemory;  // �����g_scene�Ĺ����ڴ�����
int g_mapIndex; // ��ͼ����
PScene* g_scene; // ����ָ������

// ���ļ����������
void fillArrayFromFile(const char* filename, int index);
// ��ʼ����ͼ
int Map_Init();

// ��������
PScene CreateScene(int* maps, int w, int h);

// ��ӡ����
void PrintScene(PScene scene);

// ���³���
void UpdateScene(PScene scene);

// ��Ϸ��ʼ��
int Game_Init();
// ���س�ʼ��
int Load_Init();

// �¾ɱ������
int SaveAllScene(); // �±������г���
int LoadSceneFile(); // ���س����ļ�

// ��Ϸ�д������¼�
// ������Ϸ
int LoadGame();
// �Ƴ�������
void RemoveSceneItem(PBase base);
// Ӣ���ƶ���ָ��¥��
void SetHeroMoveFloorXY(int x, int y);
int HeroMoveFloor(int beforeIndex);

// ����DLL���ģ��
void LoadAllModule();


// ����һϵ�д�����ͬ������Ϸ����ĺ��������Ƕ�����λ��(x, y)������(type)��Ϊ������������һ��ָ��sBase�ṹ���ָ��
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
