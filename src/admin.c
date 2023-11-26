#include "admin.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bool logged_in = false;

static struct adm admins[] = {
    { .name="gaurav505", .pass="abcd"},
    { .name="gap505",    .pass="abcd"},
    { .name="hammer12",  .pass="abcd"}
};

static int get_user(char usr[25]) {

    for(int i = 0; i < 3; i++) {
        if(!strcmp(usr, admins[i].name)) return i;
    }

    return -1;
}

bool login_status() { return logged_in; }

bool login() {
    
    if(logged_in) {
        printf("Logout first!\n");
        return false;
    }
    
    char usr[25], pass[25];
    printf("Username: ");
    scanf("%s", usr);

    int uind = get_user(usr);
    if(uind == -1) {
        printf("User does not exist!!\n");
        return false;
    }
    
    printf("Password: ");
    scanf("%s", pass);

    if(strcmp(pass, admins[uind].pass))  {
        printf("Incorrect Password!!\n");
        return false;
    }

    logged_in = true;
    printf("%s Logged IN successfully\n", usr);

    return true;

}

bool logout() {
    if(!logged_in) {
        printf("No user to Logout!\n");
        return true;
    }

    printf("Logging Out...\n");
    logged_in = false;
    return true;
}
