#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* join(char** str_arr, int num);

int main(void) {

    char* strs[3] = {
        "hello, world", "blah blah blah", "harry potter truly was a miserable child"
    };

    char *res = join(strs, 3);
    printf("finally: %s\n", res);
    free(res);

    return 0;
}

char* join(char** str_arr, int num) {

    int i = 0, len = 0;
    for(i = 0; i < num; i++)
        len += strlen(str_arr[i]);

    char *ans = (char*)calloc(1, (num + len) * sizeof(char));

    for(i = 0; i < num; i++) {
        strcat(ans, str_arr[i]);
        if(i != num - 1)
            strcat(ans, " ");
    }
    ans[len + num] = '\0';

    return ans;
}