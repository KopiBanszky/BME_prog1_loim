typedef enum Question_Type {
    ROW,
    CHOOSE,
    PAUSE_CHOOSE,
    FAIL,
    ROW_FAIL,
    WIN,
    STOP,
} Question_Type;

typedef struct Pause_page_Params {
    Regular_Data *lists;
    Question_Type type;
    Properties *settings;
} Pause_page_Params;

Page_Func pause_page(void *param);