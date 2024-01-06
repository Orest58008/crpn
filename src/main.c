#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int stack[argc];
  int head = 0;

  for (int i = 1; i < argc; i++) {
	char *arg = argv[i];

	if (arg[0] == '0' && arg[1] == '\0') {
	  stack[head] = 0;
	  head++;
	} else if (arg[0] == '+' && arg[1] == '\0') {
	  if (head < 2) {
		printf("Provide more arguments!");
		exit(EXIT_FAILURE);
	  }

	  int first = stack[head - 2];
	  int second = stack[head - 1];

	  head -= 2;
	  stack[head] = first + second;
	  head++;
	} else if (arg[0] == '-' && arg[1] == '\0') {
	  if (head < 2) {
		printf("Provide more arguments!");
		exit(EXIT_FAILURE);
	  }

	  int first = stack[head - 2];
	  int second = stack[head - 1];

	  head -= 2;
	  stack[head] = first - second;
	  head++;
	} else if (arg[0] == 'x' && arg[1] == '\0') {
	  if (head < 2) {
		printf("Provide more arguments!");
		exit(EXIT_FAILURE);
	  }

	  int first = stack[head - 2];
	  int second = stack[head - 1];

	  head -= 2;
	  stack[head] = first * second;
	  head++;
	} else if (arg[0] == '/' && arg[1] == '\0') {
	  if (head < 2) {
		printf("Provide more arguments!");
		exit(EXIT_FAILURE);
	  }

	  int first = stack[head - 2];
	  int second = stack[head - 1];

	  head -= 2;
	  stack[head] = first / second;
	  head++;
	} else if (atoi(arg) == 0) {
	  printf("Invalid argument!");
	  exit(EXIT_FAILURE);
	} else {
	  stack[head] = atoi(arg);
	  head++;
	}
  }

  printf("%d", stack[head - 1]);
  return 0;
}
