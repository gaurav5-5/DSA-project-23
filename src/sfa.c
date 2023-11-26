#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************
|  * .-. .-. .-. .   .   .-. . . .-. .-. . .   |
|  * `-. |-' |-  |   |   |   |-| |-  |   |<     |
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

// boolean typing
// 0 is falsy in C
// values other than 0 are truthy
#ifndef bool
#define bool unsigned char
#define true 1
#define false 0
#endif

// macro for freeing pointer
#define freeptr(_ptr)   \
    if ((_ptr) != NULL) \
        free((_ptr));

// structure definition for trie
typedef struct trie_node
{
    bool end;
    struct trie_node **letters;
} tnode;

/**
 * Node Creation Function for trie
 * @retval tnode*
 */
tnode *trie_init()
{
    tnode *new = (tnode *)calloc(1, sizeof(tnode));
    new->end = false;
    new->letters = (tnode **)calloc(27, sizeof(tnode *)); // calloc to prevent garbage values

    return new;
}

/**
 * insert a word inside the dictionary
 * @param *Word pointer to Word to be added
 * @param *Dictionary Pointer to dictionary to add to
 */
void str_to_tree(char *Word, tnode *Dictionary)
{

    tnode *current, *previous;
    current = previous = Dictionary;
    int index = 26;

    for (char *letter = Word; *letter != '\0'; letter++)
    {

        switch (*letter)
        {
        case '\'':
            index = 26;
            break;

        default:
            if (*letter <= 'Z')
                *letter = ((char)((int)(*letter) + 32));
            index = (*letter) - 97;
            break;
        }
        if (current->letters[index] == NULL)
        {
            current->letters[index] = trie_init();
        }
        previous = current;
        current = current->letters[index];
    }
    if (!previous->end)
        previous->end = true;
}

/** check spelling using trie
 * @param *Word pointer to Word to be checked
 * @param *Dictionary pointer to dictionary to check with
 */
bool checkspell(char *Word, tnode *Dictionary)
{

    tnode *previous, *current;
    previous = current = Dictionary;
    int index = 26;

    for (char *letter = Word; *letter != '\0' && *letter != ' ' && *letter != '\n'; letter++)
    {

        previous = Dictionary;
        switch (*letter)
        {
        case '\'':
            index = 26;
            break;

        default:
            if (*letter <= 'Z')
                *letter = (char)((int)(*letter) + 32);
            index = *letter - 97;
            break;
        }
        current = current->letters[index];
        if (current == NULL)
            return false;
    }
    if (!(previous->end))
        return false;
    return true;
}

bool checksentence(char *Sentence, tnode *Dictionary)
{

    bool res = true;
    for (char *lptr = Sentence; res && *lptr != '\0'; lptr++)
    {
        if (lptr == Sentence)
            res = checkspell(lptr, Dictionary);
        else if (*lptr == ' ')
            res = checkspell(++lptr, Dictionary);
    }

    return res;
}

void free_trie(tnode **head)
{
    if (*head == NULL)
        return;
    for (int i = 0; i < 27; i++)
    {
        free_trie(&((*head)->letters[i]));
    }
    freeptr(*head);
}

/**
 * Dictionary to be preloaded is stored
 * in Plaintext[.txt] format.
 *
 * Each word is on a new line
 *
 * FILE STRUCTURE:
 * +-------------------+
 * | word1(\n)         |
 * | word2(\n)         |
 * | ...               |
 * | lastWord(EOF)     |
 * +-------------------+
 */

void file_to_trie(tnode **Dictionary)
{

    tnode *new = trie_init();
    FILE *dfile = fopen("./res/words.txt", "r");
    // system("cd");
    // assert(dfile);

    char letter;
    int index = 0;
    char *word = (char *)malloc((0x64) * sizeof(char));
    while (true)
    {

        letter = getc(dfile);

        /*
         * Pressing the ENTER key on windows outputs 2 characters:
         * '\r' -> Carriage Return [Bring cursor to start of line]
         * '\n' -> New Line        [Go to Next line]
         * This line is to fix any errors due to '\r'
         */
        if (letter == '\r')
            continue;

        if (letter == '\n' || letter == EOF)
        {

            word[index] = '\0';
            str_to_tree(word, new);
            index = -1;

            if (letter == EOF)
                break;
        }
        else
            word[index] = letter;

        index++;
    }
    fclose(dfile);
    freeptr(word);

    *Dictionary = new;
    new = NULL;
}

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

// array to hold frames
static char frames[5][700];

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

int main()
{

    printf("\033[?1049h");
    init_frames();
    tnode *DICT = trie_init();
    file_to_trie(&DICT);
    int opt = 0;
    bool res = false;
    do
    {
        char buf[32];
        // _flushall();
        display_ui(0);
        scanf("%d", &opt);
        display_ui(opt);
        switch (opt)
        {
        case 1:
            scanf("%s", buf);
            str_to_tree(buf, DICT);
            strcpy(message, "\0");
            sprintf(message, "\033[32mSuccessfully added %s\033[0;0m", buf);
            break;

        case 2:
            scanf("%s", buf);
            str_to_tree(buf, DICT);
            strcpy(message, "\0");
            sprintf(message, "\033[32mSuccessfully deleted %s\033[0;0m", buf);
            break;

        case 3:
            scanf("%s", buf);
            res = checkspell(buf, DICT);
            strcpy(message, "\0");
            if (res)
                sprintf(message, "\033[32m%s is Correct!!\033[0;0m", buf);
            else
                sprintf(message, "\033[31m%s is Wrong!!\033[0;0m", buf);
            break;

        case 4:
            fflush(stdin);
            scanf("%[\n]%[^\n]", buf, buf);
            res = checksentence(buf, DICT);
            strcpy(message, "\0");
            if (res)
                sprintf(message, "\033[32mSentence is fully Correct!!\033[0;0m");
            else
                sprintf(message, "\033[31mSentence has Wrong words!!\033[0;0m");
            break;

        default:
            break;
        }
    } while (opt);
    printf("\033[?1049h");

    free_trie(&DICT);

    return 0;
}