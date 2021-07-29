#include "stdio.h"

struct non_locals {
	int count;
	int * y;
};

int f(int x , int* non_locals);

int main() {
	int y = 5;
	struct non_locals n = { 1, &y };
	f(5, &n);	
}

int f(int x, int* non_locals) {
	struct non_locals* nl = (struct non_locals*)non_locals;
	return x + *nl->y;
}

