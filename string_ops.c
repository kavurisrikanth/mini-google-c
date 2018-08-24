/*
  String operations for project.
*/

#include "string_ops.h"

/**
 * This method returns the raw text between an opening tag and a closing tag.
 *
 * Inputs: str - The string to parse.
 *         buffer - The storage location of the result.
 * Returns: Success code, true or false.
 */
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

    char *open_one = strchr(str, '<'),
         *open_two = strrchr(str, '<'),
         *close_one = strchr(str, '>');

    // Opening tags are at different places on the same line, so the closing tags must be different.
    // So we're good.
    if(open_two != open_one) {
        // Allocate the buffer.
        *buffer = (char*)allocate((1 + strlen(str)) * sizeof(char));

        // Some witchcraft to copy the exact text.
        memcpy(*buffer,
                str + (close_one - str) + 1,
                (open_two - close_one - 1) * sizeof(char));

        // And terminate the string.
        *(*buffer + (open_two - close_one) - 1) = '\0';

        // We're done, so return true.
        return true;
    }

    // Some error in the string. So say so.
    return false;
}

/**
 * If the tag is an opening <a> tag, returns the link for the href attribute.
 *
 * Inputs: str - The tag string.
 *         buffer - The space for the result.
 * Result: Status code: true or false.
 */
bool get_tag_link(char* str, char **buffer) {

    char *open, *quote_one, *quote_two;

    int find = 0;

    open = strchr(str, '<');

    if(open != NULL) {
        // it is a tag
        if(is_opening_tag(str)) {
            // opening tag
            if((find = search_in_str(str, (char*)"href")) != -1) {
                quote_one = strchr(str + find, '"');
                quote_two = strchr(quote_one + 1, '"');

                *buffer = (char*)allocate((quote_two - quote_one) * sizeof(char));
                strncpy(*buffer, quote_one + 1, quote_two - quote_one - 1);
                *(*buffer + (quote_two - quote_one)) = '\0';

                // only one href per tag.
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

    int len = strlen(str), j = i;

    while(j <= len) {
        *(str + j - i) = *(str + j);
        j++;
    }
}

void strip(char *str, char delim) {
    /*
        Remove spaces from the left and right of str.
    */

    rstrip(str, delim);
    lstrip(str, delim);

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

void insert(char **history, char *str, int pos) {
    /*
        Insert str into the array of strings.
    */

    *(history + pos) = (char*)allocate((1 + strlen(str)) * sizeof(char));
    strcpy(*(history + pos), str);
}

bool visited(char **history, int num, char *str) {
    /*
        Searches history for str
    */

    int i = 0;
    printf("\n");
    for(i = 0; i < num; i++) {
        printf("Comparing %s and %s\n", *(history + i), str);
        if(strcmp(*(history + i), str) == 0)
            return true;
    }
    printf("\n");

    return false;
}
