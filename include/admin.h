#ifndef ADMIN_H
#define ADMIN_H

# include <stdbool.h>

struct adm {
    char name[25];
    char pass[25];
}; 

bool login_status();
bool login();
bool logout();


#endif //! ADMIN_H
