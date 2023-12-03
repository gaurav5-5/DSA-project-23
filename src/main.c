#include "trie.h"
#include "ui.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/***********************************************
|  * .-. .-. .-. .   .   .-. . . .-. .-. . .   |
|  * `-. |-' |-  |   |   |   |-| |-  |   |<    |
|  * `-' '   `-' `-' `-' `-' ' ` `-' `-' ' `   |
|  * Spelling Checker Application              |
|----------------------------------------------|
|  * @author Gaurav Prajapati   11             |
|  * @author Sourabh Bhosale    48             |
|  * @author Vivaswan Sapre     57             |
|----------------------------------------------|
|  * SY BTech ECE                              |
|  * Div. B - B3                               |
|----------------------------------------------|
|  * This is a C program to check correctness  |
|  * of an input spelling.                     |
|                                              |
|  * It uses a trie data structure having      |
|  * 27 subnodes for storing words.            |
***********************************************/

int main()
{

    init_frames();

    tnode *DICT = file_to_trie();

    int opt = 0;
    bool res = false;

    char buf[32],ch;
    
    // start alternative buffer
    printf("\033[?1049h");
    
    do
    {
        // display frame for menu [0]
        display_ui(0);
        fflush(stdin);
        scanf("%d", &opt);
        // display selected option [opt]
        display_ui(opt);
        
        fflush(stdin);
        
        switch (opt)
        {
        case 1:
            scanf("%s", buf);
            tn_insert(buf, DICT);
            if(check_word(buf,DICT)) res = true;
            else res = false;
            break;

        case 2:
            scanf("%s", buf);
            res = tn_delete(buf, DICT);
            break;

        case 3:
            scanf("%s", buf);
            res = check_word(buf, DICT);
            break;

        case 4:
            // get rid of leading \n in input buffer
            while((ch = fgetc(stdin)) == '\n');
            buf[0] = ch;
            buf[1] = '\0';
            scanf("%[^\n]", buf+1);
            res = check_sentence(buf, DICT);
            break;

        default:
            break;
        }
        // set message line
        set_message(opt,res,buf);

    } while (opt);
    // close alternate buffer
    printf("\033[?1049l");

    // free up memory taken by trie
    tn_free(&DICT);

    return 0;
}