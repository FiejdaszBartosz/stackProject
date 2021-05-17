#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "mess.h"

const char* courses[] = {
	"informatyka",
	"matematyka",
	"fizyka"
};

void* STUDENT_init(char* init_surname, int init_year, DEGREE_COURSE init_course)
{
	STUDENT* ptr_data = (STUDENT*)malloc(sizeof(STUDENT));
	if (!ptr_data)
		mess_fun(MESS_MEM_ALOC_ERROR);
	if (ptr_data)
	{
		ptr_data->surname = (char*)malloc((strlen(init_surname) + 1) * sizeof(char));
		if (!ptr_data->surname)
			mess_fun(MESS_MEM_ALOC_ERROR);

		strcpy(ptr_data->surname, init_surname);

		ptr_data->course = init_course;
		ptr_data->birth_year = init_year;
		ptr_data->size = strlen(init_surname);
	}
		
	return (void*)(ptr_data);
}

const char* STUDENT_get_course(enum DEGREE_COURSE course_name)
{
	return courses[course_name];
}

void STUDENT_free(void* ptr)
{
	STUDENT *ptr_data = (STUDENT*)ptr;

	if (ptr_data)
	{
		if (ptr_data->surname)
		{
			free(ptr_data->surname);
			ptr_data->surname = NULL;
		}
		if (ptr_data)
		{
			free(ptr_data);
			ptr_data = NULL;
		}
	}
}

void* STUDENT_push(char* surname, int birth_year, DEGREE_COURSE course)
{
	return STUDENT_init(surname, birth_year, course);
}

void STUDENT_print(void* ptr)
{
	STUDENT* ptr_temp = (STUDENT*)ptr;
	if (ptr_temp)
	{
		printf("nazwisko      : %s\n", ptr_temp->surname);
		printf("kierunek      : %s\n", STUDENT_get_course(ptr_temp->course));
		printf("rok urodzenia : %d\n", ptr_temp->birth_year);
	}
}

int STUDENT_search_surname(void* ptr_current_data, void* ptr_search_data)
{
	STUDENT* ptr_current = (STUDENT*)ptr_current_data;
	STUDENT* ptr_serch = (STUDENT*)ptr_search_data;

	if (strcmp(ptr_current->surname, ptr_serch->surname) == 0)
		return 1;

	return 0;
}

int STUDENT_search_course(void* ptr_current_data, void* ptr_search_data)
{
	STUDENT* ptr_current = (STUDENT*)ptr_current_data;
	STUDENT* ptr_serch = (STUDENT*)ptr_search_data;

	if (ptr_current->course == ptr_serch->course)
		return 1;

	return 0;
}

int STUDENT_search_birth_year(void* ptr_current_data, void* ptr_search_data)
{
	STUDENT* ptr_current = (STUDENT*)ptr_current_data;
	STUDENT* ptr_serch = (STUDENT*)ptr_search_data;

	if (ptr_current->birth_year == ptr_serch->birth_year)
		return 1;

	return 0;
}

bool STUDENT_save(void* ptr_data, FILE* pf)
{
	if (pf && ptr_data)
	{
		STUDENT* temp = (STUDENT*)(ptr_data);
		size_t retval;

		if ((retval = fwrite((const void*)(temp), sizeof(STUDENT), 1, pf)) != 1)
			return false;

		if ((retval = fwrite((const void*)(temp->surname), sizeof(char), temp->size + 1, pf)) != temp->size + 1)
			return false;

		return true;
	}
	else
		return false;
}

bool STUDENT_load(void** ptr_data, FILE* pf)
{
	if (pf)
	{
		STUDENT* temp = (STUDENT*)malloc(sizeof(STUDENT));
		if (!temp)
		{
			mess_fun(MESS_MEM_ALOC_ERROR);
		}
		size_t retval;


		if ((retval = fread((void*)temp, sizeof(STUDENT), 1, pf)) != 1)
			return false;

		

		if ((temp->surname = (char*)malloc((temp->size + 1) * sizeof(char))) == NULL)
			return false;
		if ((retval = fread((void*)temp->surname, sizeof(char), temp->size + 1, pf)) != temp->size + 1)
			return false;

		*ptr_data = STUDENT_push(temp->surname, temp->birth_year, temp->course);

		return true;
	}
	else
		return false;
}

