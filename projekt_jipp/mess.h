enum MESSAGES
{
	MESS_MEM_ALOC_ERROR,
	MESS_FILE_OPEN_ERROR,
	MESS_CHOICE_WARN,
	MESS_PUSH_ERROR,
	MESS_FATAL_ERROR,
	MESS_TOTAL
};

void mess_fun(enum MESSAGES mess);
void file_error(FILE* fp, __int64* file_descriptor);