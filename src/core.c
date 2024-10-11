#include <stdio.h>
#include "core.h"

int get_max_matches(char *pattern, char *line)
{
    long pattern_length = strnlen(pattern, MAX_STRING_SIZE);
    long line_length = strnlen(line, MAX_STRING_SIZE);
    
    return line_length / pattern_length; // Can not be more matches than the ratio line_length / word_length
}

int search_pattern_in_line(char *pattern, char *line, int *matches, int max_matches)
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

int search_patterns_in_line(char **patterns, int patterns_count, char *line, int **matches)
{
    for (int i = 0; i < patterns_count; i++) {
        continue;
    }
    return 0;
}