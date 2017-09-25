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

  strings = (char**)allocate(1024 * sizeof(char*)),
  links = (char**)allocate(1024 * sizeof(char*));

  remove_tags((char*)argv[1], &count, &link_count, strings, links);

#if 1
  printf("\n\nFinally...\n");
  for(i = 0; i < count; i++)
    printf("%sblabla\n", *(strings + i));
#endif

  for(i = 0; i < count; i++)
    deallocate(*(strings + i));
  deallocate(strings);

  for(i = 0; i < link_count; i++)
    deallocate(*(links + i));
    deallocate(links);

  return 0;
}

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

    // int count = 0;

  printf("%s opened\n", file);

  // Allocate memory for the arrays
  // str = (char**)allocate(1024 * sizeof(char*)),
  // links = (char**)allocate(1024 * sizeof(char*));

  char* temp = (char*)allocate(1024 * sizeof(char));
  int i = 0, j = 0;

#if 1
  while(fgets(temp, 1024, fp) != NULL) {
    //   if(*(temp + strlen(temp) - 1) == '\n')
    //     *(temp + strlen(temp) - 1) = '\0';

    // printf("stripping: %s\n", temp);
    strip(temp, ' ');
    strip(temp, '\n');
    // printf("stripped: %s\n", temp);

    // printf("temp: %s\n", temp);
    if(strlen(temp) > 0) {

        // Check if putting this in get_tag_text() is better
        // if(*(str + i) != NULL)
        //     *(str + i) = (char*)allocate((1 + strlen(temp)) * sizeof(char));

        // if(*(links + i) != NULL)
        //     *(links + i) = (char*)allocate((1 + strlen(temp)) * sizeof(char));

        if(get_tag_text(temp, (str + i))) {
            printf("just added: %s\n", *(str + i));
            i++;
        }

        if(get_tag_link(temp, (links + j))) {
            j++;
        }
    }

    memset(temp, 0, 1024 * sizeof(char));

    // break;
    }
  *count = i;
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
  // return str;
}