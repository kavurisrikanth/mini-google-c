/*
    Main file for project
*/

#include "testing.h"

int main(int argc, char const *argv[]) {
    /* code */
    if(argc != 2) {
        fprintf(stderr, "Wrong number of args!\n");
        fprintf(stderr, "Usage: ./file_ops <html_file>\n");
        return 1;
    }

    /*
     * argv[1] contains the search term(s).
     * To search, we need the list of files to search in.
     * So decide on the location of the HTML files,
     * and then search
    */
    bool lin = false;
    char *path = get_directory((char*)".", &lin),
         **files = NULL,
         **history = (char**)allocate(1024 * sizeof(char*));
    int num_files = 0, i = 0, hits = 0;
    files = get_all_html_files_in_dir(path, &num_files);
    printf("arg: %s\n", argv[1]);

    if(num_files != 0) {
        for(i = 0; i < num_files; i++)
            blabla(*(files + i), &history, &hits);
    }
    else
        printf("No HTML files found in %s\n", path);

    printf("\nFiles:\n");
    for(i = 0; i < num_files; i++)
        printf("file: %s\n", *(files + i));

    for(i = 0; i < num_files; i++)
        deallocate(*(files + i));
    deallocate(files);

    printf("\n\nHistory\n");
    for(i = 0; i < hits; i++)
        printf("%s\n", *(history + i));

    for(i = 0; i < hits; i++)
        deallocate(*(history + i));
    deallocate(history);

    deallocate(path);

    return 0;
}
