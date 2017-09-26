#include "file_ops.h"
#include "memory.h"
#include "string_ops.h"

int main(int argc, char const *argv[]) {
  /* code */

  if(argc != 2) {
    fprintf(stderr, "Wrong number of args!\n");
    fprintf(stderr, "Usage: ./file_ops <html_file>\n");
    return 1;
  }

  int count = 0, i = 0, link_count = 0;
  char **strings = NULL, **links = NULL;

  bool lin = false;
  char  *temp = (char*)allocate(1024 * sizeof(char));
  strcpy(temp, argv[1]);
  char *path = get_directory(temp, &lin);
  printf("path: %s\n", path);

  strings = (char**)allocate(1024 * sizeof(char*)),
  links = (char**)allocate(1024 * sizeof(char*));

  remove_tags((char*)argv[1], &count, &link_count, strings, links);

#if 1
  printf("\n\nFinally...\n");
  for(i = 0; i < count; i++)
    printf("%s\n", *(strings + i));

    // printf("\n");
    // for(i = 0; i < link_count; i++)
    //     printf("%s\n", *(links + i));
#endif

    FILE *fp = NULL;
    // char ;
    for(i = 0; i < link_count; i++) {
        memset(temp, 0, 1024 * sizeof(char));
        strcat(temp, path);
        strcat(temp, "/");
        strcat(temp, *(links + i));
        printf("%s\n", temp);
        if((fp = fopen(temp, "r")) != NULL) {
            printf("file opened: %s\n", temp);
            fclose(fp);
        }
    }
    deallocate(temp);

  for(i = 0; i < count; i++)
    deallocate(*(strings + i));
  deallocate(strings);

  for(i = 0; i < link_count; i++)
    deallocate(*(links + i));
    deallocate(links);

    deallocate(path);
  return 0;
}

#if 1
char* get_directory(char *rel_path, bool *lin) {
    /*
        Returns the directory in which the file is present
    */
    char *abs_path = NULL,
         *temp_lin = (char*)allocate((1 + strlen(rel_path)) * sizeof(char)),
         *temp_win = (char*)allocate((1 + strlen(rel_path)) * sizeof(char));

    temp_lin = strrchr(rel_path, '/');
    temp_win = strrchr(rel_path, '\\');

    if(temp_lin == NULL && temp_win == NULL) {
        *lin = true;
        abs_path = realpath((char*)".", NULL);
        return abs_path;
    }

    if(temp_lin != NULL) {
        // Linux
        *lin = true;
        *temp_lin = '\0';
        abs_path = realpath(rel_path, NULL);
    }

    if(temp_win != NULL) {
        // Windows
        *lin = false;
        *temp_win = '\0';
        abs_path = realpath(rel_path, NULL);
    }

    return abs_path;
}
#endif

void remove_tags(char *file, int *count, int *link_count, char **str, char **links) {
    /*
        Under construction function to read a file,
        read the tags in the file, analyze the tags, and return
        the text and links in the tags.
        Functionality might move around later.
    */
  FILE *fp = fopen(file, "r");

  // File opening failed.
  if(fp == NULL)
    return;

  printf("%s opened\n", file);

  char* temp = (char*)allocate(1024 * sizeof(char));
  int i = 0, j = 0;

#if 1
  while(fgets(temp, 1024, fp) != NULL) {

    strip(temp, ' ');
    strip(temp, '\n');

    if(strlen(temp) > 0) {

        // Check if putting this in get_tag_text() is better
        if(get_tag_text(temp, (str + i))) {
            i++;
        }

        if(get_tag_link(temp, (links + j))) {
            j++;
        }
    }

    memset(temp, 0, 1024 * sizeof(char));

    }
  *count = i;
  *link_count = j;
#endif

#if 0
    for(i = 0; i < *count; i++) {
        printf("%s\n", close_two);
    }
#endif
#if 0
while(fscanf(fp, "\\s+?<%[^\n]s>", str) != EOF) {
    printf("%s\n", str);
    memset(str, 0, 1024 * sizeof(char));
    count++;
    if(count > 20)
        break;
}
#endif

  fclose(fp);
  deallocate(temp);
}
