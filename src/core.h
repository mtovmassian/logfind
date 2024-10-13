#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 8192

int get_max_matches(char *pattern, char *line);

int search_pattern_in_line(char *pattern, char *line, int *matches, int max_matches);

int search_patterns_in_file_any(char *patterns[], int patterns_count, char *file_path);

#endif