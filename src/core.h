#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 8192

int search_matches_in_line(char *pattern, char *line, int *matches, int max_matches);

#endif