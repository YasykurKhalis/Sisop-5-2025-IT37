#include "../include/shell.h"
#include "../include/kernel.h"

int cursor_row = 0;
int cursor_col = 0;

unsigned char current_color = 0x0F;  // Putih di latar hitam (default VGA)

void main() {
  clearScreen();
  shell();
  while (1); // biar tidak langsung keluar
}

void setColor(unsigned char color) {
  current_color = color;
}

void setCursor(int row, int col) {
  cursor_row = row;
  cursor_col = col;
}

void updateCursor() {
  int dx = (cursor_row << 8) | cursor_col;
  interrupt(0x10, 0x0200, 0, 0, dx); // panggil BIOS untuk update posisi kursor
}

void printCharAt(char c, int row, int col) { // cetak karakter pada posisi tertentu
  int offset = (row * 80 + col) * 2; // 2 byte per karakter 1 untuk karakter 1 untuk warna
  putInMemory(0xB800, offset, c);
  putInMemory(0xB800, offset + 1, current_color);
}

void printString(char *str) {
  //TODO: Implementasi fungsi untuk mencetak string
  while (*str) {
    if (*str == '\n') {
      cursor_row++;
      cursor_col = 0;
    } else {
      printCharAt(*str, cursor_row, cursor_col);
      cursor_col++;
      if (cursor_col >= 80) {
        cursor_col = 0;
        cursor_row++;
      }
    }
    str++;
  }
  updateCursor();
}

void readString(char *buf) {
  //TODO: Implementasi fungsi untuk membaca string
  int i = 0;
  char c;
  char temp[2];
  
  while (1) {
    c = interrupt(0x16, 0, 0, 0, 0); // baca karakter keyboard
    if (c == '\r') { // Enter
      break;
    } else if (c == '\b' && i > 0) { // Backspace
      i--;
      cursor_col--;
      if (cursor_col < 0) {
        if (cursor_row > 0) {
          cursor_row--;
          cursor_col = 79; // pindah ke akhir baris sebelumnya
        } else {
          cursor_col = 0;
        }
      }
      printCharAt(' ', cursor_row, cursor_col);
    } else if (c >= ' ' && i < 127) { // karakter printable
      buf[i] = c;
      i++;
      temp[0] = c;
      temp[1] = '\0';
      printString(temp);
    }
    updateCursor();
  }
  buf[i] = '\0';
  printString("\n");
  updateCursor();
}

void clearScreen()
{
  //TODO: Implementasi fungsi untuk membersihkan layar
  int i, j;
  for (i = 0; i < 25; i++) {
    for (j = 0; j < 80; j++) {
      putInMemory(0xB800, (i * 80 + j) * 2, ' ');
      putInMemory(0xB800, (i * 80 + j) * 2 + 1, 0x07);
    }
  }
  cursor_row = 0;
  cursor_col = 0;
  updateCursor();
}

