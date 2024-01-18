#include "libs/debugmalloc.h"
#include "pages/main_menu.h"
#include <stdlib.h>
#include <time.h>
#include "libs/utility.h"
#include "libs/din_list_manager.h"
#include "libs/read_data_from_row_file.h"
#include "libs/manage_stat_file.h"

#ifdef _WIN32
    #include <windows.h>
#endif

//TODO: commentelgetés

int main() {
    /* Ékezetes szöveg kiírása miatt */
    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
    srand(time(NULL));

    char *loimFILE = validate_file("source/loim.csv", LOIM);
    char *sorokFILE = validate_file("source/sorok.csv", SOROK);


    Difficulties_list *list_for_different_difficulties[15]; /* 5 */
    for (int i = 0; i < 15; ++i) {
        list_for_different_difficulties[i] = NULL;
    }

    Choose_By_Question *loim_list;
    Row_Question *row_list;
    loim_list = load_loim_in_dinlist(loimFILE, list_for_different_difficulties);
    row_list = create_row_question_list(sorokFILE);
//    if(loim_list == NULL){
//    }
//    if(row_list == NULL){
//    }
    Properties settings = { /*2*/
            4, 75
    };
    settings.time_sec = 0;
    settings.used_help = 1;
    Properties preview = { /*3*/
            4, 75
    };
    Statistics *stats = stat_file();
    Regular_Data lists = {
            loim_list,
            row_list,
            list_for_different_difficulties,
            &settings,
            stats
    };
    Settings_menu_Param settingsMenuParam = {
            &lists,
            &settings,
            &preview
    };
    Main_menu_Params params = {
            &lists,
            &settingsMenuParam
    };

    Page_Func action = main_menu(&params);
    while(action.function != NULL){
        if(action.function == main_menu){
            action = main_menu(&params);
        }
        action = action.function(action.param);
    }
    /* Error kezelés */
    if(action.function == NULL){
        int err_code = action.key;
        if(err_code == 200) {
            printf("Sccuess - END\n");
            free(loimFILE);
            free(sorokFILE);
        }
        else {
            printf("Program vég\n");
        }
    }


    return 0;
}
