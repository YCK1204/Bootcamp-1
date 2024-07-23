#include <string.h>
#include <ctype.h>

#include "bigInt.h"


void BIGINT_InitBigInt(BIGINT* bi)
{
	for (int i = 0; i < MAX_DIGIT_NUMBER; ++i) {
		bi->digits[i] = '0';
	}
	bi->digits[MAX_DIGIT_NUMBER] = '\0';
}

void BIGINT_StringToBigInt(BIGINT* bi, char* str)
{
	if (str == NULL)
		return;
	BIGINT_InitBigInt(bi);
	int cntBi = MAX_DIGIT_NUMBER-1;
	int flag = 0;
	if (str[0] == '+')
		str = str + 1;
	if (str[0] == '-') {
		str = str + 1; 
		flag = !flag;
	}
	for (int i = strlen(str)-1; i >= 0; --i) {
		bi->digits[cntBi] = str[i];
		cntBi--;
	}
	if (flag)
		BIGINT_ToTenComplement(bi);
}

void BIGINT_BigIntToString(BIGINT* bi, char* str)
{
	int cntStr;
	int flag = 0;
	if (BIGINT_IsNegative(bi)) {
		str[0] = '-';
		flag = !flag;
		BIGINT_FromTenComplement(bi);
	}
	int endBi;
	for (endBi= 0; endBi < MAX_DIGIT_NUMBER - 1; ++endBi) {
		if (bi->digits[endBi] != '0') {
			break;
		}
	}
	cntStr = MAX_DIGIT_NUMBER - endBi - 1;
	if (flag)
		cntStr++;

	for (int i = MAX_DIGIT_NUMBER-1; i >= endBi; --i) {
		str[cntStr--] = bi->digits[i];
	}
}

void BIGINT_ToTenComplement(BIGINT* bi) // 10의 보수 취하기
{
	BIGINT one;
	BIGINT_StringToBigInt(&one, "1");
	for (int i = 0; i < MAX_DIGIT_NUMBER; ++i) {
		bi->digits[i] = '9' - bi->digits[i] + '0';
	}
	BIGINT_Add(bi->digits, bi->digits, &one);
}
void  BIGINT_FromTenComplement(BIGINT* bi)
{
	BIGINT one;
	BIGINT_StringToBigInt(&one, "-1");
	BIGINT_Add(bi->digits, bi->digits, &one);
	for (int i = 0; i < MAX_DIGIT_NUMBER; ++i) {
		bi->digits[i] = '9' - bi->digits[i] + '0';
	}
}

BIGINT* BIGINT_Add(BIGINT* result, BIGINT* lhs, BIGINT* rhs) 
{
	int carry = 0;
	char tmp;
	for (int i = MAX_DIGIT_NUMBER-1; i >= 0; --i) {
		tmp = lhs->digits[i] - '0' + rhs->digits[i] + carry;
		carry = 0;
		if (!isdigit(tmp)) {
			tmp -= 10;
			carry = 1;	
		}
		result->digits[i] = tmp;
	}
	return result;
}

BIGINT* BIGINT_Sub(BIGINT* result, BIGINT* lhs, BIGINT* rhs)
{
	if (BIGINT_IsNegative(rhs)) {
		BIGINT_FromTenComplement(rhs);
	}
	else {
		BIGINT_ToTenComplement(rhs);
	}
	BIGINT_Add(result, lhs, rhs);
	return result;
}
int BIGINT_IsNegative(BIGINT* bigNum)
{
	if (bigNum->digits[0] == '9')
		return 1;
	return 0;
}