#include "../libs/econio.h"
#include "../libs/utility.h"
#include "main_menu.h"
#include <stdlib.h>
#include <string.h>
#include "../libs/debugmalloc.h"


Page_Func set_vote_chance(void *param);

/* Véglegesen elmenti a beállításokat */
Page_Func save(void *param){
    Settings_menu_Param *params = param;
    params->settings->difficulty = params->preview->difficulty;
    params->settings->vote_chance = params->preview->vote_chance;

    Page_Func res = {
            main_menu,
            params->lists,
            KEY_ENTER
    };
//    free(param);
    return res;
}

Page_Func back(void *param){
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
Page_Func set_difficulty(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[4] = {{"d", NULL, set_difficulty, 'd', params},
                                        {"Enter", "Mentés", save, KEY_ENTER, param},
                                        {"w", NULL, set_vote_chance, 'w', params},
                                        {"Esc", "Mégse", back, KEY_ESCAPE, params}};

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
    display_menu_items(settings_menu_items, 4);


    return wait_menu_input(settings_menu_items, 4);

}

/* A szavazás sikerességének esélyein lépked végig, még nem menti a végleges beállításokat. */
Page_Func set_vote_chance(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[4] = {{"d", NULL, set_difficulty, 'd', params},
                                        {"Enter", "Mentés", save, KEY_ENTER, param},
                                        {"w", NULL, set_vote_chance, 'w', params},
                                        {"Esc", "Mégse", back, KEY_ESCAPE, params}};

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
    display_menu_items(settings_menu_items, 4);



    return wait_menu_input(settings_menu_items, 4);
}

/* Megjeleníti a beállítások menüpontot */
Page_Func settings_menu(void *param){
    Settings_menu_Param *params = param;
    Menu_Item settings_menu_items[4] = {{"d", NULL, set_difficulty, 'd', params},
                                        {"Enter", "Mentés", save, KEY_ENTER, param},
                                        {"w", NULL, set_vote_chance, 'w', params},
                                        {"Esc", "Mégse", back, KEY_ESCAPE, params}};

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


    display_menu_items(settings_menu_items, 4);


    return wait_menu_input(settings_menu_items, 4);

}