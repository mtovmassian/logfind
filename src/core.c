#include <stdio.h>
#include "core.h"

int search_matches_in_line(char *pattern, char *line, int *matches, int max_matches)
{
    long pattern_length = strnlen(pattern, MAX_STRING_SIZE);

    char *line_current = line;
    char *match = strstr(line_current, pattern);
    
    int match_count = 0;
    while (match != NULL &&  match_count < max_matches) {
        int match_index = match - line;
        matches[match_count] = match_index;
        match_count++;
        line_current = strstr(line_current, pattern) + pattern_length;
        match = strstr(line_current, pattern);
    }

    return match_count;
}