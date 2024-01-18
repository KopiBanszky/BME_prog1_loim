#include "read_data.h"
#include "debugmalloc.h"
#include "read_data_from_row_file.h"



void free_Choose_Question_list(Choose_By_Question *elso){
    while (elso != NULL){
        Choose_By_Question *tmp = elso->next;
        free(elso->question);
        free(elso->answerA);
        free(elso->answerB);
        free(elso->answerC);
        free(elso->answerD);
        free(elso->category);
        free(elso);
        elso = tmp;
    }
}


void free_Difficulty_list(Difficulties_list *list_for_different_difficulties[]){
    for (int i = 0; i < 15; ++i) {
        Difficulties_list *elso = list_for_different_difficulties[i];
        while (elso != NULL){
            Difficulties_list *tmp = elso->next;
            free(elso);
            elso = tmp;
        }
    }
}

void free_Row_Question_list(Row_Question *elso){
    while (elso != NULL){
        Row_Question *tmp = elso->next;
        free(elso->question);
        free(elso->answerA);
        free(elso->answerB);
        free(elso->answerC);
        free(elso->answerD);
        free(elso->answer);
        free(elso->category);
        free(elso);
        elso = tmp;
    }

}

int din_length_diff(Difficulties_list *list){
    int n = 0;
    Difficulties_list *tmp = list;
    if(tmp != NULL) while (tmp->next != NULL){
        tmp = tmp->next;
        ++n;
    }
    return n;
}

int din_length_row(Row_Question *list){
    int n = 0;
    Row_Question *tmp = list;
    while (tmp != NULL){
        tmp = tmp->next;
        ++n;
    }
    return n;
}

Choose_By_Question *get_question_by_number(int difficulty, int num, Difficulties_list *list_for_different_difficulties[]){
    Difficulties_list *tmp = list_for_different_difficulties[difficulty];
    for (int i = 0; i < num; ++i) {
        tmp = tmp->next;
    }
    return tmp->question;
}

Row_Question *get_row_question_by_number(int num, Row_Question *first){
    for (int i = 0; i < num; ++i) {
        if(first->next == NULL) break;
        first = first->next;
    }
    return first;
}