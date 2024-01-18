#include "read_data_from_row_file.h"
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#include "debugmalloc.h"

Row_Question *create_row_question_list(char path_to_file[]){
    FILE* file = fopen(path_to_file, "r");
    if (file == NULL) {
        perror("Hiba a fájl megnyitasakor");
        return NULL;
    }

    Row_Question *first = NULL;

    char temp_line[500];
    fgets(temp_line, sizeof (temp_line), file);
    while (fgets(temp_line, sizeof(temp_line), file) != NULL) {
        Row_Question *line = (Row_Question *) malloc(sizeof(Row_Question));

        if (line == NULL) {
            perror("Null pointer");
            abort();
        }

        int *lengths = count_chars_between_char(temp_line, ';');


        line->question = (char *) malloc((lengths[0] + 2) * sizeof(char));
        line->answerA = (char *) malloc((lengths[1] + 2) * sizeof(char));
        line->answerB = (char *) malloc((lengths[2] + 2) * sizeof(char));
        line->answerC = (char *) malloc((lengths[3] + 2) * sizeof(char));
        line->answerD = (char *) malloc((lengths[4] + 2) * sizeof(char));
        line->answer = (char *) malloc((lengths[5] + 2) * sizeof(char));
        line->category = (char *) malloc((lengths[6] + 2) * sizeof(char));
        free(lengths);
        line->next = NULL;

        sscanf(temp_line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]\n",
               line->question,
               line->answerA,
               line->answerB,
               line->answerC,
               line->answerD,
               line->answer,
               line->category);


        line->next = first;
        first = line;
    }

    fclose(file);
    return first;
}