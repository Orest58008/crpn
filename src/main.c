#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Binary operators
#define BINARY_COUNT 5
float add (float a, float b) { return a + b; }
float sub (float a, float b) { return a - b; }
float mul (float a, float b) { return a * b; }
float quo (float a, float b) { return a / b; }

typedef float (*binary)(float, float);
char  *binary_names[BINARY_COUNT] = { "+",  "-",  "x",  "/",  "xx"  };
binary binary_funcs[BINARY_COUNT] = { &add, &sub, &mul, &quo, &powf };

// Unary operators
#define UNARY_COUNT 3

typedef double (*unary)(double);
char *unary_names[UNARY_COUNT] = { "sin", "cos", "tan" };
unary unary_funcs[UNARY_COUNT] = { &sin,  &cos,  &tan  };

// A function to check if string is representing a zero
int is_zero(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
	if (str[i] != '0' && str[i] != '.') {
	  return 0;
	}
  }

  return 1;
}


int main(int argc, char **argv) {
  float stack[argc];
  short head = 0; // Head is the position of next element to be, not the last one, ktim

  for (short i = 1; i < argc; i++) {
	char *arg = argv[i];
	
	if (atof(arg) != 0) {
	  stack[head] = atof(arg); head++;
	} else if (is_zero(arg)) { // Check if arg is 0
	  stack[head] = 0;         head++;
	} else {
	  short flag = 0;

	  // Check if arg is a binary operator
	  for (short j = 0; j < BINARY_COUNT; j++) {
		if (!strcmp(binary_names[j], arg)) {
		  if (head < 2) {
			fprintf(stderr, "Provide more arguments!\n"); return 1;
		  }
		  
		  head -= 2;
		  stack[head] = binary_funcs[j](stack[head], stack[head + 1]);
		  head++;

		  flag = 1;
		  break;
		}
	  }

	  // Check if arg is an unary operator
	  for (short j = 0; j < UNARY_COUNT; j++) {
		if (!strcmp(unary_names[j], arg)) {
		  if (head < 1) {
			fprintf(stderr, "Provide more arguments!\n"); return 1;
		  }

		  head--;
		  stack[head] = unary_funcs[j](stack[head]);
		  head++;

		  flag = 1;
		  break;
		}
	  }

	  if (!flag) {
		fprintf(stderr, "Invalid operator `%s`!\n", arg); return 1;
	  }
	}
  }

  if (head > 1) {
	fprintf(stderr, "Too many arguments!\n"); return 1;
  }

  printf("%G\n", stack[head - 1]);
  return 0;
}
