#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <limits.h>
#include <stddef.h>
#include <string.h>

#define T_INT 0
#define T_FLOAT 1
#define T_DOUBLE 2
#define T_STRING 3
#define T_CHAR 4
#define T_LIST 10
#define T_DICT 20
#define NO_TYPE -1
#define NO_CHAR 255
#define INT_INFINITY INT_MAX

typedef struct NodeList {
    void *data;
    struct NodeList *next;
} NodeList;

typedef struct List {
    NodeList *head;
    NodeList *tail;
    int size;
    int type;
} List;

typedef struct NodeDict {
    char *key;
    void *data;
    struct NodeDict *next;
} NodeDict;

typedef struct Dict {
    NodeDict *head;
    NodeDict *tail;
    List *keys;
    int size;
    int d_type;
    int k_type;
} Dict;

int isinfInt(int value);
void cleanName(char *name);

typedef int (*EqFunc)(const void *, const void *);
EqFunc eqTest(const int type);

int eqInt(const void *a, const void *b);
int eqFloat(const void *a, const void *b);
int eqDouble(const void *a, const void *b);
int eqString(const void *a, const void *b);
int eqChar(const void *a, const void *b);

#endif