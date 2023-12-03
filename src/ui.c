#include "ui.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>


/**
 * Frames for the UI are stored in ui.txt
 * Each frame is 44x15+8 ~ 700
 *   44 -> columns
 *   15 -> rows
 *   8 -> VT100 sequence terms
 * Total of 5 frames:
 *   1  -> STARTUP/IDLE
 *  2-5 -> MENU CHOICE
 */

// Array to hold frames of UI
static char frames[5][700];

// String holding output from last executed command
static char message[70];

// initialize frames from res/ui.txt
void init_frames()
{

    FILE *ui_file = NULL;
    // open res/ui.txt for reading frames
    ui_file = fopen("./res/ui.txt", "r+");
    if (ui_file == NULL)
        perror("Error opening file");
    for (int i = 0; i < 5; i++)
    {

        char px = fgetc(ui_file);
        int j, x_cnt = -2;
        for (j = 0; x_cnt && px != EOF; j++)
        {
            switch (px)
            {
            case '\\':
                fgetc(ui_file);
                frames[i][j] = '\033';
                break;

            default:
                frames[i][j] = px;
                break;
            }
            px = fgetc(ui_file);
            if (px == 'X')
                x_cnt++;
        }
        frames[i][j] = '\0';

        fgetc(ui_file);
    }

    fclose(ui_file);
}

// Display UI Frame
// @param Frame Frame number to be displayed
void display_ui(int Frame)
{
    if (!(Frame >= 0 && Frame < 5))
        return;

    // reset cursor position and style
    printf("\033[2J\033[H\033[0;0m");
    // print frame
    printf("%s", frames[Frame]);
    // save input cursor position
    printf("\033[2A\033[6C\033[s");
    // move cursor to message area
    printf("\033[H\033[5B\033[4C");
    // print message
    printf("%s", message);
    // restore saved cursor position
    printf("\033[u");
}

// Set Message
// @param Key int
// @param success bool
// @param str char*
void set_message(int Key, bool success, char *str) 
{
    
    // Clear str message
    strcpy(message, "\0");

    switch (Key)
    {
    case 1:
        if(success) 
            sprintf(message, "\033[32mSuccessfully added %s\033[0;0m", str);
        else
            sprintf(message, "\033[31mError in adding %s\033[0;0m", str);
        break;

    case 2:
        if(success)
            sprintf(message, "\033[32mSuccessfully deleted %s\033[0;0m", str);
        else
            sprintf(message, "\033[31m%s not in Dictionary\033[0;0m", str);
        break;

    case 3:
        if (success)
            sprintf(message, "\033[32m%s is Correct!!\033[0;0m", str);
        else
            sprintf(message, "\033[31m%s is Wrong!!\033[0;0m", str);
        break;

    case 4:            
        if (success)
            sprintf(message, "\033[32mSentence is spelled Correct!!\033[0;0m");
        else
            sprintf(message, "\033[31mSentence has Wrong spellings!!\033[0;0m");
        break;

    default:
        sprintf(message, "\033[31mInvalid Choice!!\033[0;0m");
        break;    
    }

}