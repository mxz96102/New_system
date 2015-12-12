#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sns_functions.h"
#include "set_functions.h"

int id_cmp(People *data1,People *data2);

int delete(void *aim);

// sns
int sns_json_file_read(Sns **self, char *filename){

}
int sns_json_file_write(Sns *self, char *filename){


}

int sns_init(Sns **self){
    Sns *temp;
    Set *people;
    temp = (Sns *) malloc(sizeof(Sns));
    if (temp == NULL)
        return 1;
    set_init(&people);
    temp->_peoples = people;
    *self = temp;
    return 0;
}

int sns_del(Sns **self){
    set_del(&(*self)->_peoples, delete);
    return 0;
}

int sns_search_people(Sns *self, int id, People **result_people){
    People *data, *result;
    int respond, flag;
    people_init(self, &data, "NULL", id, id);
    flag = set_search(self->_peoples, data, (void **) &result, &respond, (int (*)(const void *, const void *)) id_cmp);
    *result_people = result;
    return flag;
}
int sns_insert_people(Sns *self, People *people, int id_given){
    int flag;
    if (id_given <= self->peoples_id_max)
        return 2;
    flag = set_insert(&(self->_peoples), people, (int (*)(const void *, const void *)) id_cmp);
    if (flag)
        return 1;
    else
        return 0;
}
int sns_delete_people(Sns *self, People *people){
    int flag;
    flag = set_delete(&self->_peoples, people, (int (*)(const void *, const void *)) id_cmp);
    return flag;
}

int sns_map_people(Sns *self, void *pipe, int (*callback)(const void *data, void *pipe)){
    int flag = 1;
    flag = set_map(self->_peoples, pipe, *callback);
    return flag;
}

// people
int people_init(Sns *universal, People **self, char name[100], int id, int id_given){
    Set *temp;
    People *new_man;
    new_man = (People *) malloc(sizeof(People));
    if (new_man == NULL)
        return 1;
    set_init(&new_man->_followings);
    set_init(&new_man->_friends);
    set_init(&new_man->_followers);
    set_init(&new_man->__incoming_friends);
    strcpy(new_man->name, name);
    new_man->id = id;
    *self = new_man;
    return 0;
}

int people_del(Sns *universal, People **self){
    return 0;

}

int people_patch(People *self, char name[100], int id){
    strcpy(self->name, name);
    return 0;
}

int people_follow(People *self, People *target){
    int flag[2];
    flag[2] = set_insert(&(self->_followings), target, (int (*)(const void *, const void *)) id_cmp);
    flag[1] = set_insert(&(target->_followers), self, (int (*)(const void *, const void *)) id_cmp);
    if (flag[1] || flag[2])
        return 1;
    else
        return 0;
}
int people_unfollow(People *self, People *target){
    int flag[2];
    flag[2] = set_delete(&(self->_followings), target, (int (*)(const void *, const void *)) id_cmp);
    flag[1] = set_delete(&(target->_followers), self, (int (*)(const void *, const void *)) id_cmp);
    if (flag[1] || flag[2])
        return 1;
    else
        return 0;
}
int people_friend(People *self, People *target){
    int flag;
    flag = set_insert(&(self->_friends), target, (int (*)(const void *, const void *)) id_cmp);
    if (flag)
        return 1;
    else
        return 0;

}
int people_unfriend(People *self, People *target){
    int flag;
    flag = set_delete(&(self->_friends), target, (int (*)(const void *, const void *)) id_cmp);
    if (flag)
        return 1;
    else
        return 0;
}

int people_followings(People *self, Circle **followings){
    *(followings) = (Circle *) malloc(sizeof(Circle));
    (*followings)->_peoples = self->_followings;
    return 0;
}

int people_followers(People *self, Circle **followers){
    (*followers) = (Circle *) malloc(sizeof(Circle));
    (*followers)->_peoples = self->_followers;
    return 0;
}

int people_friends(People *self, Circle **friends){
    (*friends) = (Circle *) malloc(sizeof(Circle));
    (*friends)->_peoples = self->_followings;
    return 0;
}

int people_common_followings(People *self, People *target, Circle **common_followings){
    int flag;
    *common_followings = (Circle *) malloc(sizeof(Circle));
    flag = set_intersection(self->_followings, target->_followings, &((*common_followings)->_peoples),
                            (int (*)(const void *, const void *)) id_cmp);
    return flag;
}

int people_common_followers(People *self, People *target, Circle **common_followers){
    int flag;
    *common_followers = (Circle *) malloc(sizeof(Circle));
    flag = set_intersection(self->_followers, target->_followers, &((*common_followers)->_peoples),
                            (int (*)(const void *, const void *)) id_cmp);
    return flag;
}

int people_extend_friends(People *self, Circle **extend_friends){
    *extend_friends = (Circle *) malloc(sizeof(Circle));
    return 0;
}

// circle

int circle_map_people(Circle *self, void *pipe, int (*callback)(const void *data, void *pipe)){
    int flag = 1;
    flag = set_map(self->_peoples, pipe, *callback);
    return flag;
}


int id_cmp(People *data1,People *data2){
    if (data1->id==data2->id)
        return 0;
    else
        return 1;
}

