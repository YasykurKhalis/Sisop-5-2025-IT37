#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#include "std_type.h"

int my_div(int a, int b);
int my_mod(int a, int b);

bool strcmp(char *str1, char *str2);
void strcpy(char *dst, char *src);
void strcat(char *dest, char *src);

void clear(byte *buf, unsigned int size);

void atoi(char *str, int *num);
void itoa(int num, char *str);

#endif // __STD_LIB_H__
