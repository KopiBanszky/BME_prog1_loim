#include "debugmalloc.h"
#include "econio.h"
#include "../pages/main_menu.h"
#include "../pages/name_page.h"
#include "utility.h"
#include <stdio.h>
#include <string.h>
#include "din_list_manager.h"
#include "../pages/pause_page.h"


#define TITLE "  _                                     _   _           _     \n | |                                   (_) (_)         (_)    \n | |     ___  __ _ _   _  ___ _ __       ___  _ __      _ ___ \n | |    / _ \\/ _` | | | |/ _ \\ '_ \\     / _ \\| '_ \\    | / __|\n | |___|  __/ (_| | |_| |  __/ | | |   | (_) | | | |   | \\__ \\\n |______\\___|\\__, |\\__, |\\___|_| |_|    \\___/|_| |_|   |_|___/\n$$\\      $$\\ $$$$$$\\ $$\\       $$\\       $$$$$$\\  $$$$$$\\  $$\\      $$\\  $$$$$$\\   $$$$$$\\  \n$$$\\    $$$ |\\_$$  _|$$ |      $$ |      \\_$$  _|$$  __$$\\ $$$\\    $$$ |$$  __$$\\ $$  __$$\\ \n$$$$\\  $$$$ |  $$ |  $$ |      $$ |        $$ |  $$ /  $$ |$$$$\\  $$$$ |$$ /  $$ |$$ /  \\__|\n$$\\$$\\$$ $$ |  $$ |  $$ |      $$ |        $$ |  $$ |  $$ |$$\\$$\\$$ $$ |$$ |  $$ |\\$$$$$$\\  \n$$ \\$$$  $$ |  $$ |  $$ |      $$ |        $$ |  $$ |  $$ |$$ \\$$$  $$ |$$ |  $$ | \\____$$\\ \n$$ |\\$  /$$ |  $$ |  $$ |      $$ |        $$ |  $$ |  $$ |$$ |\\$  /$$ |$$ |  $$ |$$\\   $$ |\n$$ | \\_/ $$ |$$$$$$\\ $$$$$$$$\\ $$$$$$$$\\ $$$$$$\\  $$$$$$  |$$ | \\_/ $$ | $$$$$$  |\\$$$$$$  |\n\\__|     \\__|\\______|\\________|\\________|\\______| \\______/ \\__|     \\__| \\______/  \\______/ \n                                                                                            \n                                                                                            \n                                                                                            \n\n"



/* Legyen ön is milliomos felirat megjelenítése */
void display_title(){
    econio_clrscr();
    econio_textcolor(COL_BLUE);
    printf(TITLE);
    econio_textcolor(COL_WHITE);
}

/* adott hosszúságú üres karakterekbõl álló stringet tesz a elsõ paraméterbe
 * Visszatérési értéke a sikeres üreskarakterek generálásának száma*/
int create_blank_space(char dest[], int length){
    int n = 0;
    for (int i = 0; i < length; ++i) {
        dest[i] = ' ';
        ++n;
    }
    dest[length] = '\0';
    return n;
}

/* Megjeleníti a Menu_Item listában lévõ elemeketet a képernyõn, szép elválasztással
 * Visszatérési értéke a sikeresen megjelenített menüelemek száma*/
int display_menu_items(Menu_Item *item_list, int length){
//    char *keys[],  *options[];
    int max_width = 90;
    int used_chars_num = 0;

    int n = 0;


    for (int i = 0; i < length; ++i) {
        Menu_Item item = item_list[i];
        char *key = item.key;
        int key_length = strlen(item.key);

//        printf(" - %d : %llu -  ", len(item.key), strlen(item.key));

        int max_length = 0;

        if(i%2 == 0) for (int j = 0; j < length; j += 2) {
            Menu_Item next_item = item_list[j];
            if (strlen(next_item.key) > max_length) max_length = strlen(next_item.key);
        }
        else for(int j = 1; j < length; j += 2) {
            Menu_Item next_item = item_list[j];
            if (strlen(next_item.option) > max_length) max_length = strlen(next_item.option);
        }

        int first_blanks = (i%2 == 0) ? max_length - strlen(item.key) + 1 : max_length - strlen(item.option) + 1;

        if(i%2 == 1){
            max_width -= (used_chars_num + key_length + first_blanks + strlen(item.option));
            char middle[max_width];
            create_blank_space(middle, max_width);
            printf("%s", middle);
            max_width = 90;
            used_chars_num = 0;
        }
        else used_chars_num += key_length + 1 + first_blanks + strlen(item.option);


        char blank[first_blanks];
        create_blank_space(blank, first_blanks);

        econio_textcolor(COL_BLACK);
        econio_textbackground(COL_WHITE);
        if((key[0] >= 'A') && (key[0] <= 'D') && (strlen(key) == 1)) econio_textbackground(COL_YELLOW);
        printf("%s:", key);

        econio_textcolor(COL_WHITE);
        econio_textbackground(COL_BLACK);
        if((key[0] >= 'A') && (key[0] <= 'D') && (strlen(key) == 1)) econio_textbackground(COL_YELLOW);
        printf("%s", blank);

        econio_textcolor(COL_WHITE);
        econio_textbackground(COL_BLACK);
        if((key[0] >= 'A') && (key[0] <= 'D') && (strlen(key) == 1)) econio_textbackground(COL_YELLOW);
        if((key[0] >= 'A') && (key[0] <= 'D') && (strlen(key) == 1)) econio_textcolor(COL_BLACK);
        printf("%s%s", item.option, (i%2 == 0 ? " ": "\n"));
        econio_textcolor(COL_WHITE);
        econio_textbackground(COL_BLACK);
        ++n;

    }
    return n;
}

/* A Menu_Item lista alapján kezeli a billentyû lenyomásokat
 * Visszatérési értéke a lenyomott billentyû*/
Page_Func wait_menu_input(Menu_Item item_list[], int length){
    econio_rawmode();
    bool run = true;
    int key = -1;
    Page_Func res;
    while (run){
        key = econio_getch();
        for (int i = 0; i < length; ++i) {
            if(item_list[i].KEY_CODE == key){
                res.function = item_list[i].function;
                res.param = item_list[i].param;
                res.key = key;
//                item_list[i].function(item_list[i].param);
                run = false;
                break;
            }
        }
    }

    econio_normalmode();
    return res;
}

Page_Func start_game(void *param){
    Regular_Data *params = param;
    Page_Func res;
    Pause_page_Params PauseParams;
    Name_page_Params namePageParams;
//    free(param_main->settings);
    if(params->settings->name != NULL){
        PauseParams.type = ROW;
        PauseParams.lists = params;
        res.function = pause_page;
        res.param = &PauseParams;
    }
    else{
        namePageParams.lists = params;
        namePageParams.settings = params->settings;
        res.function = name_page;
        res.param = &namePageParams;
    }
    return res;
}

/* Bezárja a programot */
Page_Func app_exit(void *param){
    Exit_Params *firsts = param;
    Regular_Data *lists = firsts->lists;

    free_Choose_Question_list(lists->chooseByQuestion);
    free_Row_Question_list(lists->rowQuestion);
    free_Difficulty_list(lists->difficulty_list);
    free_stats(lists->stats);
//    free(firsts->lists->settings->name);
    Page_Func close = {
        NULL,
        NULL,
        200
    };
    return close;
}


int *count_chars_between_char(char *str, char str_end){
    int max_len = strlen(str);
    int list[max_len];
    int i_list = 0;
    int n = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if(str[i] == str_end || str[i] == '\n'){
            list[i_list] = n;
            n = 0;
            ++i_list;
        }
        ++n;
    }

    int *res = (int*) malloc((i_list+2) * sizeof (int));
    for (int i = 0; i < i_list; ++i) {
        res[i] = list[i];
    }
    res[i_list+1] = -1;
    return res;

}

/* fel kell szabadítani */

char *justify_content(char **line, int list_length, Aligments align){
    int line_length = 0;
    int max_length = 92;
    for (int i = 0; i < list_length; ++i) {
        line_length += strlen(line[i]);
    }
    if(max_length < line_length) NULL;
    int blank_sum_length = max_length - line_length;
    char *styled_line = NULL;
    int blank_length;
    char *blank_space;
    switch (align) {
        case SPACE_BETWEEN:
            styled_line = (char*) malloc((max_length + 1) * sizeof (char));
            blank_length = blank_sum_length/(list_length-1);
            blank_space = (char*) malloc((blank_length+1) * sizeof (char ));
            strcpy(styled_line, line[0]);
            create_blank_space(blank_space, blank_length);
            for (int i = 1; i < list_length; ++i) {
                strcat(styled_line, blank_space);
                strcat(styled_line ,line[i]);
            }
            strcat(styled_line, "\0");
            free(blank_space);
            break;
        case SPACE_AROUND:
            styled_line = malloc((max_length + 1) * sizeof (char));
            blank_length = blank_sum_length/(list_length+1);
            blank_space = (char*) malloc((blank_length+1) * sizeof (char ));
            create_blank_space(blank_space, blank_length);
            strcpy(styled_line, blank_space);
            for (int i = 0; i < list_length; ++i) {
                strcat(styled_line ,line[i]);
                strcat(styled_line, blank_space);
            }
            strcat(styled_line, "\0");
            free(blank_space);
            break;
        case CENTER:
            styled_line = malloc(max_length * sizeof (char));
            blank_length = blank_sum_length/2;
            blank_space = (char*) malloc((blank_length+1) * sizeof (char ));
            create_blank_space(blank_space, blank_length);
            strcpy(styled_line, blank_space);
            strcat(styled_line ,line[0]);
            strcat(styled_line, "\0");
            free(blank_space);
            break;
        case RIGHT:
            styled_line = malloc(max_length * sizeof (char));
            blank_length = blank_sum_length;
            blank_space = (char*) malloc((blank_length+1) * sizeof (char ));
            create_blank_space(blank_space, blank_length);
            strcat(styled_line, blank_space);
            strcat(styled_line ,line[0]);
            strcat(styled_line, "\0");
            free(blank_space);
            break;
        default:
            styled_line = (char*) malloc(line_length * sizeof (char));
            strcpy(styled_line, line[0]);
            for (int i = 1; i < list_length; ++i) {
                strcat(styled_line, line[i]);
            }
            strcat(styled_line, "\0");
            break;
    }
    return styled_line;
}

char *break_line_at_last_space(char *str){
    int length = strlen(str);
    int MAX_LENGTH = 85;
    int line_count = length/MAX_LENGTH + 1;
    char *res = (char*) malloc((length+line_count) * sizeof (char));
    int last_space_pos = -1;
    for (int i = 0; i < length; ++i) {
        if(i == last_space_pos){
            res[i] = '\n';
        }
        else res[i] = str[i];

        if(i % MAX_LENGTH == 0){
            int section_end = i+MAX_LENGTH;
            if(section_end < length) {
                for (int j = section_end; j > i; --j) {
                    if (str[j] == ' ') {
                        last_space_pos = j;
                        break;
                    }
                }
            }
        }
    }
    res[length] = '\0';

    return res;
}

char *join(char **list, int length, char* intersection){
    int str_length = 0;
    for (int i = 0; i < length; ++i) {
        str_length += strlen(list[i]);
    }
    char *res = malloc((str_length + 1 + (length * strlen(intersection))) * sizeof (char));
    strcpy(res, list[0]);
    for (int i = 1; i < length; ++i) {
        strcat(res, intersection);
        strcat(res, list[i]);
    }
//    strcat(res, "\0");
    return res;
}

char *readable_time(unsigned long int sec){
    char *res = (char*) malloc(16 * sizeof (char));
    int min = sec / 60;
    int left_sec = sec % 60;
    char snum[4];
    itoa(min, snum, 10);
    strcpy(res, snum);
    strcat(res, " min ");
    itoa(left_sec, snum, 10);
    strcat(res, snum);
    strcat(res, " sec");

    return res;
}