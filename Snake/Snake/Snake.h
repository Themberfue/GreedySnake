#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

// 蛇初始坐标
#define POS_X 24
#define POS_Y 5

// 符号
#define WALL L'■'
#define BODY  L'●'
#define FOOD L'◆'

// 信息默认值
#define TOTALSCORE 0 // 总分
#define FOODWEIGHT 10 // 每个食物的分数
#define SLEEPSPEED 200 // 游戏速度
#define TARGETSCORE 200 // 目标分数

// 判断相应的键是否按下、
#define KEY_PRESS(vk)  ((GetAsyncKeyState(vk)&1)?1:0)

// 蛇运动的方向
typedef enum DIRCTION {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
}DIRCTION;

typedef enum GAME_STATUS
{
	OK, // 正常进行
	KILl_BY_WALL, // 撞墙死亡
	KILL_BY_SELF, // 撞自己死亡
	END_NORMAL, // 正常退出
	END_BY_WIN // 赢得游戏
} GAME_STATUS;

typedef struct SnakeNode
{
	// 坐标
	int x;
	int y;
	// 指向下一个节点的指针
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;

// 贪吃蛇
typedef struct Snake
{
	pSnakeNode _pSnake; // 指向蛇头的指针
	pSnakeNode _pFood; // 指向食物的指针
	DIRCTION _dir; // 蛇运动的方向
	GAME_STATUS _status; // 游戏的状态
	int _foodWeight; // 一个食物的分数
	int _totalScore; // 总成绩
	int _sleepSpeed; // 游戏速度
	int _targetScore; // 目标分数
} Snake, * pSnake;

// 定位光标
void SetPos(short x, short y);

// 游戏开始
void GameStart(pSnake ps);

// 欢迎界面
void WelcomeToGame();

// 创建游戏地图
void CreateMap();

// 创建蛇
void InitSnake(pSnake ps);

// 创建食物
void CreateFood(pSnake ps);

// 运行游戏
void GameRun(pSnake ps);

// 蛇走一步
void SnakeMove(pSnake ps);

// 下一个节点是否是食物
int IsNextFood(pSnakeNode pn, pSnake ps);

// 吃食物
void EatFood(pSnakeNode pn, pSnake ps);

// 不是食物
void NotFood(pSnakeNode pn, pSnake ps);

// 蛇撞墙而死
void KillByWall(pSnake ps);

// 蛇撞自己而死
void KillBySelf(pSnake ps);

// 结束游戏（善后处理）
void GameEnd(pSnake ps);
