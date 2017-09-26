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
        // printf("checking: %s\n", *buffer);
        return true;
        // i++;
    }

    // printf("%ld\n", close_two - str);
    return false;
}

bool get_tag_link(char* str, char **buffer) {
    /*
        If the tag is an opening <a> tag, returns the link for the href
        attribute.
    */

    char *open, *quote_one, *quote_two;
    // char *close;
    int find = 0, i = 0;

    open = strchr(str, '<');
    // close = strchr(str, '>');

    if(open != NULL) {
        // it is a tag
        if(is_opening_tag(str)) {
            // opening tag
            if((find = search_in_str(str, (char*)"href")) != -1) {
                // printf("found at: %d\n", find);
                // printf("plus find: %s\n", str + find);
                quote_one = strchr(str + find, '"');
                quote_two = strchr(quote_one + 1, '"');

                // printf("q1: %s\n", quote_one);
                // printf("q2: %s\n", quote_two);
                // printf("diff: %d\n", quote_one - str);

                *buffer = (char*)allocate((quote_two - quote_one) * sizeof(char));
                strncpy(*buffer, quote_one + 1, quote_two - quote_one - 1);
                *(*buffer + (quote_two - quote_one)) = '\0';

                // only one href per tag.
                // printf("recorded: %s\n", *buffer);
                return true;
            }
        }
    }

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

bool is_opening_tag(char *str) {
    /*
        Checks if str contains an opening tag.
    */
    char *temp = strchr(str, '<');

    // there can't be a space between the < and the tag name
    return *(temp + 1) != '/';
}

int search_in_str(char *str, char *target) {
    /*
        Returns the index of the first occurrence of target in str.
        If target is not in str, then returns -1.
    */

    int i = 0, len = strlen(str), tlen = strlen(target);
    char *temp = (char*)allocate((1 + tlen) * sizeof(char));
    bool found = false;
    // int j = 0;

    for(i = 0; i < len - 1 - tlen; i++) {
        // j = i + tlen;
        memset(temp, 0, (1 + tlen) * sizeof(char));
        // memcpy()
        strncpy(temp, str + i, tlen);
        if(strcmp(temp, target) == 0) {
            // match found
            found = true;
            break;
        }
    }

    deallocate(temp);
    if(found)
        return i;
    else
        return -1;
}
