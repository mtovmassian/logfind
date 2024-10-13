#define  _POSIX_C_SOURCE 200809L // See https://man7.org/linux/man-pages/man3/getline.3.html
#include "core.h"
#include <stdio.h>
#include <string.h>

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

int search_patterns_in_file_any(char *patterns[], int patterns_count, char *file_path)
{
    FILE *file;
    char *line = NULL;
    int line_number = 0;
    int line_has_match = 0;
    size_t len = 0;
    size_t read;
    size_t read_error = -1;

    file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while ((read = getline(&line, &len, file)) != read_error) {
        line_number++;
        line_has_match = 0;
        for (int i = 0; i < patterns_count; i++) {
            if (line_has_match > 0) break; // Stop matching process early since in 'any' mode one pattern match is enough
            char *pattern = patterns[i];
            char *match = strstr(line, pattern);
            if (match != NULL) { // Line has at least one match
                // Print match infos and stop match process
                printf("%s:%d:%s", file_path, line_number, line);
                line_has_match = 1;
            }
        }
    }

    return 0;
}