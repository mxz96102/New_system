#ifndef UM_SNS_STRUCTS_H
#define UM_SNS_STRUCTS_H

#include "set_structs.h"

struct sns {
    int peoples_id_max;
    Set *_peoples;
};

struct people {
    int id;
    char name[100];
    Set *_followings;
    Set *_followers;
    Set *_friends;
    Set *__incoming_friends;
};

struct circle
{
    Set *_peoples;
};

typedef struct sns Sns;
typedef struct people People;
typedef struct circle Circle;

#endif //UM_SNS_STRUCTS_H
