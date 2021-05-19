#include <stdio.h>

enum DEGREE_COURSE {
	INFORMATYKA,
	MATEMATYKA,
	FIZYKA
};

struct STUDENT
{
	char* surname;
	int birth_year;
	DEGREE_COURSE course;
	size_t size;
};

void* STUDENT_init(char* init_surname, int init_year, DEGREE_COURSE course);
const char* STUDENT_get_course(enum DEGREE_COURSE course);
void STUDENT_free(void* ptr);
void* STUDENT_push(char* surname, int birth_year, DEGREE_COURSE course);
void STUDENT_print(void* ptr);
int STUDENT_search_surname(void* ptr_current_data, void* ptr_search_data);
int STUDENT_search_course(void* ptr_current_data, void* ptr_search_data);
int STUDENT_search_birth_year(void* ptr_current_data, void* ptr_search_data);
bool STUDENT_save(void* ptr_data, FILE* pf);
bool STUDENT_load(void** ptr_data, FILE* pf);

bool STUDENT_save_q(void* ptr_data, FILE* pf);
bool STUDENT_load_q(void** ptr_data, FILE* pf);