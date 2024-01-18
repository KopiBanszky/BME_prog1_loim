#include "../libs/utility.h"
#include "settings_menu.h"

Page_Func main_menu(void* param);

typedef struct Main_menu_Params{
    Regular_Data *lists;
    Settings_menu_Param *settingsMenuParam;
} Main_menu_Params;
