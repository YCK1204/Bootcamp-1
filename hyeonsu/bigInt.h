#define MAX_DIGIT_NUMBER 100

typedef struct {
	char digits[MAX_DIGIT_NUMBER + 1];
}BIGINT;


void BIGINT_InitBigInt(BIGINT* bi);
void BIGINT_StringToBigInt(BIGINT* bi, char* str);
void BIGINT_BigIntToString(BIGINT* bi, char* str);
void  BIGINT_ToTenComplement(BIGINT* bi);
void  BIGINT_FromTenComplement(BIGINT* bi);
BIGINT* BIGINT_Add(BIGINT* result, BIGINT* lhs, BIGINT* rhs);
BIGINT* BIGINT_Sub(BIGINT* result, BIGINT* lhs, BIGINT* rhs);
int BIGINT_IsNegative(BIGINT* bigNum);