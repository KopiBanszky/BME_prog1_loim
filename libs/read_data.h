#ifndef READ_DATA_H
#define READ_DATA_H

typedef struct Choose_By_Question{
    int difficulty;
    char *question;
    char *answerA;
    char *answerB;
    char *answerC;
    char *answerD;
    char answer;
    char *category;
    struct Choose_By_Question *next;
} Choose_By_Question;

typedef struct Difficulties_list{
    Choose_By_Question *question;
    struct Difficulties_list *next;
} Difficulties_list;

typedef enum FILE_TYPE{
    LOIM,
    SOROK
} File_type;


char *validate_file(char *path, File_type fileType);


Choose_By_Question *load_loim_in_dinlist(char *pathToFile, Difficulties_list *list_for_different_difficulties[]);
#endif // READ_DATA_H