#include <stdio.h>

struct STACK
{
	void* ptr_element_data;
	struct STACK* next;
};

typedef void(*free_data)(void* ptr_data);
typedef int(compare_data)(void* ptr_current_data, void* ptr_serch_data);
typedef void(*print_data)(void* ptr_data);
typedef bool(IO_object)(void* ptr_data, FILE* pf);

void STACK_init(free_data ptr_free_fun, print_data ptr_print_fun);
void STACK_free();
STACK* STACK_push(void* ptr_data);
STACK STACK_pop();
void* STACK_serch(void* ptr_serch_data, compare_data ptr_compare_type, int first_entry);
bool STACK_save(IO_object object);
bool STACK_load(IO_object* object);
