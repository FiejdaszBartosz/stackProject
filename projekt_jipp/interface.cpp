#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mess.h"
#include "data.h"
#include "stack.h"
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
	char surname[512];
	int year;
	
	DEGREE_COURSE course;

	printf("Podaj nastepujace dane studenta:\n");
	printf("Nazisko: ");
	scanf("%s", surname);
	printf("\nKierunek:\n0 - INFORMATYKA\n1 - MATEMATYKA\n2 - FIZYKA\n ");
	scanf("%d", &course);
	printf("\nRok urodzenia: ");
	scanf("%d", &year);

	void* ptr_data = STUDENT_push(surname, year, course);
	if (!STACK_push(ptr_data))
		mess_fun(MESS_PUSH_ERROR);
}

void pop()
{
	STACK temp = STACK_pop();

	STUDENT_print(temp.ptr_element_data);
	STUDENT_free(temp.ptr_element_data);
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