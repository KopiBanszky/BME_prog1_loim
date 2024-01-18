#include "../libs/econio.h"
#include "../libs/utility.h"
#include "main_menu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../libs/debugmalloc.h"


Page_Func find_vote_chance(void *param);
Page_Func stat_menu(void *param);
Page_Func stat_menu_all(void *param);

void printTableRow(Statistics *first){
    int place = 1;
    while (first != NULL){
        printf("|");
        char splace[24];
        itoa(place, splace, 10);
        strcat(splace, ".");
        char sprize[24];
        itoa(first->prize, sprize, 10);
        strcat(sprize, " Ft");
        char *time = readable_time(first->time_sec);
        char long_time[24];
        strcpy(long_time, time);
        free(time);
        char name_ext[24];
        strcpy(name_ext, first->name); /* A debugmalloc kanária miatt csak egy tonna KKKKKKKKKKKKK-t másol be*/
        char *header[4] = {
                splace,
                name_ext,
                sprize,
                long_time,
        };
        for (int i = 0; i < 4; ++i) {
            bool voltveg = false;
            for (int j = 0; j < 24; ++j) {
                if(header[i][j] == '\0') voltveg = true;
                if(voltveg) header[i][j] = ' ';
            }
            voltveg = false;
            header[i][22] = '|';
            header[i][23] = '\0';
            printf("%s", header[i]);
        }
        printf("\n");
        Statistics *tmp = first;
        first = first->next;
        ++place;
        free(tmp);
    }
}

Statistics *filteredSorted(Settings_menu_Param *params, bool unfiltered){
    Statistics *tmp = params->lists->stats;
    Properties *settings = params->preview;
    Statistics *first = NULL;
    while (tmp != NULL){
            if(
                unfiltered || (
                (tmp->vote_chance == settings->vote_chance) && (tmp->difficulty == settings->difficulty)
            )){
                Statistics *new = (Statistics*) malloc(sizeof (Statistics));
                new->difficulty = tmp->difficulty;
                new->vote_chance = tmp->vote_chance;
                new->prize = tmp->prize;
                new->time_sec = tmp->time_sec;
                new->name = tmp->name;
                new->next = NULL;
                if(first == NULL) first = new;
                else {
                    new->next = first;
                    first = new;
                }
            }
            tmp = tmp->next;
    }


    bool changed = true;
    if((first != NULL) && (first->next != NULL))
        while (changed) {
            Statistics *lemarado;
            Statistics *current = first;
            Statistics *next_node;
            changed = false;
            do {
                next_node = current->next;
                if (current->time_sec > next_node->time_sec) {
                    changed = true;
                    if (lemarado == NULL) {
                        first = next_node;
                        current->next = next_node->next;
                        first->next = current;
                        lemarado = first;
                        continue;
                    } else {
                        lemarado->next = next_node;
                        current->next = next_node->next;
                        next_node->next = current;
                        lemarado = next_node;
                        continue;
                    }
                } else {
                    lemarado = current;
                    current = next_node;
                }
            } while (current->next != NULL);

        }




    return first;
}

/* Véglegesen elmenti a beállításokat */
Page_Func search(void *param){
    Settings_menu_Param *params = param;
    Page_Func res = {
            stat_menu,
            params,
            KEY_ENTER
    };
    return res;
}

Page_Func backToMain(void *param){
    Settings_menu_Param *params = param;
    params->preview->difficulty = params->settings->difficulty;
    params->preview->vote_chance = params->settings->vote_chance;

    Page_Func res = {
            main_menu,
            params->lists,
            KEY_ENTER
    };
//    free(param);
    return res;
}


/* A nehézség beállításait lépteti, még nem menti véglegesen. */
Page_Func find_difficulty(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[5] = {{"d", NULL, find_difficulty, 'd', params},
                                        {"a", "Összes", stat_menu_all, 'a', params},
                                        {"w", NULL, find_vote_chance, 'w', params},
                                        {"Enter", "Ok", search, KEY_ENTER, param},
                                        {"Esc", "Vissza", backToMain, KEY_ESCAPE, params}};

    ++params->preview->difficulty;
    if(params->preview->difficulty > 9) params->preview->difficulty = 0;

    char options[63] = "Nehézség: ";
    for (int i = 0; i < 10; ++i) {
        char snum[3];
        itoa(i+1, snum, 10);
        strcat(options, " - ");
        /* || karakterek közé teszi az éppen kiválasztott opciót */
        if(i == params->preview->difficulty){
            strcat(options, "|");
            strcat(options, snum);
            strcat(options, "|");
            continue;
        }
        strcat(options, snum);
    }

    char snum[4];
    char vote_menupoint[31] = "Szavazás segítség esélye - ";
    itoa(params->preview->vote_chance, snum, 10);
    strcat(vote_menupoint, snum);
    strcat(vote_menupoint, "%");
    settings_menu_items[2].option = vote_menupoint;


    display_title();
    settings_menu_items[0].option = options;
    display_menu_items(settings_menu_items, 5);


    return wait_menu_input(settings_menu_items, 5);

}

/* A szavazás sikerességének esélyein lépked végig, még nem menti a végleges beállításokat. */
Page_Func find_vote_chance(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[5] = {{"d", NULL, find_difficulty, 'd', params},
                                        {"a", "Összes", stat_menu_all, 'a', params},
                                        {"w", NULL, find_vote_chance, 'w', params},
                                        {"Enter", "Ok", search, KEY_ENTER, param},
                                        {"Esc", "Vissza", backToMain, KEY_ESCAPE, params}};

    params->preview->vote_chance += 5;

    char difficulty_menupoint[15] = "Nehézség - ";
    char snum[4];
    itoa(params->preview->difficulty, snum, 10);
    strcat(difficulty_menupoint+1, snum);
    settings_menu_items[0].option = difficulty_menupoint;

    if(params->preview->vote_chance > 100) params->preview->vote_chance = 10;
    char options[31] = "Szavazás segítség esélye - ";
    itoa(params->preview->vote_chance, snum, 10);
    strcat(options, snum);
    strcat(options, "%");

    display_title();
    settings_menu_items[2].option = options;
    display_menu_items(settings_menu_items, 5);



    return wait_menu_input(settings_menu_items, 5);
}

Page_Func stat_menu_all(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[5] = {{"d", NULL, find_difficulty, 'd', params},
                                        {"a", "Összes", stat_menu_all, 'a', params},
                                        {"w", NULL, find_vote_chance, 'w', params},
                                        {"Enter", "Ok", search, KEY_ENTER, param},
                                        {"Esc", "Vissza", backToMain, KEY_ESCAPE, params}};

    display_title();


    char difficulty_menupoint[15] = "Nehézség - ";
    char snum[4];
    itoa(params->preview->difficulty+1, snum, 10);
    strcat(difficulty_menupoint, snum);
    settings_menu_items[0].option = difficulty_menupoint;

    char vote_menupoint[31] = "Szavazás segítség esélye - ";
    itoa(params->preview->vote_chance, snum, 10);
    strcat(vote_menupoint, snum);
    strcat(vote_menupoint, "%");
    settings_menu_items[2].option = vote_menupoint;


    display_menu_items(settings_menu_items, 5);

    Statistics *sorted_list = filteredSorted(params, true);
    if(sorted_list == NULL){
        printf("\n\nNincs a keresésnek megfelelõ játékos.\n");
        return wait_menu_input(settings_menu_items, 5);
    }
    printf("\n\n|");

    char header[4][24] = {
            "Helyezés",
            "Név",
            "Nyeremény",
            "Játékidõ",
    };
    for (int i = 0; i < 4; ++i) {
        bool voltveg = false;
        for (int j = 0; j < 24; ++j) {
            if(header[i][j] == '\0') voltveg = true;
            if(voltveg) header[i][j] = ' ';
        }
        voltveg = false;
        header[i][22] = '|';
        header[i][23] = '\0';
        printf("%s", header[i]);
    }
    printf("\n");

    printTableRow(sorted_list);

    return wait_menu_input(settings_menu_items, 5);
}


/* Megjeleníti a beállítások menüpontot */
Page_Func stat_menu(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[5] = {{"d", NULL, find_difficulty, 'd', params},
                                        {"a", "Összes", stat_menu_all, 'a', params},
                                        {"w", NULL, find_vote_chance, 'w', params},
                                        {"Enter", "Ok", search, KEY_ENTER, param},
                                        {"Esc", "Vissza", backToMain, KEY_ESCAPE, params}};

    display_title();


    char difficulty_menupoint[15] = "Nehézség - ";
    char snum[4];
    itoa(params->preview->difficulty+1, snum, 10);
    strcat(difficulty_menupoint, snum);
    settings_menu_items[0].option = difficulty_menupoint;

    char vote_menupoint[31] = "Szavazás segítség esélye - ";
    itoa(params->preview->vote_chance, snum, 10);
    strcat(vote_menupoint, snum);
    strcat(vote_menupoint, "%");
    settings_menu_items[2].option = vote_menupoint;


    display_menu_items(settings_menu_items, 5);

    Statistics *sorted_list = filteredSorted(params, false);
    if(sorted_list == NULL){
        printf("\n\nNincs a keresésnek megfelelõ játékos.\n");
        return wait_menu_input(settings_menu_items, 5);
    }
    printf("\n\n|");

    char header[4][24] = {
            "Helyezés",
            "Név",
            "Nyeremény",
            "Játékidõ",
    };
    for (int i = 0; i < 4; ++i) {
        bool voltveg = false;
        for (int j = 0; j < 24; ++j) {
            if(header[i][j] == '\0') voltveg = true;
            if(voltveg) header[i][j] = ' ';
        }
        voltveg = false;
        header[i][22] = '|';
        header[i][23] = '\0';
        printf("%s", header[i]);
    }
    printf("\n");

    printTableRow(sorted_list);

    return wait_menu_input(settings_menu_items, 5);

}