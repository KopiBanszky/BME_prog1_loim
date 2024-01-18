#ifndef LEGYEN_ON_IS_MILLIOMOS_NAME_PAGE
#define LEGYEN_ON_IS_MILLIOMOS_NAME_PAGE

#include "../libs/utility.h"
#endif

typedef struct Name_page_Params {
    Regular_Data *lists;
    Properties *settings;
} Name_page_Params;


Page_Func name_page(void *param);
