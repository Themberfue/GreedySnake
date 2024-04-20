#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

// �߳�ʼ����
#define POS_X 24
#define POS_Y 5

// ����
#define WALL L'��'
#define BODY  L'��'
#define FOOD L'��'

// ��ϢĬ��ֵ
#define TOTALSCORE 0 // �ܷ�
#define FOODWEIGHT 10 // ÿ��ʳ��ķ���
#define SLEEPSPEED 200 // ��Ϸ�ٶ�
#define TARGETSCORE 200 // Ŀ�����

// �ж���Ӧ�ļ��Ƿ��¡�
#define KEY_PRESS(vk)  ((GetAsyncKeyState(vk)&1)?1:0)

// ���˶��ķ���
typedef enum DIRCTION {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
}DIRCTION;

typedef enum GAME_STATUS
{
	OK, // ��������
	KILl_BY_WALL, // ײǽ����
	KILL_BY_SELF, // ײ�Լ�����
	END_NORMAL, // �����˳�
	END_BY_WIN // Ӯ����Ϸ
} GAME_STATUS;

typedef struct SnakeNode
{
	// ����
	int x;
	int y;
	// ָ����һ���ڵ��ָ��
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;

// ̰����
typedef struct Snake
{
	pSnakeNode _pSnake; // ָ����ͷ��ָ��
	pSnakeNode _pFood; // ָ��ʳ���ָ��
	DIRCTION _dir; // ���˶��ķ���
	GAME_STATUS _status; // ��Ϸ��״̬
	int _foodWeight; // һ��ʳ��ķ���
	int _totalScore; // �ܳɼ�
	int _sleepSpeed; // ��Ϸ�ٶ�
	int _targetScore; // Ŀ�����
} Snake, * pSnake;

// ��λ���
void SetPos(short x, short y);

// ��Ϸ��ʼ
void GameStart(pSnake ps);

// ��ӭ����
void WelcomeToGame();

// ������Ϸ��ͼ
void CreateMap();

// ������
void InitSnake(pSnake ps);

// ����ʳ��
void CreateFood(pSnake ps);

// ������Ϸ
void GameRun(pSnake ps);

// ����һ��
void SnakeMove(pSnake ps);

// ��һ���ڵ��Ƿ���ʳ��
int IsNextFood(pSnakeNode pn, pSnake ps);

// ��ʳ��
void EatFood(pSnakeNode pn, pSnake ps);

// ����ʳ��
void NotFood(pSnakeNode pn, pSnake ps);

// ��ײǽ����
void KillByWall(pSnake ps);

// ��ײ�Լ�����
void KillBySelf(pSnake ps);

// ������Ϸ���ƺ���
void GameEnd(pSnake ps);
