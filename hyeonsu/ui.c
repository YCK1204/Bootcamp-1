#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "stack.h"
#include "calculation.h"
#include "test.h"
 
int main() {

	EventLoopRun();

	return 0;
}


MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;
	system("cls");
	printf("[1] ��Ģ����\t[0]������\n");
	if (1 != scanf_s("%d%*c", &input)) {
		while (getchar() != '\n');
		return -1;
	}
	return input;
}

void EventLoopRun()
{
	MY_MENU menu = 0;
	while ((menu = PrintMenu()) != 0) {
		switch (menu) {
		case MENU_CALCULATION:
			Calculator();
			break;
		case MENU_EXIT:
			break;
		default:
			continue;
		}
		_getch();
	}
}



void Calculator()
{
	printf("���� �Է��� �ּ���\n");
	char szBuffer[BUFFER_MAX] = { 0 };
	if (1 != scanf_s("%[^\n]s", szBuffer, BUFFER_MAX)) {
		printf("�߸��� �Է°��Դϴ�.\n");
		return;
	}
	RemoveSpace(szBuffer);
	if (!CheckBracket(szBuffer)) {
		printf("��ȣ ¦�� ���� �ʽ��ϴ�.\n");
			return;
	}

	char szPostfix[BUFFER_MAX *2] = { 0 };

	if (-1 == InfixToPostfix(szBuffer, szPostfix)) { 
		printf("�Ŀ��� +-*/()������ ��� �����մϴ�.\n");
		return;
	}
	char* remain = NULL;
	char* result = CalculatePostfix(szPostfix, &remain);
	printf("�����: %s\n", result);
	printf("\n");
}