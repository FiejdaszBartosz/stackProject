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
	"SHOW   -  2",
	"FIND   -  3",
	"SAVE   -  4",
	"LOAD   -  5",
	"CLEAR  -  6",
	"END    -  7"
};

static const char* degree[] = {
	"0 - INFORMATYKA",
	"1 - MATEMATYKA",
	"2 - FIZYKA",
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

	printf("Podaj nastepujace dane studenta:\n\n");
	printf("Nazwisko:\n");
	scanf("%s", surname);
	printf("\nKierunek:\n");
	show_course();
	scanf("%d", &course);
	printf("\nRok urodzenia:\n");
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

void show()
{
	STACK_show();
}

void show_course()
{
	for (size_t i = 0; i < COURSE_TOTAL; i++)
	{
		printf("%s\n", degree[i]);
	}
}

void find()
{
	int choice;

	printf("Podaj kryterium wyszukiwania:\n0 - NAZWISKO\n1 - KIERUNEK\n2 - ROK URODZENIA\n");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 0: find_surname();
		break;
	case 1: find_course();
		break;
	case 2: find_birth_year();
		break;

	default: mess_fun(MESS_CHOICE_WARN);
		break;
	}

}

void find_surname()
{
	STUDENT* data_to_search = (STUDENT*)malloc(sizeof(STUDENT));
	memset(data_to_search, 0, sizeof(STUDENT));
	if (!data_to_search)
		mess_fun(MESS_MEM_ALOC_ERROR);

	void* ptr_data;

	char str[128];
	printf("Podaj nazwisko: ");
	scanf("%s", str);

	data_to_search->surname = (char*)malloc(sizeof(str) / sizeof(char));
	if (!data_to_search->surname)
		mess_fun(MESS_MEM_ALOC_ERROR);

	strcpy(data_to_search->surname, str);

	ptr_data = STACK_serch(data_to_search, STUDENT_search_surname, 1);

	if (ptr_data)
	{
		printf("\nZnaleziono: \n");
		STUDENT_print(ptr_data);
	}
	else
		printf("Nie znaleziono!");

	while (ptr_data)
	{
		ptr_data = STACK_serch(data_to_search, STUDENT_search_surname, 0);
		if (ptr_data)
			STUDENT_print(ptr_data);
	}

	if (data_to_search->surname)
	{
		free(data_to_search->surname);
		data_to_search->surname = NULL;
	}

	if (data_to_search)
	{
		free(data_to_search);
		data_to_search = NULL;
	}
}

void find_course()
{
	STUDENT* data_to_search = (STUDENT*)malloc(sizeof(STUDENT));
	memset(data_to_search, 0, sizeof(STUDENT));
	if (!data_to_search)
		mess_fun(MESS_MEM_ALOC_ERROR);

	void* ptr_data;
	int serch_course;

	printf("Wprowadz kierunek ktorego szukasz\n0 - INFORMATYKA\n1 - MATEMATYKA\n2 - FIZYKA\n");
	scanf_s("%d", &serch_course);

	switch (serch_course)
	{
	case 0: data_to_search->course = INFORMATYKA;
		break;
	case 1: data_to_search->course = MATEMATYKA;
		break;
	case 2: data_to_search->course = FIZYKA;
		break;
	default: mess_fun(MESS_CHOICE_WARN);
	}

	ptr_data = STACK_serch(data_to_search, STUDENT_search_course, 1);

	if (ptr_data)
	{
		printf("\nZnaleziono: \n");
		STUDENT_print(ptr_data);
	}
	else
		printf("Nie znaleziono!");

	while (ptr_data)
	{
		ptr_data = STACK_serch(data_to_search, STUDENT_search_course, 0);
		if (ptr_data)
			STUDENT_print(ptr_data);
	}

	if (data_to_search->surname)
	{
		free(data_to_search->surname);
		data_to_search->surname = NULL;
	}

	if (data_to_search)
	{
		free(data_to_search);
		data_to_search = NULL;
	}
}

void find_birth_year()
{
	STUDENT* data_to_search = (STUDENT*)malloc(sizeof(STUDENT));
	memset(data_to_search, 0, sizeof(STUDENT));
	if (!data_to_search)
		mess_fun(MESS_MEM_ALOC_ERROR);

	void* ptr_data;
	int year;

	printf("Podaj rok urodzenia: ");
	scanf_s("%d", &year);

	data_to_search->birth_year = year;

	ptr_data = STACK_serch(data_to_search, STUDENT_search_birth_year, 1);

	if (ptr_data)
	{
		printf("\nZnaleziono: \n");
		STUDENT_print(ptr_data);
	}
	else
		printf("Nie znaleziono!");

	while (ptr_data)
	{
		ptr_data = STACK_serch(data_to_search, STUDENT_search_birth_year, 0);
		if (ptr_data)
			STUDENT_print(ptr_data);
	}

	if (data_to_search->surname)
	{
		free(data_to_search->surname);
		data_to_search->surname = NULL;
	}

	if (data_to_search)
	{
		free(data_to_search);
		data_to_search = NULL;
	}
}

void save()
{
	if (!STACK_save(STUDENT_save))
		mess_fun(MESS_FILE_OPEN_ERROR);
}

void load()
{
	if(!STACK_load(*STUDENT_load))
		mess_fun(MESS_FILE_OPEN_ERROR);
}

void clear()
{
	STACK_free();
}