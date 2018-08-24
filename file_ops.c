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

/**
 * Visits a file.
 */
void visit_file(char *file, char ***history, int *hits) {
    /* code */

    int count = 0, i = 0, link_count = 0;
    char **strings = NULL, **links = NULL;

    // Check if we are in Linux or Windows.
    // bool lin = false;

    // Since we are dealing with pointers, we'll play safe and have temporary pointers.
    char *temp = (char*)allocate(1024 * sizeof(char));

    // Copy file to temp.
    strcpy(temp, file);

    // Get the path to the file.
    char *path = get_directory(temp);
    printf("path: %s\n", path);

    // Make sure temp has the absolute path to file.
    if(!is_absolute_path(file)) {
        strcat(temp, path);
        strcat(temp, "/");
    }
    strcat(temp, file);
    printf("temp outside: %s\n", temp);

    // If we've already visited this file, go back.
    if(visited(*history, *hits, temp)) {
        deallocate(temp);
        deallocate(path);
        return;
    }

    // Get stuff ready.
    strings = (char**)allocate(1024 * sizeof(char*)),
    links = (char**)allocate(1024 * sizeof(char*));

    // Parse file and insert into history. We need to insert right now, since the next operation is
    // visiting files mentioned in this file. If we don't insert here, then we risk an infinite loop.
    read_and_parse_html((char*)temp, &count, &link_count, strings, links);
    insert(*history, temp, *hits);
    printf("Inserted into history: %s\n", temp);
    *hits += 1;

// Debug printout.
#if 0
    printf("\n\nFinally...\n");
    for(i = 0; i < count; i++)
        printf("%s\n", *(strings + i));
#endif

    /*
     * Actual major part here. Parse the strings to check for the required phrase.
     */

    FILE *fp = NULL;

    // And now the second major part. Visit all files that are mentioned in this file.
    for(i = 0; i < link_count; i++) {
        memset(temp, 0, 1024 * sizeof(char));
        strcat(temp, *(links + i));
        if((fp = fopen(temp, "r")) != NULL) {
            printf("temp inside: %s\n", temp);
            visit_file(temp, history, hits);
            fclose(fp);
        }
    }

    // Free up used memory.
    deallocate(temp);

    for(i = 0; i < count; i++)
        deallocate(*(strings + i));
    deallocate(strings);

    for(i = 0; i < link_count; i++)
        deallocate(*(links + i));
    deallocate(links);

    deallocate(path);
}

#if 1
char* get_directory(char *rel_path) {
    /*
        Returns the directory in which the file is present
    */
    char *abs_path = NULL,
         *temp_lin = NULL,
         *temp_win = NULL;

    temp_lin = strrchr(rel_path, '/');
    temp_win = strrchr(rel_path, '\\');

    if(temp_lin == NULL && temp_win == NULL) {
        abs_path = realpath((char*)".", NULL);
        return abs_path;
    }

    if(temp_lin != NULL) {
        // Linux
        *temp_lin = '\0';
        abs_path = realpath(rel_path, NULL);
    }

    if(temp_win != NULL) {
        // Windows
        *temp_win = '\0';
        abs_path = realpath(rel_path, NULL);
    }

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
