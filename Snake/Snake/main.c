#define _CRT_SECURE_NO_WARNINGS 1

#include "Snake.h"

void test() {
    system("color 0a");
    char ch;
    do
    {
        system("cls");
        // 创建贪吃蛇
        Snake snake = { 0 };
        // 初始化游戏
        GameStart(&snake);
        // 运行游戏
        GameRun(&snake);
        // 结束游戏 (善后处理)
        GameEnd(&snake);
        SetPos(40, 16);
        printf("还要再来一把吗？\n");
        SetPos(40, 17);
        printf("输入Y/y继续游戏，输入N/n结束游戏：");
        ch = getchar();
        while (getchar() != '\n');
    } while (ch == 'Y' || ch == 'y');
    SetPos(0, 28);
}

int main()
{
    // 设置适配本地环境
    setlocale(LC_ALL, "");

    // 创建时间错
    srand((unsigned int)time(NULL));

    test();

    return 0;
}
