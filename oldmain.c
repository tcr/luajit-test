#include <stdio.h>

int test (int a, int b)
{
  return a & b;
}
 
int main ()
{
	printf("Hello World: %d\n", test(0xFF, 0x1));
	return 0;
}
