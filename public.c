#include "public.h"

// 定义一个静态数组s_creates，用于存储不同类型的游戏对象创建函数
static FCreateMaster  s_creates[1024] = { 0 };

void RegCreateMaster(int index, FCreateMaster cb)
{
    s_creates[index] = cb;
}

// 函数RegCreateMasterAll用于注册所有预定义的游戏对象创建函数
void RegCreateMasterAll()
{
    RegCreateMaster(1, CreateWall); // 注册创建墙壁的函数
    RegCreateMaster(2, CreateHero); // 注册创建英雄的函数
    RegCreateMaster(3, CreateYellowDoor); // 注册创建黄色门的函数
    RegCreateMaster(4, CreateBlueDoor); // 注册创建蓝色门的函数
    RegCreateMaster(5, CreateRedDoor); // 注册创建红色门的函数
    //6绿头怪 7红头怪 8黑头怪 9蓝蝙蝠 10大蝙蝠 11蓝法师 12骷髅人
    RegCreateMaster(6, CreateGreenSlime);
    RegCreateMaster(7, CreateRedSlime);
    RegCreateMaster(8, CreateBlackSlime);
    RegCreateMaster(9, CreateBlueBat);
    RegCreateMaster(10, CreateBigBat);
    RegCreateMaster(11, CreateBlueMagic);
    RegCreateMaster(12, CreateSkeleton);

    RegCreateMaster(13, CreateYellowKey);
    RegCreateMaster(14, CreateBlueKey);
    RegCreateMaster(15, CreateRedKey);
    RegCreateMaster(16, CreateHpPick);
    RegCreateMaster(17, CreateMoneyPick);
    RegCreateMaster(18, CreateUpStairFloor); // 注册创建上楼梯的地板的函数
    RegCreateMaster(19, CreateDownStairFloor); // 注册创建下楼梯的地板的函数
    RegCreateMaster(20, CreateSwordPick);
    RegCreateMaster(21, CreateShop); 
}

static int sg_Sceneindex = 0;

PScene CreateScene(int* maps, int w, int h)
{
    // 分配内存用于存储场景信息
    PScene scene = (PScene)malloc(sizeof(TScene));
    scene->index = 0;
    scene->indexScene = sg_Sceneindex;
    sg_Sceneindex++;
    // 遍历地图数据，对每个位置调用相应的创建函数
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            // 获取当前位置的类型
            int type = maps[x * w + y];

            // 根据类型从s_creates数组中获取相应的创建函数
            FCreateMaster f = s_creates[type];
            if (f == NULL) continue; // 如果没有找到对应的创建函数，跳过此次循环

            // 调用创建函数创建游戏对象
            PBase base = f(x, y, type,NULL);
            if (base == NULL) continue; // 如果创建失败，跳过此次循环

            // 将新创建的游戏对象添加到场景中
            base->scene = scene;
            scene->bases[scene->index] = base;
            scene->index++;
        }
    }

    // 返回创建的场景
    return scene;
}

//新加载方式
int LoadSceneFile()
{
    const char filename[1024];
    for (int i = 0; i < g_ShareMemory; i++)
    {
        int sX = 0;
        int sY = 0;
        int sType = 0;
        sprintf(filename, ".\\scenes\\%d.scene.txt", i);
        FILE* file = fopen(filename, "r");
        if (file == NULL) 
        {
            printf("Failed to open file %s\n", filename);
            exit(1);
        }
        g_scene[i] = (PScene)malloc(sizeof(TScene));

        g_scene[i]->index = 0;
        int indexLast = 0;
        do
        {
            char buf[1024] = { 0 };
            fgets(buf, 1024, file);
            sscanf(buf, "%d %d", &g_scene[i]->indexScene, &indexLast);
        } while (0);
        for (int j = 0; j < indexLast; j++)
        {
            char buf[1024] = { 0 };
            fgets(buf, 1024, file);
            int sType, sX, sY;
            sscanf(buf, "%d %d %d", &sType, &sX, &sY);
            if (sType == 2)
            {
                g_mapIndex = g_scene[i]->indexScene;
            }
            FCreateMaster f = s_creates[sType];
            if (f == NULL)continue;

            PBase base = f(sX, sY, sType, buf);
            if (base == NULL)continue;
            base->scene = g_scene[i];
            g_scene[i]->bases[g_scene[i]->index++] = base;
        }
        fclose(file);
    }
    return 1;
}

//开始游戏，读地图初始化。
void fillArrayFromFile(const char* filename, int index) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return;
    }

    int row, col;
    for (row = 0; row < mapX; row++) {
        for (col = 0; col < mapY; col++) {
            if (fscanf(file, "%d", &Maps[index][row][col]) != 1) {
                printf("Failed to read data from file %s\n", filename);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
}

int Map_Init()
{
    char mapSourceFile[256];
    for (int i = 0; i < M_index; i++)
    {
        sprintf(mapSourceFile, ".\\map\\map%d.txt", i);
        fillArrayFromFile(mapSourceFile, i);
    }
}
