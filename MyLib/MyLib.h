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

#endif