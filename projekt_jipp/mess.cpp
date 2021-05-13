#include "mess.h"
#include <stdlib.h>
#include <stdio.h>

static const char* message_str_arr[] = {
	"E memory allocation error",
	"W unknown comand"
};

void mess_fun(enum MESSAGES mess)
{
	puts(message_str_arr[mess] + 1);

	if (message_str_arr[mess][0] == 'E')
	{
		//Free pamieci
		system("pause");
	}

	return;
}