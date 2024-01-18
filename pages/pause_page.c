#include "../libs/utility.h"
#include "../libs/econio.h"
#include <stdio.h>
#include "pause_page.h"
#include "main_menu.h"
#include "choose_question.h"
#include "../libs/debugmalloc.h"
#include "row_question_page.h"
#include <time.h>

Page_Func pause_page(void *param){
    Pause_page_Params *params = param;
    Regular_Data *lists = params->lists;
    Question_Type type = params->type;
    display_title();

    if((type != ROW) && (type != STOP)){
        unsigned long int current_time =(unsigned long) time(NULL);
        unsigned long int time_sec = current_time - params->lists->settings->timestamp;
        params->lists->settings->time_sec = params->lists->settings->time_sec + time_sec;
        params->lists->settings->timestamp = 0;
    }
    Menu_Item fake_list[2] = {
            {"", "", main_menu, KEY_ENTER, NULL},
            {"", "", main_menu, KEY_ENTER, NULL},
    };
    Choose_question_Params chooseQuestionParams;
    if((type == CHOOSE) || (type == PAUSE_CHOOSE)){
//        chooseQuestionParams = (Choose_question_Params*) malloc(sizeof(Choose_question_Params));
        chooseQuestionParams.lists = lists;
    }
//    printf("%s - %p\n", lists->rowQuestion->question, lists->stats);

    if(type == CHOOSE){
        char *line_elements[2] ={"Jöhet a feleletválasztós kérdés?", "Enter - Igen"};
        char *line = justify_content(line_elements, 2,  SPACE_BETWEEN);
        if(line == NULL) printf("NULL line");

        chooseQuestionParams.question_num = -1;

        printf("%s\n", line);
        free(line);
        fake_list[0].function = choose_question;
        fake_list[0].KEY_CODE = KEY_ENTER;
        fake_list[0].param = &chooseQuestionParams;

        free(params);
        return wait_menu_input(fake_list, 1);
    }
    else if(type == PAUSE_CHOOSE){
        char *line_elements[1] ={"Helyes válasz. Tovább mész?"};
        char *line = justify_content(line_elements, 1,  CENTER);
        if(line == NULL) printf("NULL line");
        printf("%s\n", line);
        free(line);


        chooseQuestionParams.question_num = 0;
        fake_list[0].key = "Enter";
        fake_list[0].option = "Igen";
        fake_list[0].function = choose_question;
        fake_list[0].KEY_CODE = KEY_ENTER;
        fake_list[0].param = &chooseQuestionParams;

        Pause_page_Params PauseParams = {
                lists,
                STOP,
        };
        fake_list[1].key = "Esc";
        fake_list[1].option = "Nem";
        fake_list[1].function = pause_page;
        fake_list[1].KEY_CODE = KEY_ESCAPE;
        fake_list[1].param = &PauseParams;

        display_menu_items(fake_list, 2);

        return wait_menu_input(fake_list, 2);
    }
    else if(type == ROW){
        char *line_elements[2] ={"Jöhet a sorkérdés?", "Enter - Igen"};
        char *line = justify_content(line_elements, 2,  SPACE_BETWEEN);
        if(line == NULL) printf("NULL line");

        printf("%s\n", line);
        free(line);
        fake_list[0].function = row_question_page;
        fake_list[0].KEY_CODE = KEY_ENTER;
        fake_list[0].param = lists;

        return wait_menu_input(fake_list, 1);
    }
    else if(type == ROW_FAIL){
        char *line_elements[2] ={"Hibás válasz, próbáld újra!", "Enter - Mehet"};
        char *line = justify_content(line_elements, 2,  SPACE_BETWEEN);
        if(line == NULL) printf("NULL line");


        printf("%s\n", line);
        free(line);
        fake_list[0].function = row_question_page;
        fake_list[0].KEY_CODE = KEY_ENTER;
        fake_list[0].param = params->lists;

        free(params);
        return wait_menu_input(fake_list, 1);
    }
    else if(type == FAIL){
        lists->settings->prize = 0;
        char *line_elements[2] ={"Hibás válasz, vesztettél.", "Enter - Tovább"};
        char *line = justify_content(line_elements, 2,  SPACE_BETWEEN);
        if(line == NULL) printf("NULL line");
        printf("%s\n", line);
        free(line);

        char *menu_names[2] = {"Nyeremény", "Játék idõ"};
        char *menu_line = justify_content(menu_names, 2, SPACE_BETWEEN);
        printf("%s\n", menu_line);
        free(menu_line);
        char *data_row[2] = {"", readable_time(lists->settings->time_sec)};
        char snum[15];
        itoa(lists->settings->prize, snum, 10);
        strcat(snum, " Ft");
        data_row[0] = snum;
        char *data_line = justify_content(data_row, 2, SPACE_BETWEEN);
        printf("%s\n", data_line);
        free(data_line);
        free(data_row[1]);



        lists->settings->used_help = 1;
        fake_list[0].function = main_menu;
        fake_list[0].KEY_CODE = KEY_ENTER;

        change_stat(lists);
        write_stat_file(lists->stats);

        return wait_menu_input(fake_list, 1);
    }
    else if((type == WIN) || (type == STOP)){
        char *line_elements[2] ={(type == STOP ? "Megálltál!" : "Nyertél!"), "Enter - Tovább"};
        char *line = justify_content(line_elements, 2,  SPACE_BETWEEN);
        if(line == NULL) printf("NULL line");
        printf("%s\n", line);
        free(line);

        char *menu_names[2] = {"Nyeremény", "Játék idõ"};
        char *menu_line = justify_content(menu_names, 2, SPACE_BETWEEN);
        printf("%s\n", menu_line);
        free(menu_line);
        char *data_row[2] = {"", readable_time(lists->settings->time_sec)};
        char snum[15];
        itoa(lists->settings->prize, snum, 10);
        strcat(snum, " Ft");
        data_row[0] = snum;
        char *data_line = justify_content(data_row, 2, SPACE_BETWEEN);
        printf("%s\n", data_line);
        free(data_line);
        free(data_row[1]);

        lists->settings->used_help = 1;
        fake_list[0].function = main_menu;
        fake_list[0].KEY_CODE = KEY_ENTER;

        change_stat(lists);
        write_stat_file(lists->stats);

        return wait_menu_input(fake_list, 1);
    }

    Page_Func error = {
            NULL,
            NULL,
            -1,
    };
    return error;
}