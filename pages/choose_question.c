#include "../libs/utility.h"
#include "../libs/din_list_manager.h"
#include "../libs/debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "main_menu.h"
#include <ctype.h>
#include "choose_question.h"
#include "pause_page.h"
#include <time.h>


typedef struct Show_help_Params {
    Regular_Data *lists;
    Choose_By_Question *question;
    int question_count;
    int key;
} Show_help_Params;

Page_Func show_help(void* param){
    Show_help_Params *params = param;
    int question_count = params->question_count;
    Choose_By_Question *question = params->question;
    Regular_Data *lists = params->lists;
    int key = params->key;
    char *line[2] = {question->question ,question->category};
    char sdifficulty[4];
    itoa(lists->settings->difficulty, sdifficulty, 10);
    char sprize[10];
    itoa(lists->settings->prize, sprize, 10);
    strcat(sprize, " Ft");
    char answer_smoll = tolower(question->answer);
    display_title();
//    printf("%c", question->answer);


    Pause_page_Params pausePageParams_w = {
            lists,
            FAIL,
            lists->settings
    };
    Pause_page_Params pausePageParams_r = {
            lists,
            question_count == 15 ? WIN : PAUSE_CHOOSE,
            lists->settings
    };

    Show_help_Params help_h = {
            lists,
            question,
            question_count,
            'h'
    };
    Show_help_Params help_v = {
            lists,
            question,
            question_count,
            'v'
    };

    Menu_Item answerslist[8] = {
            {"a",         question->answerA, pause_page, 'a', answer_smoll == 'a' ? &pausePageParams_r : &pausePageParams_w},
            {"b",         question->answerB, pause_page, 'b', answer_smoll == 'b' ? &pausePageParams_r : &pausePageParams_w},
            {"c",         question->answerC, pause_page, 'c', answer_smoll == 'c' ? &pausePageParams_r : &pausePageParams_w},
            {"d",         question->answerD, pause_page, 'd', answer_smoll == 'd' ? &pausePageParams_r : &pausePageParams_w},
            {"Nehézség",  sdifficulty,       NULL,        '_', NULL},
            {"h",         "Felezés",   show_help,   'h', &help_h},
            {"Nyeremény", sprize,            NULL,        '_', NULL},
            {"v",         "Szavazás",  show_help,   'v', &help_v},
    };

    if(key == 'h'){
        int first_delete = rand() % 4;
        while (answerslist[first_delete].KEY_CODE == answer_smoll)
            first_delete = rand() % 4;
        int secound_delete = rand() % 4;
        while ((secound_delete == first_delete) || (answerslist[secound_delete].KEY_CODE == answer_smoll))
            secound_delete = rand() % 4;
        answerslist[first_delete].option = "";
        answerslist[first_delete].KEY_CODE = '-';
        answerslist[secound_delete].option = "";
        answerslist[secound_delete].KEY_CODE = '-';
        lists->settings->used_help *= 2;
    }
    else if(key == 'v'){
        int is_OK = rand() % 100;
        if(is_OK < lists->settings->vote_chance){
            for (int i = 0; i < 4; ++i) {
                if(answer_smoll == answerslist[i].KEY_CODE){
                    char temp_ans[2];
                    temp_ans[0] = question->answer;
                    temp_ans[1] = '\0';
                    answerslist[i].key = temp_ans;
                    break;
                }
            }
        }
        else{
            int wrong_i = rand() % 4;
            while (answerslist[wrong_i].KEY_CODE == answer_smoll)
                wrong_i = rand() % 4;
            char temp_ans[2];
            temp_ans[0] = toupper(answerslist[wrong_i].key[0]);
            temp_ans[1] = '\0';
            answerslist[wrong_i].key = temp_ans;
        }
        lists->settings->used_help *= 3;
    }

    if(lists->settings->used_help % 2 == 0){
        answerslist[5].key = "Felhasználva";
        answerslist[5].KEY_CODE = '-';
    }
    if(lists->settings->used_help % 3 == 0){
        answerslist[7].key = "Felhasználva";
        answerslist[7].KEY_CODE = '-';
    }
    char *joined_line = join(line, 2, " - ");
    char *styled_row = break_line_at_last_space(joined_line);
    printf("%d:\n%s\n", question_count, styled_row);
    free(styled_row);
    free(joined_line);

    display_menu_items(answerslist, 8);

    return wait_menu_input(answerslist, 8);
}

Page_Func choose_question(void *param){
    Choose_question_Params *params = param;
    Regular_Data *lists = params->lists;
    int is_first = params->question_num;
    static int question_count = 0;
    if(is_first == -1) question_count = 0;
    ++question_count;
    params->question_num = 0;
    Properties *settings = params->lists->settings;
    settings->prize = 0;
    if(question_count > 5)
        settings->prize = 50000;
    if(question_count > 10)
        settings->prize = 100000;
    if(question_count == 15)
        settings->prize = 150000;

    display_title();
    Difficulties_list **difficultyList = lists->difficulty_list;
    int length = din_length_diff(difficultyList[settings->difficulty + 1]);
    int rand_q = rand() % length -1;
    Choose_By_Question *question = get_question_by_number(settings->difficulty, rand_q, difficultyList);
    char *line[2] = {question->question ,question->category};
    char sdifficulty[4];
    itoa(settings->difficulty, sdifficulty, 10);
    char sprize[10];
    itoa(settings->prize, sprize, 10);
    strcat(sprize, " Ft");
    char answer_smoll = tolower(question->answer);

    settings->timestamp = (unsigned long) time(NULL);


//    printf("%c", question->answer);
//    printf("%d\n", lists->settings->used_help);


    Pause_page_Params pausePageParams_w = {
            lists,
            FAIL,
            settings
    };
    Pause_page_Params pausePageParams_r = {
            lists,
            question_count == 15 ? WIN : PAUSE_CHOOSE,
            settings
    };

    Show_help_Params help_v = {
            lists,
            question,
            question_count,
            'v'
    };
    Show_help_Params help_h = {
            lists,
            question,
            question_count,
            'h'
    };

    Menu_Item answerslist[8] = {
            {"a",         question->answerA, pause_page, 'a', answer_smoll == 'a' ? &pausePageParams_r : &pausePageParams_w},
            {"b",         question->answerB, pause_page, 'b', answer_smoll == 'b' ? &pausePageParams_r : &pausePageParams_w},
            {"c",         question->answerC, pause_page, 'c', answer_smoll == 'c' ? &pausePageParams_r : &pausePageParams_w},
            {"d",         question->answerD, pause_page, 'd', answer_smoll == 'd' ? &pausePageParams_r : &pausePageParams_w},
            {"Nehézség",  sdifficulty,       NULL,        '_', NULL},
            {"h",         "Felezés",   show_help,   'h', &help_h},
            {"Nyeremény", sprize,            NULL,        '_', NULL},
            {"v",         "Szavazás",  show_help,   'v', &help_v},
    };
    if(settings->used_help % 2 == 0){
        answerslist[5].key = "Felhasználva";
        answerslist[5].KEY_CODE = '-';
    }
    if(settings->used_help % 3 == 0){
        answerslist[7].key = "Felhasználva";
        answerslist[7].KEY_CODE = '-';
    }
    char *joined_line = join(line, 2, " - ");
    char *styled_row = break_line_at_last_space(joined_line);
    printf("%d:\n%s\n", question_count, styled_row);
    free(styled_row);
    free(joined_line);

    display_menu_items(answerslist, 8);



//    free(param);
    return wait_menu_input(answerslist, 8);
}