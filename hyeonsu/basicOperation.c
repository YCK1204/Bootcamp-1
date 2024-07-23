#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "basicOperation.h"
#include "bigInt.h"





char* Add(char* lhs, char* rhs) // 처음 ~ 공백이 나올때 까지: 해당 포인터의 num값
 { // 버그 아직 못잡음
	char* pszResult = (BIGINT*)calloc(1, sizeof(BIGINT));
	BIGINT result;
	BIGINT_InitBigInt(&result);

	BIGINT bigLhs;
	BIGINT bigRhs;
	BIGINT_StringToBigInt(&bigLhs, lhs);
	BIGINT_StringToBigInt(&bigRhs, rhs);
	BIGINT_Add(&result, &bigLhs, &bigRhs);
	BIGINT_BigIntToString(&result, pszResult);
	
	return pszResult;
}
char* Sub(char* lhs, char* rhs)
{ 
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));

	BIGINT result;
	BIGINT_InitBigInt(&result);

	BIGINT bigLhs;
	BIGINT bigRhs;
	BIGINT_StringToBigInt(&bigLhs, lhs);
	BIGINT_StringToBigInt(&bigRhs, rhs);
	BIGINT_Sub(&result, &bigLhs, &bigRhs);
	BIGINT_BigIntToString(&result, pszResult);

	return pszResult;
}
char* Mul(char* lhs, const char* rhs)
{
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));

	return pszResult;
}
char* Div(const char* lhs, const char* rhs, char* remain) // 나눗셈이 여러번이라 나머지가 여러개인 경우: 나머지 합산
{
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));

	
	return pszResult;
}

void ReverseString(char* pszTarget)
{

	int lenTarget = 0;
	while (pszTarget[lenTarget] != '\0') {
		lenTarget++;
	}
	char tmp;
	for (int i = 0; i < lenTarget / 2; ++i) {
		tmp = pszTarget[i];
		pszTarget[i] = pszTarget[lenTarget - i - 1];
		pszTarget[lenTarget - i - 1] = tmp;
	}
}
