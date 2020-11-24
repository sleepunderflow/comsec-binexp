#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void vuln() {
  char name[50] = {0};
  puts("What is your name?");
  gets(name);
  }

int main(int argc, char* argv[]) {
  vuln();
  return 0;
}
