#include "file_ops.h"

char** get_all_html_files_in_dir(char *path, int *files_count) {
	/*
		Returns a list of all HTML files in a directory.
	*/

	DIR *dir;
	struct dirent *d;
	char *extn,
        **files = NULL;
	int i = 0;

	// To keep track of the number, since we're returning an array.
	*files_count = 0;

	dir = opendir(path);
	if(dir) {
		files = (char**)allocate(10 * sizeof(char*));
		while((d = readdir(dir)) != NULL) {
			// printf("%s\n", d->d_name);
			extn = strchr(d->d_name, '.');
			if(extn) {
				// printf("extn: %s\n", extn);
				if(strcmp(extn, ".html") == 0) {
					// printf("%s is a text file!\n", d->d_name);
					// *(files + i) = (char*)allocate((1 + d->d_name) * sizeof(char));
					*(files + i) = strdup(d->d_name);
					i++;
					(*files_count)++;
				}
			}
		}
		closedir(dir);
	} else {
		fprintf(stderr, "Invalid directory: %s\n", path);
	}

	return files;
}

void blabla(char *file, char ***history, int *hits) {
  /* code */

  if(visited(*history, *hits, file))
    return;

  int count = 0, i = 0, link_count = 0;
  char **strings = NULL, **links = NULL;

  bool lin = false;
  char *temp = (char*)allocate(1024 * sizeof(char));
  strcpy(temp, file);
  char *path = get_directory(temp, &lin);
  printf("path: %s\n", path);

  strings = (char**)allocate(1024 * sizeof(char*)),
  links = (char**)allocate(1024 * sizeof(char*));

  memset(temp, 0, 1024 * sizeof(char));
  if(!is_absolute_path(file)) {
      strcat(temp, path);
      strcat(temp, "/");
  }
  strcat(temp, file);
  read_and_parse_html((char*)temp, &count, &link_count, strings, links);
  insert(*history, temp, *hits);
  *hits += 1;

#if 1
  printf("\n\nFinally...\n");
  for(i = 0; i < count; i++)
    printf("%s\n", *(strings + i));
#endif

    FILE *fp = NULL;

    for(i = 0; i < link_count; i++) {
        memset(temp, 0, 1024 * sizeof(char));
        // strcat(temp, path);
        // strcat(temp, "/");
        strcat(temp, *(links + i));
        printf("%s\n", temp);
        if((fp = fopen(temp, "r")) != NULL) {
            printf("file opened: %s\n", temp);
            blabla(temp, history, hits);
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
  // return 0;
}

#if 1
char* get_directory(char *rel_path, bool *lin) {
    /*
        Returns the directory in which the file is present
    */
    char *abs_path = NULL,
         *temp_lin = NULL,
         *temp_win = NULL;

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

    // deallocate(temp_lin);
    // deallocate(temp_win);
    return abs_path;
}
#endif

void read_and_parse_html(char *file, int *count, int *link_count, char **str, char **links) {
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

  printf("\n\n%s opened\n", file);

  char* temp = (char*)allocate(2048 * sizeof(char));
  int i = 0, j = 0;

  while(fgets(temp, 2048, fp) != NULL) {

    // strip(temp, ' ');
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

  fclose(fp);
  deallocate(temp);
}

bool is_absolute_path(char *str) {
    /*
        Checks if a given string is an absolute path
    */

    if(str == NULL || strlen(str) == 0)
        return false;

    char *test_lin, *test_win;

    test_lin = strchr(str, '/');
    test_win = strchr(str, '\\');

    if(test_win == NULL && test_lin == NULL)
        return false;

    return true;
}
