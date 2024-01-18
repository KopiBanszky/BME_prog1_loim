#ifndef LEGYEN_ON_IS_MILLIOMOS_CHOOSE_QUESTION_H
#define LEGYEN_ON_IS_MILLIOMOS_CHOOSE_QUESTION_H
#endif //LEGYEN_ON_IS_MILLIOMOS_CHOOSE_QUESTION_H

typedef struct Choose_question_Params{
    int question_num;
    Regular_Data *lists;
} Choose_question_Params;

Page_Func choose_question(void *param);

