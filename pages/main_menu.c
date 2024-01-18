#include "../libs/econio.h"
#include "../libs/utility.h"
#include "settings_menu.h"
#include "../libs/din_list_manager.h"
#include "stat_page.h"

typedef struct Main_menu_Params{
    Regular_Data *lists;
    Settings_menu_Param *settingsMenuParam;
} Main_menu_Params;


/* Megjeleníti a fõmenüt */
Page_Func main_menu(void* param){
    Main_menu_Params *params = param;

    display_title();

    Regular_Data *lists = params->lists;

    Exit_Params exitParams = {
            lists,
    };
    Menu_Item main_menu_items[4] = {
            {"s", "Beállítások",   settings_menu,              's', params->settingsMenuParam},
            {"d", "Dicsõséglista", stat_menu,                  'd', params->settingsMenuParam},
            {"Enter", "Indítás",   start_game,                 KEY_ENTER, lists},
            {"Esc", "Kilépés",     (Page_Func (*)(void *)) app_exit, KEY_ESCAPE, &exitParams},
    };


    display_menu_items(main_menu_items, 4);

    return wait_menu_input(main_menu_items, 4);

}