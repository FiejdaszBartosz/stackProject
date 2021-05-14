#include <stdlib.h>
#include <stdio.h>
#include "mess.h"
#include "stack.h"

static const char* message_str_arr[] = {
	"E memory allocation error",
	"W unknown comand",
	"W push error"
};

void mess_fun(enum MESSAGES mess)
{
	puts(message_str_arr[mess] + 1);

	if (message_str_arr[mess][0] == 'E')
	{
		STACK_free();
		system("pause");
	}

	return;
}