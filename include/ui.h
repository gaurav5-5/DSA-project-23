#ifndef SPL_UI_H
#define SPL_UI_H

#include <stdbool.h>

void init_frames();
void display_ui(int Frame);
void set_message(int Key, bool success, char *str);


#endif // !SPL_UI_H