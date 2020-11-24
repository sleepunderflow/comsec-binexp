#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>



void get_input(char* output) {
  char input[500];
  printf("Hello, enter your input (temporarely stored to %018p, copied to %018p):\n", input, output);
  read(0, input, 490);
  strcpy(output, input);
}

void vuln() {
  char text[50];
  get_input(text);
  return;
}


int main(int argc, char* argv[]) {
  printf("Address of system: %018p\n", system);
  int var = 0;
  vuln();
  return 0;
}