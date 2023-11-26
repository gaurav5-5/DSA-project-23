#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void prn_bin(int a, int bs) {
    int i = 31, fr = 1;
    while(i >= 0) {
        printf("%d", ((a >> i--) & 1) );
        if(!((i+1) % bs)) { printf(" | "); fr = 1;}
    }
    printf("\n");
}

static char *carr2b64(char *arr) {
    int sz = 3;
    
    int temp = 0x0;
    for(int i = 0; i < sz; i++)  
        if(arr[i] == '='  || arr[i] == '\0')
            temp <<= 8;
        else
            temp = (temp << 8) | arr[i];

    char *ret = (char*)calloc(4, sizeof(char));
    for(int i = 0; i < 4; i++) {
        char x = (temp >> (i*6)) & 0b00111111;
        switch(x) {
            case 0b00000000 ... 0b00011001:
            ret[3-i] = 'A' + x;
            break;

            case 0b00011010 ... 0b00110011:
            ret[3-i] = 'a' + x - 0b00011010;
            break;

            case 0b00110100 ... 0b00111101:
            ret[3-i] = '0' + x - 0b00110100;
            break;

            case 0b00111110:
            ret[3-i] = '+';
            break;

            case 0b00111111:
            ret[3-i] = '/';
            break;

            default:
            ret[3-i] = '=';
        }
    }

    return ret;
}

char *convb64(char *str) {

    int len = strlen(str);
    
    int b64len = ceil(len * 4 / 3) + 1;
    char *b64str = (char*)calloc(b64len, sizeof(char));
    b64str[0] = '\0';

    for(int i = 0; i < len; i+=3) {
        char *substr = (char*)calloc(3, sizeof(char));
        strncpy(substr, str+i, 3);
    
        substr = carr2b64(substr);
        strcat(b64str, substr);
    
        free(substr);
    }

    return b64str;
}


static char *b642carr3(char *b64str3) {
    
    char *ret = (char*)calloc(3, sizeof(char));
    
    int temp = 0x0;
    for (int i = 0; i < 4; i++) {
        temp <<= 6;
        if(!(b64str3[i] == '='  || b64str3[i] == '\0'))
            temp |= b64str3[i];
    }

        // printf("%d ",temp);

    //convert chars into 6bit blocks
    int oldblk = 0x0;
    for (int i = 3; i >= 0; i--) {
        char ch = (char)((temp >> (i*6)) & 0b00111111);
    
        switch (ch)
        {
        case 'A' ... 'Z':
            ch = ch - 'A';
            break;

        case 'a' ... 'z':
            ch = ch + 0b00011010 - 'a';
            break;

        case '0' ... '9':
            ch = ch + 0b00110100 - '0';
            break;

        case '+':
            ch = 0b00111110;
            break;

        case '/':
            ch = 0b00111111;
            break;

        default:
            break;
        }


        oldblk = (oldblk << 6) | ch;
    }
    // printf("%d ", oldblk);
    prn_bin(oldblk,6);


    for(int i = 0; i < 3; i++) {
        char ch = (oldblk>>(i*8))&0b01111111;
        // printf("%d ", ch);
        ret[2-i] = ch;
    }
    prn_bin(oldblk,8);

    return ret;
    
}

char *convASCII(char *str) {
    
    int len = strlen(str);

    int asciilen = ceil(len*3/4)+1;
    char *asciistr = (char*)calloc(asciilen, sizeof(char));
    asciistr[0] = '\0';

    for(int i = 0; i < len; i+=4) {
        char *substr = (char*)calloc(4, sizeof(char));
        strncpy(substr, str+i, 4);

        substr = b642carr3(substr);
        strcat(asciistr, substr);

        free(substr);
    }

    return asciistr;
}

int main() 
{
    char a[] = "abcdef";
    char *b64 = convb64(a);
    char *asc = convASCII(b64);

    printf("origin: %s\nbase64: %s\nb642as: %s",a,b64,asc);
    return 0;
}