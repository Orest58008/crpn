#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Binary operators
#define BINARY_COUNT 4
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int quo(int a, int b) { return a / b; }
typedef int (*binary)(int, int);

int main(int argc, char **argv) {
  int stack[argc];
  int head = 0; // Head is the position of next element to be, not the last one, ktim
  char *binary_names[BINARY_COUNT] = {"+", "-", "x", "/"};
  binary binary_funcs[BINARY_COUNT] = {&add, &sub, &mul, &quo};

  for (int i = 1; i < argc; i++) {
	char *arg = argv[i];

	if (atoi(arg) != 0) {
	  stack[head] = atoi(arg);
	  head++;
	} else if (arg[0] == '0' && arg[1] == '\0') { // Check if arg is 0
	  stack[head] = 0;
	  head++;
	} else {
	  short flag = 0;

	  // Check if arg is a binary operator
	  for (int j = 0; j < BINARY_COUNT; j++) {
		if (!strcmp(binary_names[j], arg)) {
		  if (head < 2) {
			printf("Provide more arguments!");
			return 1;
		  }
		  
		  head -= 2;
		  stack[head] = binary_funcs[j](stack[head], stack[head + 1]);
		  head++;

		  flag = 1;
		}
	  }

	  if (!flag) {
		printf("Invalid operator `%s`!", arg);
		return 1;
	  }
	}

	if (head > argc / 2) {
	  printf("Too many arguments!");
	  return 1;
	}
  }

  if (head > 1) {
	printf("Too many arguments!");
	return 1;
  }

  printf("%d", stack[head - 1]);
  return 0;
}
