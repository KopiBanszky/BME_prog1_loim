typedef struct Properties{
    int difficulty;
    int vote_chance;
    char *name;
    int prize;
    unsigned long int time_sec;
    unsigned long int timestamp;
    int used_help; /*1 = None, 2 = felezés, 3 = szavazás, 6 = both */
} Properties;

typedef struct Page_Func{
    struct Page_Func (*function)(void*);
    void *param;
    int key;
} Page_Func;