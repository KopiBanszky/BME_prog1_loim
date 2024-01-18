#ifndef LEGYEN_ON_IS_MILLIOMOS_UTILITY
#define LEGYEN_ON_IS_MILLIOMOS_UTILITY

#include "../properties.h"
#include "read_data.h"
#include "read_data_from_row_file.h"
#include "manage_stat_file.h"


typedef struct Menu_Item{
    char *key;
    char *option;
    Page_Func (*function)(void*);
    int KEY_CODE;
    void* param;
} Menu_Item;

typedef enum Aligments{
    CENTER,
    SPACE_BETWEEN,
    SPACE_AROUND,
    RIGHT
} Aligments;

typedef struct Regular_Data{
    Choose_By_Question *chooseByQuestion;
    Row_Question *rowQuestion;
    Difficulties_list **difficulty_list;
    Properties *settings;
    Statistics *stats;
} Regular_Data;

typedef struct Start_Params {
    Regular_Data *lists;
    void *settings;
} Start_Params;

typedef struct Exit_Params {
    Regular_Data *lists;
    void *settings;
} Exit_Params;

//int int_parse(char* str);

void display_title();

int display_menu_items(Menu_Item item_list[], int length);

Page_Func wait_menu_input(Menu_Item item_list[], int length);

Page_Func app_exit(void *param);

Page_Func start_game(void *param);

int *count_chars_between_char(char *str, char str_end);

char *justify_content(char **line, int list_length, Aligments align);

char *break_line_at_last_space(char *str);

char *join(char **list, int length, char* intersection);

char **split(char *str, char section_char);

void free_split(char **list);

char *readable_time(unsigned long int sec);

#endif