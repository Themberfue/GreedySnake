#define _CRT_SECURE_NO_WARNINGS 1

#include "Snake.h"

void test() {
    system("color 0a");
    char ch;
    do
    {
        system("cls");
        // ����̰����
        Snake snake = { 0 };
        // ��ʼ����Ϸ
        GameStart(&snake);
        // ������Ϸ
        GameRun(&snake);
        // ������Ϸ (�ƺ���)
        GameEnd(&snake);
        SetPos(40, 16);
        printf("��Ҫ����һ����\n");
        SetPos(40, 17);
        printf("����Y/y������Ϸ������N/n������Ϸ��");
        ch = getchar();
        while (getchar() != '\n');
    } while (ch == 'Y' || ch == 'y');
    SetPos(0, 28);
}

int main()
{
    // �������䱾�ػ���
    setlocale(LC_ALL, "");

    // ����ʱ���
    srand((unsigned int)time(NULL));

    test();

    return 0;
}
