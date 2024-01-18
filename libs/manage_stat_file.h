#ifndef LEGYEN_ON_IS_MILLIOMOS_MANAGE_STAT_FILE_H
#define LEGYEN_ON_IS_MILLIOMOS_MANAGE_STAT_FILE_H


typedef struct Statistics {
    char *name;
    int prize;
    unsigned long int time_sec;
    int difficulty;
    int vote_chance;
    struct Statistics *next;
} Statistics;


#endif //LEGYEN_ON_IS_MILLIOMOS_MANAGE_STAT_FILE_H

Statistics *stat_file();

int change_stat(void *param);

int write_stat_file(Statistics *first);

void free_stats(Statistics *first);