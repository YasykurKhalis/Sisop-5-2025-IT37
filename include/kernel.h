#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "std_type.h"

#define COLOR_BLUE          0x1
#define COLOR_RED           0x4
#define COLOR_LIGHT_YELLOW  0xE
#define COLOR_WHITE         0xF

extern void printChar(char c);
extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);

int _start();

void printString(char* str);
void readString(char* buf);
void clearScreen();

#endif // __KERNEL_H__
