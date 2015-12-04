#ifndef UM_SNS_FUNCTIONS_H
#define UM_SNS_FUNCTIONS_H

#include "sns_structs.h"

// sns
int sns_json_file_read(Sns **self, char *filename);
int sns_json_file_write(Sns *self, char *filename);

int sns_init(Sns **self);
int sns_del(Sns **self);

int sns_search_people(Sns *self, int id, People **result_people);
int sns_insert_people(Sns *self, People *people, int id_given);
int sns_delete_people(Sns *self, People *people);

int sns_map_people(Sns *self, void *pipe, int (*callback)(const void *data, void *pipe));

// people
int people_init(Sns *universal, People **self, char name[100], int id, int id_given);
int people_del(Sns *universal, People **self);

int people_patch(People *self, char name[100], int id);
int people_follow(People *self, People *target);
int people_unfollow(People *self, People *target);
int people_friend(People *self, People *target);
int people_unfriend(People *self, People *target);

int people_followings(People *self, Circle **followings);
int people_followers(People *self, Circle **followers);
int people_friends(People *self, Circle **friends);
int people_common_followings(People *self, People *target, Circle **common_followings);
int people_common_followers(People *self, People *target, Circle **common_followers);
int people_extend_friends(People *self, Circle **extend_friends);

// circle
int circle_map_people(Circle *self, void *pipe, int (*callback)(const void *data, void *pipe));

#endif //UM_SNS_FUNCTIONS_H
