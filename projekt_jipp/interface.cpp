#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mess.h"
#include "interface.h"

static const char* interface_arr[] = {
	"PUSH   -  0",
	"POP    -  1",
	"FIND   -  2",
	"SAVE   -  3",
	"LOAD   -  4",
	"CLEAR  -  5",
	"END    -  6"
};

void menu()
{
	size_t i;
	for (i = 0; i < INTERFACE_TOTAL; ++i)
	{
		printf("%s\n", interface_arr[i]);
	}
}

void push()
{
	printf("PUSH\n");
}

void pop()
{
	printf("POP\n");
}

void find()
{
	printf("FIND\n");
}

void save()
{
	printf("SAVE\n");
}

void load()
{
	printf("LOAD\n");
}

void clear()
{
	printf("CLEAR\n");
}