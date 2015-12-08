#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sns_functions.h"
#include "set_functions.h"

int id_cmp(People *data1,People *data2);

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

}

int sns_search_people(Sns *self, int id, People **result_people){
    People *data, *result;
    int respond;
    people_init(self, &data, NULL, id, id);
    set_search(self->_peoples, data, &result, &respond, id_cmp);
    return 0;

}
int sns_insert_people(Sns *self, People *people, int id_given){
    int8_t flag;
    if (id_given <= self->peoples_id_max)
        return 2;
    flag = set_insert(&(self->_peoples), people, id_cmp);
    if (flag)
        return 1;
    else
        return 0;
}
int sns_delete_people(Sns *self, People *people){

}

int sns_map_people(Sns *self, void *pipe, int (*callback)(const void *data, void *pipe)){

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
    return 0;
}
int people_del(Sns *universal, People **self){

}

int people_patch(People *self, char name[100], int id){

}
int people_follow(People *self, People *target){
    int flag[2];
    flag[2] = set_insert(&(self->_followings), target, id_cmp);
    flag[1] = set_insert(&(target->_followers), self, id_cmp);
    if (flag[1] || flag[2])
        return 1;
    else
        return 0;
}
int people_unfollow(People *self, People *target){
    int flag[2];
    flag[2] = set_delete(&(self->_followings), target, id_cmp);
    flag[1] = set_delete(&(target->_followers), self, id_cmp);
    if (flag[1] || flag[2])
        return 1;
    else
        return 0;
}
int people_friend(People *self, People *target){
    int flag;
    flag = set_insert(&(self->_friends), target, id_cmp);
    if (flag)
        return 1;
    else
        return 0;

}
int people_unfriend(People *self, People *target){
    int flag;
    flag = set_delete(&(self->_friends), target, id_cmp);
    if (flag)
        return 1;
    else
        return 0;
}

int people_followings(People *self, Circle **followings){
    (*followings)->_peoples = self->_followings;
    return 0;
}

int people_followers(People *self, Circle **followers){
    (*followers)->_peoples = self->_followers;
    return 0;
}

int people_friends(People *self, Circle **friends){
    (*friends)->_peoples = self->_followings;
    return 0;
}

int people_common_followings(People *self, People *target, Circle **common_followings){

}

int people_common_followers(People *self, People *target, Circle **common_followers){

}

int people_extend_friends(People *self, Circle **extend_friends){

}

// circle

int circle_map_people(Circle *self, void *pipe, int (*callback)(const void *data, void *pipe)){

}


int id_cmp(People *data1,People *data2){
    if (data1->id==data2->id)
        return 0;
    else
        return 1;

}