#define _CRT_SECURE_NO_WARNINGS 1

#include "snake.h"

void SetPos(short x, short y)
{
	//获得标准输出设备的句柄
	HANDLE houtput = NULL;
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);

	//定位光标的位置
	COORD pos = { x, y };
	SetConsoleCursorPosition(houtput, pos);
}

void WelcomeToGame()
{
	SetPos(40, 14);
	wprintf(L"欢迎来到贪吃蛇小游戏\n");
	SetPos(42, 20);
	system("pause");
	system("cls");
	SetPos(25, 14);
	wprintf(L"用 ↑. ↓ . ← . → 来控制蛇的移动，按F3加速，F4减速\n");
	SetPos(25, 15);
	wprintf(L"加速能够得到更高的分数\n");

	SetPos(42, 20);
	system("pause");
	system("cls");
}

void CreateMap()
{
	//上
	int i = 0;
	for (i = 0; i < 29; i++)
	{
		wprintf(L"%lc", WALL);
	}

	//下
	SetPos(0, 26);
	for (i = 0; i < 29; i++)
	{
		wprintf(L"%lc", WALL);
	}
	//左
	for (i = 1; i <= 25; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}

	//右
	for (i = 1; i <= 25; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}

}

void InitSnake(pSnake ps)
{
	int i = 0;
	pSnakeNode cur = NULL;

	for (i = 0; i < 5; i++)
	{
		cur = (pSnakeNode)malloc(sizeof(SnakeNode));
		if (cur == NULL)
		{
			perror("InitSnake()::malloc()");
			return;
		}
		cur->next = NULL;
		cur->x = POS_X + 2 * i;
		cur->y = POS_Y;

		//头插法插入链表
		if (ps->_pSnake == NULL) //空链表
		{
			ps->_pSnake = cur;
		}
		else //非空
		{
			cur->next = ps->_pSnake;
			ps->_pSnake = cur;
		}
	}

	cur = ps->_pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}

	//设置贪吃蛇的属性
	ps->_dir = RIGHT;//默认向右
	ps->_totalScore = TOTALSCORE;
	ps->_foodWeight = FOODWEIGHT;
	ps->_sleepSpeed = SLEEPSPEED;//单位是毫秒
	ps->_status = OK;
	ps->_targetScore = TARGETSCORE;
}

void CreateFood(pSnake ps)
{
	int x = 0;
	int y = 0;

	//生成x是2的倍数
	//x：2~54
	//y: 1~25
again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);

	//x和y的坐标不能和蛇的身体坐标冲突

	pSnakeNode cur = ps->_pSnake;
	while (cur)
	{
		if (x == cur->x && y == cur->y)
		{
			goto again;
		}
		cur = cur->next;
	}

	//创建食物的节点
	pSnakeNode pFood = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pFood == NULL)
	{
		perror("CreateFood()::malloc()");
		return;
	}

	pFood->x = x;
	pFood->y = y;
	pFood->next = NULL;

	SetPos(x, y);//定位位置
	wprintf(L"%lc", FOOD);

	ps->_pFood = pFood;
}

void GameStart(pSnake ps)
{
	//0. 先设置窗口的大小，再光标隐藏
	system("mode con cols=100 lines=30");
	system("title 贪吃蛇");
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);

	//隐藏光标操作
	CONSOLE_CURSOR_INFO CursorInfo;

	GetConsoleCursorInfo(houtput, &CursorInfo);//获取控制台光标信息

	CursorInfo.bVisible = false; //隐藏控制台光标

	SetConsoleCursorInfo(houtput, &CursorInfo);//设置控制台光标状态

	//1. 打印环境界面和功能介绍
	WelcomeToGame();
	//2. 绘制地图
	CreateMap();
	//3. 创建蛇
	InitSnake(ps);
	//4. 创建食物
	CreateFood(ps);
}

void PrintHelpInfo()
{
	SetPos(64, 14);
	wprintf(L"%ls", L"不能穿墙，不能咬到自己");
	SetPos(64, 15);
	wprintf(L"%ls", L"用 ↑. ↓ . ← . → 来控制蛇的移动");
	SetPos(64, 16);
	wprintf(L"%ls", L"按F3加速，F4减速");
	SetPos(64, 17);
	wprintf(L"%ls", L"按ESC退出游戏，按空格暂停游戏");
	SetPos(64, 18);
	wprintf(L"%ls", L"Copyright[2024][@Themberfue].");
}

// 暂停
void Pause()
{
	while (1)
	{
		Sleep(200);
		if (KEY_PRESS(VK_SPACE))
		{
			break;
		}
	}
}

int IsNextFood(pSnakeNode pn, pSnake ps)
{
	return (ps->_pFood->x == pn->x && ps->_pFood->y == pn->y);
}

void EatFood(pSnakeNode pn, pSnake ps)
{
	//头插法
	ps->_pFood->next = ps->_pSnake;
	ps->_pSnake = ps->_pFood;

	//释放下一个位置的节点
	free(pn);
	pn = NULL;

	pSnakeNode cur = ps->_pSnake;
	//打印蛇
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	ps->_totalScore += ps->_foodWeight;

	//重新创建食物
	CreateFood(ps);
}


void NotFood(pSnakeNode pn, pSnake ps)
{
	//头插法
	pn->next = ps->_pSnake;
	ps->_pSnake = pn;

	pSnakeNode cur = ps->_pSnake;
	while (cur->next->next != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}

	//把最后一个结点打印成空格
	SetPos(cur->next->x, cur->next->y);
	printf("  ");

	//释放最后一个结点
	free(cur->next);

	//把倒数第二个节点的地址置为NULL
	cur->next = NULL;
}

// 蛇撞墙而死
void KillByWall(pSnake ps) {
	if (ps->_pSnake->x == 0 || ps->_pSnake->x == 56 
		|| ps->_pSnake->y == 0 || ps->_pSnake->y == 26)
	{
		ps->_status = KILl_BY_WALL;
	}
}

// 蛇撞自己而死
void KillBySelf(pSnake ps) {
	pSnakeNode cur = ps->_pSnake->next;

	while (cur)
	{
		if (cur->x == ps->_pSnake->x && cur->y == ps->_pSnake->y)
		{
			ps->_status = KILL_BY_SELF;
			return;
		}
		cur = cur->next;
	}
	return;
}

// 蛇走一步
void SnakeMove(pSnake ps)
{
	//创建一个结点，表示蛇即将到的下一个节点
	pSnakeNode pNextNode = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pNextNode == NULL)
	{
		perror("SnakeMove()::malloc()");
		return;
	}

	switch (ps->_dir)
	{
	case UP:
		pNextNode->x = ps->_pSnake->x;
		pNextNode->y = ps->_pSnake->y - 1;
		break;
	case DOWN:
		pNextNode->x = ps->_pSnake->x;
		pNextNode->y = ps->_pSnake->y + 1;
		break;
	case LEFT:
		pNextNode->x = ps->_pSnake->x - 2;
		pNextNode->y = ps->_pSnake->y;
		break;
	case RIGHT:
		pNextNode->x = ps->_pSnake->x + 2;
		pNextNode->y = ps->_pSnake->y;
		break;
	}

	//检测下一个坐标处是否是食物
	if (IsNextFood(pNextNode, ps))
	{
		EatFood(pNextNode, ps);
	}
	else
	{
		NotFood(pNextNode, ps);
	}

	// 蛇撞墙而死
	KillByWall(ps);

	// 蛇撞自己而死
	KillBySelf(ps);
}

void GameRun(pSnake ps)
{
	//打印帮助信息
	PrintHelpInfo();
	do
	{
		//打印总分数和食物的分值
		SetPos(64, 10);
		printf("总分数:%d\n", ps->_totalScore);
		SetPos(64, 11);
		printf("目标分数:%d\n", ps->_targetScore);
		SetPos(64, 12);
		printf("当前食物的分数:%2d\n", ps->_foodWeight);

		if (KEY_PRESS(VK_UP) && ps->_dir != DOWN)
		{
			ps->_dir = UP;
		}
		else if (KEY_PRESS(VK_DOWN) && ps->_dir != UP)
		{
			ps->_dir = DOWN;
		}
		else if (KEY_PRESS(VK_LEFT) && ps->_dir != RIGHT)
		{
			ps->_dir = LEFT;
		}
		else if (KEY_PRESS(VK_RIGHT) && ps->_dir != LEFT)
		{
			ps->_dir = RIGHT;
		}
		else if (KEY_PRESS(VK_SPACE))
		{
			Pause();
		}
		else if (KEY_PRESS(VK_ESCAPE))
		{
			//正常退出游戏
			ps->_status = END_NORMAL;
		}
		else if (KEY_PRESS(VK_F3))
		{
			//加速
			if (ps->_sleepSpeed > 50)
			{
				ps->_sleepSpeed -= 30;
				ps->_foodWeight += 2;
			}
		}
		else if (KEY_PRESS(VK_F4))
		{
			//减速
			if (ps->_foodWeight > 2)
			{
				ps->_sleepSpeed += 30;
				ps->_foodWeight -= 2;
			}
		}

		SnakeMove(ps);//蛇走一步的过程

		// 判断是否到达目标分数
		if (ps->_totalScore >= ps->_targetScore)
		{
			ps->_status = END_BY_WIN;
		}

		Sleep(ps->_sleepSpeed);

	} while (ps->_status == OK);
	system("cls");
}

// 结束游戏（善后处理）
void GameEnd(pSnake ps) {
	SetPos(40, 14);
	switch (ps->_status)
	{
	case END_NORMAL:
		printf("您已正常退出游戏\n");
		break;
	case KILl_BY_WALL:
		printf("您因为撞墙而死\n");
		SetPos(40, 15);
		printf("不甘心吗？那就再开一把！\n");
		break;
	case KILL_BY_SELF:
		printf("您因为撞到自己而死\n");
		SetPos(40, 15);
		printf("不甘心吗？那就再开一把！\n");
		break;
	case END_BY_WIN:
		SetPos(40, 15);
		printf("恭喜你！赢得游戏！\n");
		break;
	}

	// 释放贪吃蛇和食物
	pSnakeNode cur = ps->_pSnake;
	while (cur)
	{
		pSnakeNode del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	if (ps->_pFood)
	{
		free(ps->_pFood);
		ps->_pFood = NULL;
	}
}