#include "../include/shell.h"
#include "../include/kernel.h"
#include "../include/std_lib.h"

char username[32] = "user";
char base_username[32] = "user";
char grandcompany_suffix[16] = "";

char *valid_commands[] = {"clear", "yo", "gurt", "user", "grandcompany", "add", "sub", "mul", "div", "yogurt"};
int command_count = 10;

int yogurt_counter = 0;

bool is_valid_command(char *input) {
  int i;
  for (i = 0; i < command_count; i++) {
    if (strcmp(input, valid_commands[i]) == true) {
      return true;
    }
  }
  return false;
}

void getFullUsername(char *dest) {
  strcpy(dest, base_username);
  if (grandcompany_suffix[0] != '\0') {
    strcat(dest, "@");
    strcat(dest, grandcompany_suffix);
  }
}

void printPrompt() {
  char full[64];
  getFullUsername(full);
  printString(full);
  printString("> ");
}

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];

  setCursor(0, 0);
  printString("EorzeOS e Youkoso!\n");

  while (true) {
    printPrompt();
    readString(buf);

    clear(cmd, 64);
    clear(arg[0], 64);
    clear(arg[1], 64);
    parseCommand(buf, cmd, arg);

    if (is_valid_command(cmd)) {
      if (strcmp(cmd, "clear") == true) {
        clearScreen();
        setColor(0x0F);
        strcpy(username, base_username);
        grandcompany_suffix[0] = '\0';
      } 
      else if (strcmp(cmd, "yo") == true) {
        printString("gurt\n");
      } 
      else if (strcmp(cmd, "gurt") == true) {
        printString("yo\n");
      } 
      else if (strcmp(cmd, "user") == true) {
        char full[64];
        if (arg[0][0] != '\0') {
          strcpy(base_username, arg[0]);
        } else {
          strcpy(base_username, "user");
        }

        getFullUsername(full);
        printString("Username changed to ");
        printString(full);
        printString("\n");
      }
      else if (strcmp(cmd, "grandcompany") == true) {
        if (strcmp(arg[0], "maelstrom") == true) {
          clearScreen();
          setColor(0x0C);  
          strcpy(grandcompany_suffix, "Storm");
        } else if (strcmp(arg[0], "twinadder") == true) {
          clearScreen();
          setColor(0x0E);
          strcpy(grandcompany_suffix, "Serpent");
        } else if (strcmp(arg[0], "immortalflames") == true) {
          clearScreen();
          setColor(0x09);
          strcpy(grandcompany_suffix, "Flame");
        } else {
          printString("Unknown grand company. Use: maelstrom, twinadder, immortalflames\n");
        }
      }
      else if (strcmp(cmd, "add") == true || strcmp(cmd, "sub") == true ||
        strcmp(cmd, "mul") == true || strcmp(cmd, "div") == true) {

        int a, b, result;
        char resultStr[64];

        atoi(arg[0], &a);
        atoi(arg[1], &b);

        if (strcmp(cmd, "add") == true) {
          result = a + b;
        } else if (strcmp(cmd, "sub") == true) {
          result = a - b;
        } else if (strcmp(cmd, "mul") == true) {
          result = a * b;
        } else if (strcmp(cmd, "div") == true) {
          if (b == 0) {
            printString("Error: Division by zero\n");
            continue;
          }
          result = my_div(a, b);
        }

        itoa(result, resultStr);
        printString(resultStr);
        printString("\n");
      }
      else if (strcmp(cmd, "yogurt") == true) {
        int seed;
        int idx;
        static char *responses[] = {
          "yo",
          "ts unami gng </3",
          "sygau"
        };
        int response_count = 3;

        yogurt_counter++;

        seed = (yogurt_counter * 17) ^ (yogurt_counter << 3);
        idx = my_mod(seed, response_count);
        if (idx < 0) idx += response_count;

        printString("gurt> ");
        printString(responses[idx]);
        printString("\n");
      }
    }
    else {
      printString(buf);
      printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0;

  // Ambil command
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = '\0';

  // Lewati spasi
  if (buf[i] == ' ') i++;

  // Ambil argumen pertama
  while (buf[i] != ' ' && buf[i] != '\0') {
    arg[0][j++] = buf[i++];
  }
  arg[0][j] = '\0';

  // Lewati spasi
  if (buf[i] == ' ') i++;

  // Ambil argumen kedua
  while (buf[i] != '\0') {
    arg[1][k++] = buf[i++];
  }
  arg[1][k] = '\0';
}


// Tambahkan fungsi bila perlu