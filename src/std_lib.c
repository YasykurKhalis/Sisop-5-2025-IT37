#include "../include/std_lib.h"

int my_div(int a, int b)
{
  //TODO: Implementasi pembagian
  //NOTE: HARUS BISA ANGKA NEGATIF
  int neg = 0;
  int res = 0;
  if (a < 0) { a = -a; neg = !neg; }
  if (b < 0) { b = -b; neg = !neg; }

  while (a >= b) {
    a -= b;
    res++;
  }

  return neg ? -res : res;
}

int my_mod(int a, int b)
{
  //TODO: Implementasi modulus
  int r = a - my_div(a, b) * b;
  if (r < 0) r += b;
  return r;
}

bool strcmp(char *str1, char *str2) {
  //TODO: Implementasi perbandingan string
  while (*str1 && *str2) {
    if (*str1 != *str2) return false;
    str1++;
    str2++;
  }
  return *str1 == *str2;
}

void strcpy(char *dst, char *src)
{
  //TODO: Implementasi penyalinan string
  while (*src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
}

void clear(byte *buf, unsigned int size)
{
  //TODO: Implementasi pembersihan buffer
  int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num)
{
  //TODO: Implementasi konversi string ke integer
  //NOTE: HARUS BISA ANGKA NEGATIF
  int sign = 1;
  *num = 0;

  if (*str == '-') {
    sign = -1;
    str++;
  }

  while (*str >= '0' && *str <= '9') {
    *num = *num * 10 + (*str - '0');
    str++;
  }

  *num *= sign;
}

void itoa(int num, char *str)
{
  //TODO: Implementasi konversi integer ke string
  //NOTE: HARUS BISA ANGKA NEGATIF
  int i = 0, isNegative = 0;
  int start, end;
  char tmp;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    str[i++] = my_mod(num, 10) + '0';
    num = my_div(num, 10);
  }

  if (isNegative)
    str[i++] = '-';

  str[i] = '\0';

  // Reverse string
  start = 0;
  end = i - 1;
  while (start < end) {
    tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    start++;
    end--;
  }
}

void strcat(char *dest, char *src) {
  while (*dest) dest++;         // Pindah ke akhir string dest
  while (*src) {
    *dest = *src;               // Salin src ke dest
    dest++;
    src++;
  }
  *dest = '\0';                 // Akhiri dengan null terminator
}