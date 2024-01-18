#include <stdio.h>
#include "../libs/utility.h"
#include "pause_page.h"
#include "../libs/debugmalloc.h"
#include <string.h>
#include "name_page.h"



Page_Func name_page(void *param) {
    Name_page_Params *params = param;
    display_title();

    char *line_elements[1] ={"Kérlek add meg a neved (max. 50):"};
    char *line = justify_content(line_elements, 1,  CENTER);

    printf("%s\n", line);
    free(line);
    char name[50];
    fgets(name, sizeof name, stdin);
    name[strlen(name)-1] = '\0';

    params->settings->name = (char*) malloc(sizeof (name));
    strcpy(params->settings->name, name);


    Pause_page_Params PauseParams = {
            params->lists,
            ROW,
    };
    Page_Func res = {
        pause_page,
        &PauseParams
    };

    return res;
}