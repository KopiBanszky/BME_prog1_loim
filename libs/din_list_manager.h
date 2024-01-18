#include "read_data.h"
#include "read_data_from_row_file.h"

void free_Choose_Question_list(Choose_By_Question *elso);

void free_Difficulty_list(Difficulties_list *list_for_different_difficulties[]);

Choose_By_Question *get_question_by_number(int difficulty, int num, Difficulties_list *list_for_different_difficulties[]);

int din_length_diff(Difficulties_list *list);

void free_Row_Question_list(Row_Question *elso);

Row_Question *get_row_question_by_number(int num, Row_Question *first);

int din_length_row(Row_Question *list);