#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "memory.h"

#ifndef STRING_OPS_H
#define STRING_OPS_H

bool get_tag_text(char* str, char **buffer);
bool get_tag_link(char* str, char **buffer);
void lstrip(char *str, char delim);
void rstrip(char *str, char delim);
void strip(char *str, char delim);

#endif