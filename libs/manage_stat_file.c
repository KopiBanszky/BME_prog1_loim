#include <stdio.h>
#include "debugmalloc.h"
#include "utility.h"


Statistics *stat_file(){
    FILE *stats_fp = fopen("source/rangsor.csv", "r");
    if(stats_fp == NULL)
        return NULL;

    Statistics *first = NULL;

    char temp_line[120];
    while (fgets(temp_line, sizeof(temp_line), stats_fp) != NULL) {
        Statistics *line = (Statistics *) malloc(sizeof(Statistics));

        if (line == NULL) {
            perror("Null pointer");
            abort();
        }

        int name_length = 0;
        while(name_length < 51) {
            if(temp_line[name_length] == ';') break;
            ++name_length;
        }


        line->name = (char *) malloc((name_length + 1) * sizeof(char));
        line->next = NULL;

        sscanf(temp_line, "%[^;];%d;%ld;%d;%d\n",
               line->name,
               &line->prize,
               &line->time_sec,
               &line->difficulty,
               &line->vote_chance);


        line->next = first;
        first = line;
    }

    fclose(stats_fp);
    return first;
}

int change_stat(void *param){
    Regular_Data *lists = param;
    int changed = 0;
    Statistics *save = lists->stats;
    Regular_Data *tmp = lists;
    if(tmp->stats != NULL) while (tmp->stats != NULL){
        if(strcmp(tmp->stats->name, lists->settings->name) == 0){
            tmp->stats->vote_chance = lists->settings->vote_chance;
            tmp->stats->difficulty = lists->settings->difficulty;
            tmp->stats->time_sec = lists->settings->time_sec;
            tmp->stats->prize = lists->settings->prize;
            tmp->stats = save;
            changed = 1;
            break;
        }
        tmp->stats = tmp->stats->next;
    }
    else {
        lists->stats = (Statistics*) malloc(sizeof (Statistics));
        lists->stats->name = lists->settings->name;
        lists->stats->next = NULL;
        lists->stats->prize =lists-> settings->prize;
        lists->stats->time_sec = lists->settings->time_sec;
        lists->stats->difficulty = lists->settings->difficulty;
        lists->stats->vote_chance =lists-> settings->vote_chance;
        changed = -1;
    }
    if(changed == 0){
        tmp->stats = (Statistics*) malloc(sizeof (Statistics));
        tmp->stats->name = lists->settings->name;
        tmp->stats->next = save;
        tmp->stats->prize = lists->settings->prize;
        tmp->stats->time_sec = lists->settings->time_sec;
        tmp->stats->difficulty = lists->settings->difficulty;
        tmp->stats->vote_chance = lists->settings->vote_chance;
        changed = 2;
    }
    return changed;
}

int write_stat_file(Statistics *first){
    FILE *stat_fp = fopen("source/rangsor.csv", "w");
    if(stat_fp == NULL) return -1;

    int changed = 0;
    Statistics *tmp = first;
    if(tmp != NULL) while (tmp != NULL){

        fprintf(stat_fp, "%s;%d;%lu;%d;%d\n", tmp->name,
                tmp->prize,
                tmp->time_sec,
                tmp->difficulty,
                tmp->vote_chance);
        tmp = tmp->next;
        ++changed;
    }
    else{
        fclose(stat_fp);
        return -1;
    }

    fclose(stat_fp);
    return changed;
}

void free_stats(Statistics *first){
    while (first != NULL){
        Statistics *tmp = first->next;
        free(first->name);
        free(first);
        first = tmp;
    }
}