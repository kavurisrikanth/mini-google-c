#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include "memory.h"
#include "string_ops.h"

void read_and_parse_html(char *file, int *count, int *link_count, char **str, char **links);
char* get_directory(char *rel_path);
void visit_file(char *file, char ***history, int *hits);
char** get_all_html_files_in_dir(char *path, int *files_count);
bool is_absolute_path(char *str);

#endif
