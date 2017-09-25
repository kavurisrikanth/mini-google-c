/*
  String operations for project.
*/

#include "string_ops.h"

bool get_tag_text(char* str, char **buffer) {
    /*
        str is basically a string from < to >.
        In this function, we just return the text between
        the opening and closing tags like
        <tag>this text here</tag>.

        Future functions might break the tag down and return
        all of the info within it like tag name, tag attributes
        etc.

        buffer is where we fill in the data.
    */

    // printf("received str: %saaa\n", str);

    char *open_one, *open_two, *close_one, *close_two;
    // int i = 0;

    open_one = strchr(str, '<');
    close_one = strchr(str, '>');
    open_two = strrchr(str, '<');
    close_two = strrchr(str, '>');

    if(open_two != open_one) {
        // Opening tags are at different places on the same line
        // so the closing tags must be different
        *buffer = (char*)allocate((1 + strlen(str)) * sizeof(char));
        memcpy(*buffer,
                str + (close_one - str) + 1,
                (open_two - close_one - 1) * sizeof(char));
        *(*buffer + (open_two - close_one) - 1) = '\0';
        printf("checking: %s\n", *buffer);
        return true;
        // i++;
    }

    printf("%ld\n", close_two - str);
    return false;
}

bool get_tag_link(char* str, char **buffer) {

    return false;
}

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

    if(i == 0)
        return;

    memcpy(str, str + i, (strlen(str) - i) * sizeof(char));
    *(str + strlen(str) - i) = '\0';
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