#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Binary operators
#define BINARY_COUNT 8
int add (int a, int b) { return a + b; }
int sub (int a, int b) { return a - b; }
int mul (int a, int b) { return a * b; }
int quo (int a, int b) { return a / b; }
int and (int a, int b) { return a & b; }
int or  (int a, int b) { return a | b; }
int xor (int a, int b) { return a ^ b; }
int expo(int a, int b) {
  if (b < 0) return 1 / expo(a, b);
  else if (b == 0) return 1;
  else if (b == 1) return a;         // vvv
  else if (b == 2) return a * a;     // It is faster than to use cycles for everything
  else if (b == 3) return a * a * a; // ^^^
  else {
	int result = 1;
	while (b != 0) {
      result *= a;
	  b--;
	}

	return result;
  }
}

typedef int (*binary)(int, int);
char  *binary_names[BINARY_COUNT] = { "+",  "-",  "x",  "/",  "xx",  "and", "or", "xor" };
binary binary_funcs[BINARY_COUNT] = { &add, &sub, &mul, &quo, &expo, &and,  &or,  &xor  };

// Unary operators
#define UNARY_COUNT 1
int neg(int a) { return ~a; }

typedef int (*unary)(int);
char *unary_names[UNARY_COUNT] = { "~"  };
unary unary_funcs[UNARY_COUNT] = { &neg };

int main(int argc, char **argv) {
  int stack[argc];
  short head = 0; // Head is the position of next element to be, not the last one, ktim

  for (short i = 1; i < argc; i++) {
	char *arg = argv[i];

	if (atoi(arg) != 0) {
	  stack[head] = atoi(arg); head++;
	} else if (arg[0] == '0' && arg[1] == '\0') { // Check if arg is 0
	  stack[head] = 0;         head++;
	} else {
	  short flag = 0;

	  // Check if arg is a binary operator
	  for (short j = 0; j < BINARY_COUNT; j++) {
		if (!strcmp(binary_names[j], arg)) {
		  if (head < 2) {
			printf("Provide more arguments!"); return 1;
		  }
		  
		  head -= 2;
		  stack[head] = binary_funcs[j](stack[head], stack[head + 1]);
		  head++;

		  flag = 1;
		}
	  }

	  // Check if arg is an unary operator
	  for (short j = 0; j < UNARY_COUNT; j++) {
		if (!strcmp(unary_names[j], arg)) {
		  if (head < 1) {
			printf("Provide more arguments!"); return 1;
		  }

		  head--;
		  stack[head] = unary_funcs[j](stack[head]);
		  head++;

		  flag = 1;
		}
	  }

	  if (!flag) {
		printf("Invalid operator `%s`!", arg); return 1;
	  }
	}

	if (head > argc / 2) {
	  printf("Too many arguments!"); return 1;
	}
  }

  if (head > 1) {
	printf("Too many arguments!"); return 1;
  }

  printf("%d", stack[head - 1]);
  return 0;
}
