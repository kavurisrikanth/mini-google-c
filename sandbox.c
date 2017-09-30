#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rstrip(char *str, char delim) {
    /*
        Remove spaces from the end of str.
    */
    char *temp;
    do {
        temp = strrchr(str, delim);
        if(temp != NULL && *(temp + 1) == '\0')
            *temp = '\0';
    } while(temp != NULL && *(temp + 1) == '\0');
}

void lstrip(char *str, char delim) {
    /*
        Remove spaces from the start of str.
    */
    int i = 0;
    while(*(str + i) == delim) {
        i++;
    }

    // printf("str: %s, i: %d\n", str, i);

    if(i == 0)
        return;

    int len = strlen(str), j = i;
    // printf("\ni: %d\n", i);
    // printf("str pre-memcpy: %s\n", str);
    // memcpy(str, str + i, (len - 1 - i) * sizeof(char));
    while(j <= len) {
        *(str + j - i) = *(str + j);
        j++;
    }
    // *(str + (len - 1 - i)) = '\0';
    // printf("str post-memcpy: %shahaha\n\n", str);
}

void strip(char *str, char delim) {
    /*
        Remove spaces from the left and right of str.
    */

    // printf("stripping: %s\n", str);

    rstrip(str, delim);
    // printf("right stripped: %s\n", str);
    lstrip(str, delim);

    // printf("verdict: %s\n", str);
}

int main(void) {

    FILE *fp = fopen("index.html", "r");

    if(fp == NULL) {
        fprintf(stderr, "file opening failed\n");
        return 1;
    }

    char *str = (char*)calloc(1, 1024 * sizeof(char));

    while(fgets(str, 1024, fp) != NULL) {
        strip(str, '\n');
        strip(str, ' ');
        //
        printf("%sblabla\n", str);
    }

    free(str);
    fclose(fp);
    return 0;
}