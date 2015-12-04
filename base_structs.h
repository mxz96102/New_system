#ifndef UM_BASE_STRUCTS_H
#define UM_BASE_STRUCTS_H

struct base {
    void *data;
    struct base*next;
};
typedef struct base Base;

#endif //UM_BASE_STRUCTS_H
