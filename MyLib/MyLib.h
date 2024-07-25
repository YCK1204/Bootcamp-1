#ifndef MYLIB_H
# define MYLIB_H

#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

char* Trim(char* str);
char* _Substr(char* str, size_t start);
char* Substr(char* str, size_t start, size_t count);
char* Getline(int fd);
char** Split(char* str, int delim, bool trim);
char* StrJoin(char* s1, char* s2);
int StrFindByChar(char* str, char target, size_t pos);
int StrFindByString(char* str, char* target, size_t pos);
void ReplaceString(char** oldString, char* newString);
char* IntToAscii(int n);
char* CharToString(char c);
void _InsertString(char** original, size_t pos, char c);
void InsertString(char** original, size_t pos, char* str);
char* MyStrcpy(char* dest, char* src, size_t pos);
char* MyStrncpy(char* dest, char* src, size_t pos, size_t n);

#endif