#include "libs.c"

int vuln() {
  char test[100] = {0};
  puts("Hello, the target of this challenge is to execute /bin/sh");
  puts("\nEnter something: ");
  gets(test);
  puts("Hello! You have entered: \n");
  puts(test);
  return 0;
}

int _start(int argc, char* argv[]) {
  vuln();
  exit(0);
}