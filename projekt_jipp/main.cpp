#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mess.h"
#include "stack.h"
#include "data.h"
#include "interface.h"

int main()
{
	STACK_init(STUDENT_free, STUDENT_print);
	int choice = 0;

	while (choice >= INTREFACE_PUSH && choice <= INTERFACE_END)
	{
		menu();
		scanf("%d", &choice);

		switch (choice)
		{
		case INTREFACE_PUSH: push();
			break;
		case INTERFACE_POP: pop();
			break;
		case INTERFACE_FIND: find();
			break;
		case INTERFACE_SAVE: save();
			break;
		case INTERFACE_LOAD: load();
			break;
		case INTERFACE_CLEAR: clear();
			break;
		case INTERFACE_END: clear();
			return 0;
		default:
			mess_fun(MESS_CHOICE_WARN);
			break;
		}
	}

	return 0;
}