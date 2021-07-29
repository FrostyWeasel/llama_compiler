#include <stdio.h>

int f(void (*g)(int), int x);
void g(int x);

int main()
{
	void (*fun_ptr)(int) = &g(5);
	f(fun_ptr, 5);

	return 0;
}


int f(void (*g)(int), int x){
	g;
	return x;
}
void g(int x) {
	x = x+1;
}
