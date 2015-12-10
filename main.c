#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sns_functions.h"

Sns *global;
int id;

int main(void) {
    int option = 1;
    while (option != 9) {
        option = menu();
        switch (option) {
            case 1:
                option = File();
            case 2:
            case 3:
            case 4:
            default:
                break;
        }
    }
}

int menu() {
    int option = 1;
    printf("\n################\n");
    printf("#\tUser system:\n");
    printf("#1.File operation\n");
    printf("#2.User operation\n");
    printf("#3.Sns operation\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    fscanf(stdin, "%1d", &option);
    return option;
}

int File() {
    int option = 1, flag = 1;
    printf("\n################\n");
    printf("#\tFile operation:\n");
    printf("#1.File Load\n");
    printf("#2.File Save\n");
    printf("#3.Back to main\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    while (option != 3 && flag != 0) {
        fscanf(stdin, "%1d", &option);
        switch (option) {
            case 1:
                flag = File_Load();
                break;
            case 2:
                flag = File_Save();
                break;
            case 3:
                break;
            default:
                break;
        }
    }
    return 0;
}

int File_Save() {
    int flag = 1;
    char file_name[255];
    printf("\nFile name:  ");
    fgets(file_name, 255, stdin);
    flag = sns_json_file_write(global, file_name);
    return flag;
}

int File_Load() {
    int flag = 1;
    char file_name[255];
    printf("\nFile name:  ");
    fgets(file_name, 255, stdin);
    flag = sns_json_file_read(&global, file_name);
    return flag;
}

int User() {
    int option = 1, flag = 1;
    printf("\n################\n");
    printf("#\tUser operation\n");
    printf("#1.User create\n");
    printf("#2.User information\n");
    printf("#3.User delete\n");
    printf("#4.Back to menu\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    while (option != 4 && flag != 0) {
        fscanf(stdin, "%1d", &option);
        switch (option) {
            case 1:
                flag = User_create();
                break;
            case 2:
                flag = User_information();
                break;
            case 3:
                flag = User_delete();
                break;
            case 4:
                break;
            default:
                break;
        }
    }
    return 0;
}

int User_create() {
    int flag = 1;
    People *user;
    char user_name[100];
    printf("please write your name: ");
    fflush(stdin);
    fgets(user_name, 255, stdin);
    people_init(global, &user, user_name, id, id);
    return 0;
}

int User_information() {

}

int User_delete() {

}