#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "basicOperation.h"
#include "calculation.h"



void RemoveSpace(char* pszInput)
{
	char* pszOutput = pszInput;
	while (*pszInput != '\0') {
		if (*pszInput != ' ') {
			*pszOutput = *pszInput;
			pszOutput++;
		}
		pszInput++;
	}
	*pszOutput = '\0';
}


int Priority(char operator)
{
	if (operator == '+' || operator == '-')
		return 1;
	else if (operator == '*' || operator == '/')
		return 2;
	else if (operator =='(' || operator == ')')
		return 0;
	else
		return -1;

}


int CheckBracket(const char* const infix)
{
	int cntBracket = 0;
	for (int i = 0; i < strlen(infix); ++i) {
		if (infix[i] == '(') {
			cntBracket++;
		}
		else if (infix[i] == ')') {
			cntBracket--;
		}
	}

	if (cntBracket != 0)
		return 0;

	return 1;
}


int InfixToPostfix(const char* const infix, char* const postfix)
{
	Stack s;
	StackInit(&s);
	int cntIn = 0;
	int cntPost = 0;
	int priority = 0;
	int tmp = 0;


	while (infix[cntIn] != '\0') {
		if (isdigit(infix[cntIn])) {
 			postfix[cntPost++] = infix[cntIn];
			while(isdigit(infix[cntIn+1]))
				postfix[cntPost++] = infix[++cntIn];
			postfix[cntPost++] = ' ';
		}
		else {
			priority = Priority(infix[cntIn]); 
			if (priority == -1)
				return -1;
			else if (infix[cntIn] == '(') {
				StackPush(&s, infix[cntIn]);
			}
			else if (infix[cntIn] == ')') {
				while (StackPeek(&s) != '(') {
					postfix[cntPost++] = StackPop(&s);
				}
				StackPop(&s); // '(' ������
			}
			else {
				if(!StackIsEmpty(&s) && StackPeek(&s) == '(')
					StackPush(&s, infix[cntIn]);
				else if (priority == 1 && (cntIn == 0 || !isdigit(infix[cntIn - 1]))) { // ���� ���� ó��
					postfix[cntPost++] = ' '; // ���� ���� ����
					postfix[cntPost++] = infix[cntIn++];
					if (isdigit(infix[cntIn])) {
						postfix[cntPost++] = infix[cntIn];
						while (isdigit(infix[cntIn + 1]))
							postfix[cntPost++] = infix[++cntIn];
						postfix[cntPost++] = ' ';
					}
				}
				else {
					while (!StackIsEmpty(&s) && priority <= Priority(StackPeek(&s))) {
						postfix[cntPost++] = StackPop(&s);
					}
					StackPush(&s, infix[cntIn]);
				}
			}
		}
		cntIn++;
	}
	while (!StackIsEmpty(&s)) {
		postfix[cntPost++] = StackPop(&s);
	}
	return 1;
}

char* CalculatePostfix(char* postfix, char* remain)
{
	PszStack s;
	PszStackInit(&s);
	int cntPost = 0;
	char* lhs = NULL;
	char* rhs = NULL;
	int flag = 0;

	char* heapPtr[100] = { 0 };
	size_t cntHeapPtr = 0;

	while (postfix[cntPost] != '\0') {
		
		if (postfix[cntPost] == ' ' || isdigit(postfix[cntPost])) {
			int cntTmp = 0;

			if (postfix[cntPost] == ' ') { // ���� ���� ó��
				cntPost++;
			}
			ReverseStringWithEndSpace(postfix + cntPost);			// Reverse�ؼ� ������ �����ϱ� ����
			PszStackPush(&s, (char*)(postfix+cntPost)); // int�� ���� ��� char* ���� ��� (�ſ� ū ���� ���ڿ��� �ٷ�� ����)

			while (postfix[cntPost] != ' ') {
				cntPost++;
			}
			postfix[cntPost] = '\0';
		}
		else {
			rhs = PszStackPop(&s);
			lhs = PszStackPop(&s);
			switch (postfix[cntPost]) {
			case '+':
				heapPtr[cntHeapPtr] = Add(lhs, rhs);
				PszStackPush(&s, heapPtr[cntHeapPtr++]);
				break;
			case '-':
				heapPtr[cntHeapPtr] = Sub(lhs, rhs);
				PszStackPush(&s, heapPtr[cntHeapPtr++]);
				break;
			case '*':
				heapPtr[cntHeapPtr] = Mul(lhs, rhs);
				PszStackPush(&s, heapPtr[cntHeapPtr++]);
				break;
			case '/':
				heapPtr[cntHeapPtr] = Div(lhs, rhs, remain);
				flag = 1;
				PszStackPush(&s, heapPtr[cntHeapPtr++]);
				break;
			}
		}
		cntPost++;
	}
	if (flag == 0)
		*remain = -1; // ������ ������ ���� ������ ������ ��� x
	if (cntHeapPtr == 0) {
		char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));
		for (int i = 0; postfix[i] != '\0'; ++i) {
			pszResult[i] = postfix[i];
		}
		return pszResult;
	}
	for (int i = 0; i < cntHeapPtr-1; ++i) { // ������ ���� ���� �Ҵ� ���� ����
		free(heapPtr[i]);
	}
	return heapPtr[cntHeapPtr-1];
}

void ReverseStringWithEndSpace(char* pszTarget)
{

	int lenTarget = 0;
	while (pszTarget[lenTarget] != ' ') {
		lenTarget++;
	}
	char tmp;
	for (int i = 0; i < lenTarget / 2; ++i) {
		tmp = pszTarget[i];
		pszTarget[i] = pszTarget[lenTarget - i - 1];
		pszTarget[lenTarget - i - 1] = tmp;
	}
}
