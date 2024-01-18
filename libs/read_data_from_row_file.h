#ifndef LEGYEN_ON_IS_MILLIOMOS_READ_DATA_FROM_ROW_FILE_H
#define LEGYEN_ON_IS_MILLIOMOS_READ_DATA_FROM_ROW_FILE_H

typedef struct Row_Question {
    char *question;
    char *answerA;
    char *answerB;
    char *answerC;
    char *answerD;
    char *answer;
    char *category;
    struct Row_Question *next;
} Row_Question;

Row_Question *create_row_question_list(char path_to_file[]);

#endif //LEGYEN_ON_IS_MILLIOMOS_READ_DATA_FROM_ROW_FILE_H
