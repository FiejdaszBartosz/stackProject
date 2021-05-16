#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "mess.h"
#include "interface.h"

static STACK* top = NULL;
const char filename[] = "data_file.bin";
free_data ptr_free_data;
print_data ptr_print_data;

void STACK_init(free_data ptr_free_fun, print_data ptr_print_fun)
{
	top = NULL;
	ptr_free_data = ptr_free_fun;
	ptr_print_data = ptr_print_fun;
}

void STACK_free()
{
	STACK* current = top, * temp = NULL;

	while (current)
	{
		(*ptr_free_data)(current->ptr_element_data);
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}

	top = NULL;
}

STACK* STACK_push(void* ptr_data)
{
	STACK* current = (STACK*)malloc(sizeof(STACK));
	if (!current)
		mess_fun(MESS_MEM_ALOC_ERROR);

	current->ptr_element_data = ptr_data;

	if (top == NULL)
	{
		current->next = NULL;
		top = current;

		return current;
	}
	else
	{
		current->next = top;
		top = current;

		return current;
	}
}

STACK STACK_pop()
{
	STACK current;

	if (top == NULL)
	{
		current.ptr_element_data = NULL;
		current.next = NULL;
	}
	else
	{
		STACK* temp = top->next;

		current.ptr_element_data = top->ptr_element_data;
		current.next = NULL;

		free(top);

		top = temp;
	}

	return current;
}

void* STACK_serch(void* ptr_serch_data, compare_data ptr_compare_type, int first_entry)
{
	static STACK* ptr_serch_item;
	STACK* temp;

	if (first_entry)
		ptr_serch_item = top;

	while (ptr_serch_item)
	{
		if(!(*ptr_compare_type)(ptr_serch_item->ptr_element_data, ptr_serch_data))
			ptr_serch_item = ptr_serch_item->next;
		else
		{
			temp = ptr_serch_item;
			ptr_serch_item = ptr_serch_item->next;

			return temp->ptr_element_data;
		}
	}

	return NULL;
}

bool STACK_save(IO_object object)
{
	STACK* temp1 = top, * temp2, * current = top;
	size_t i, no_items = 0, retval;

	FILE* pf = fopen(filename, "wb");
	if (!pf)
		mess_fun(MESS_FILE_OPEN_ERROR);

	while (temp1)
	{
		temp2 = temp1;
		temp1 = temp1->next;
		++no_items;
	}

	if ((retval = fwrite((const void*)&no_items, sizeof(no_items), 1, pf)) != 1)
		return false;

	for (i = 0; i < no_items; ++i)
	{
		if (!(*object)(current->ptr_element_data, pf))
			return false;

		current = current->next;
	}

	fclose(pf);
	pf = NULL;

	return true;
}

bool STACK_load(IO_object* object)
{
	STACK* tmp;
	size_t i, no_items = 0, retval;

	memset((void*)&tmp, 0, sizeof(tmp));

	FILE* pf = fopen(filename, "rb");
	if (!pf)
		return false;

	if (top != NULL)
		STACK_free();

	if ((retval = fread((void*)&no_items, sizeof(no_items), 1, pf)) != 1)
		return false;
	
	for(i = 0; i < no_items; ++i)
	{
		if (!(*object)(tmp->ptr_element_data, pf))
			return false;

		if(!STACK_push(tmp))
			return false;

		tmp->ptr_element_data = NULL;
	}

	fclose(pf);
	pf = NULL;

	free(tmp);
	tmp = NULL;
	return true;
}


