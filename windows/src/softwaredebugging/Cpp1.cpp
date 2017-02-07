#include<windows.h>

int main(int argc, char *argv[])
{
	_asm INT 3;
	printf("hello int 3\n");
	return(0);
}