#include<stdio.h>
#include<stdlib.h>
int main()
{
	char* name = (char*)malloc(sizeof(char)*4);
	sprintf(name, "%s", "xxxx");
	printf("name = %s\n", name);
}
