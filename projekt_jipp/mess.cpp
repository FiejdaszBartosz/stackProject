#include <stdlib.h>
#include <stdio.h>
#include "mess.h"
#include "stack.h"

static const char* message_str_arr[] = {
	(char*)"E memory allocation error",
	(char*)"E file open error",
	(char*)"W unknown comand",
	(char*)"W push error",
	(char *)"E fatal error"
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

void file_error(FILE* fp, __int64* file_descriptor)
{
	if (fp)
		fclose(fp);
	if (file_descriptor)
		free(file_descriptor);

	mess_fun(MESS_FATAL_ERROR);
	system("pause");
	exit(1);
}

