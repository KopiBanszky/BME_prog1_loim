#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "utility.h"
#include <stdbool.h>
#include "read_data.h"


/* Megnézi hogy léteznek e az adattároló fileok. Ha nem, kér a felhasználótól megfelelõt
 * return érték, amint lefutott: 0. Más nincs */

//TODO: Ha hibás a file spameli a while ciklusokat

char *validate_file(char *path, File_type fileType){
    FILE *tmp = fopen(path, "r");
    char new_path[500];
    if(tmp == NULL) while(tmp == NULL){
        if(fileType == LOIM)
            printf("Más feleletválasztó kérdés file. (.csv típusu): \n");
        else
            printf("Más sorbarendezendõ kérdés file. (.csv típusu): \n");
        fgets(new_path, sizeof new_path, stdin);
            new_path[strlen(new_path) - 1] = '\0';
        tmp = fopen(new_path, "r");
    }
    else{
        char *res = malloc((strlen(path) + 2) * sizeof (char));
        strcpy(res, path);
        fclose(tmp);
        return res;
    }
    char *res = malloc(strlen(new_path) * sizeof (char));
    strcpy(res, new_path);
    fclose(tmp);
    return res;
}


Choose_By_Question *load_loim_in_dinlist(char *pathToFile, Difficulties_list *list_for_different_difficulties[]){
    FILE* file = fopen(pathToFile, "r");
    if (file == NULL) {
        perror("Hiba a fájl megnyitasakor");
        return NULL;
    }

    Choose_By_Question *elso = NULL;

    char temp_line[500];
    fgets(temp_line, sizeof (temp_line), file);
    int n = 0;
    while (fgets(temp_line, sizeof(temp_line), file) != NULL){
        Choose_By_Question *line = (Choose_By_Question*) malloc( sizeof (Choose_By_Question));

        if(line == NULL){
            perror("Null pointer");
            abort();
        }

        int *lengths = count_chars_between_char(temp_line, ';');


        line->question = (char*) malloc((lengths[1]+2) * sizeof (char));
        line->answerA = (char*) malloc((lengths[2]+2) * sizeof (char));
        line->answerB = (char*) malloc((lengths[3]+2) * sizeof (char));
        line->answerC = (char*) malloc((lengths[4]+2) * sizeof (char));
        line->answerD = (char*) malloc((lengths[5]+2) * sizeof (char));
        line->category = (char*) malloc((lengths[7]+2) * sizeof (char));
        free(lengths);
        line->next = NULL;

        sscanf(temp_line, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%c;%[^;]\n",
               &line->difficulty,
               line->question,
               line->answerA,
               line->answerB,
               line->answerC,
               line->answerD,
               &line->answer,
               line->category);

        Difficulties_list *pos_by_difficulty = list_for_different_difficulties[line->difficulty-1];
        if(pos_by_difficulty == NULL){
            Difficulties_list *element = (Difficulties_list*) malloc(sizeof (Difficulties_list));
            element->question = line;
            element->next = NULL;
            list_for_different_difficulties[line->difficulty-1] = element;
        }
        else{
            Difficulties_list *element = (Difficulties_list*) malloc(sizeof (Difficulties_list));
            element->question = line;
            element->next = pos_by_difficulty;
            list_for_different_difficulties[line->difficulty-1] = element;
        }

        line->next = elso;
        elso = line;
        ++n;
    }

    fclose(file);
    return elso;

}
