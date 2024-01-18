#include "../libs/utility.h"
#include "../libs/debugmalloc.h"
#include "../libs/din_list_manager.h"
#include <stdlib.h>
#include "pause_page.h"
#include <time.h>

typedef struct Answer_Data{
    int key;
    Row_Question *question;
    Regular_Data *lists;
    struct Answer_Data *others[3];
} Answer_Data;

Page_Func test_row_answer(void *param){
    Answer_Data *answer = param;
    Row_Question *question = answer->question;
    Regular_Data *main_lists = answer->lists;
    Answer_Data A = {'A', question, main_lists};
    Answer_Data B = {'B', question, main_lists};
    Answer_Data C = {'C', question, main_lists};
    Answer_Data D = {'D', question, main_lists};
    Menu_Item answers_list[4] = {
            {"a",question->answerA, test_row_answer, 'a', &A},
            {"b",question->answerB, test_row_answer, 'b', &B},
            {"c",question->answerC, test_row_answer, 'c', &C},
            {"d",question->answerD, test_row_answer, 'd', &D},
    };
    char key = answer->key;
    static Row_Question *saved = NULL;
    static char given_ans[5];
    static int len = 0;
    if(saved != question){
        saved = question;
        given_ans[0] = '\0';
        given_ans[1] = '\0';
        given_ans[2] = '\0';
        given_ans[3] = '\0';
        len = 0;
    }
    if(strchr(given_ans, key) != NULL) return wait_menu_input(answers_list, 4);
    given_ans[strlen(given_ans)] = key;
    given_ans[strlen(given_ans)] = '\0';
    ++len;
    if(len == 4){
        Pause_page_Params *PauseParams = (Pause_page_Params*) malloc(sizeof (Pause_page_Params));
        PauseParams->lists = main_lists;
        Page_Func res = {
                pause_page,
                PauseParams,
        };
        if(strcmp(given_ans, question->answer) == 0){
            saved = NULL;
            given_ans[0] = '\0';
            given_ans[1] = '\0';
            given_ans[2] = '\0';
            given_ans[3] = '\0';
            len = 0;
            PauseParams->type = CHOOSE;
            return res;
        }
        else{
            saved = NULL;
            given_ans[0] = '\0';
            given_ans[1] = '\0';
            given_ans[2] = '\0';
            given_ans[3] = '\0';
            len = 0;
            PauseParams->type = ROW_FAIL;
            return res;
        }
    }
    else{
        if(len==1){
            free(answer->others[0]);
            free(answer->others[1]);
            free(answer->others[2]);
            free(answer);
        }
        return wait_menu_input(answers_list, 4);
    }
}

Page_Func row_question_page(void *param){
    Regular_Data *params = param;
    Row_Question *questions = params->rowQuestion;
    display_title();
    int rand_q = rand() % din_length_row(questions);
    Row_Question *rand_question = get_row_question_by_number(rand_q, questions);
    char *line[2] = {rand_question->question , rand_question->category};

    params->settings->timestamp = (unsigned long) time(NULL);

    Answer_Data *A = (Answer_Data*) malloc(sizeof (Answer_Data));
    A->key = 'A';
    A->lists = params;
    A->question = rand_question;

    Answer_Data *B = (Answer_Data*) malloc(sizeof (Answer_Data));
    B->key = 'B';
    B->lists = params;
    B->question = rand_question;

    Answer_Data *C = (Answer_Data*) malloc(sizeof (Answer_Data));
    C->key = 'C';
    C->lists = params;
    C->question = rand_question;

    Answer_Data *D = (Answer_Data*) malloc(sizeof (Answer_Data));
    D->key = 'D';
    D->lists = params;
    D->question = rand_question;
    D->others[0] = B->others[0] = C->others[0] = A;
    D->others[1] = A->others[0] = C->others[1] = B;
    D->others[2] = A->others[1] = B->others[1] = C;
    A->others[2] = B->others[2] = C->others[2] = D;


//    printf("%s\n", rand_question->answer);
    Menu_Item answers_list[4] = {
            {"a", rand_question->answerA, test_row_answer, 'a', A},
            {"b", rand_question->answerB, test_row_answer, 'b', B},
            {"c", rand_question->answerC, test_row_answer, 'c', C},
            {"d", rand_question->answerD, test_row_answer, 'd', D},
    };


    char *joined_line = join(line, 2, " - ");
    char *styled_row = break_line_at_last_space(joined_line);
    printf("%s\n", styled_row);
    free(styled_row);
    free(joined_line);

    display_menu_items(answers_list, 4);

    return wait_menu_input(answers_list, 4);
}