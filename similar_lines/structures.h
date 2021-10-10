#ifndef STRUKTURY_H
#define STRUKTURY_H

typedef struct Notnumber_t {
    char *characters;
    int notnumber_size;
} Notnumber_t;


typedef struct List_t {
    struct List_t *next;

    struct Notnumber_t *notnumbers;
    int quantity_notnumbers;
    int max_quantity_notnumbers;

    char *data;
    int data_size;

    long double *numbers;
    int quantity_numbers;
    int max_quantity_numbers;

    int no;
    bool comment;
    bool incorrect;
    bool blank;


} List_t;

#endif /* STRUKTURY_H */