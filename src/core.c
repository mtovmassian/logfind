#define  _POSIX_C_SOURCE 200809L // See https://man7.org/linux/man-pages/man3/getline.3.html
#include "core.h"
#include <stdio.h>
#include <string.h>

int all(int values[], int values_count)
{
    for (int i = 0; i < values_count; i++) {
        if (values[i] == 0) return 0;
    }
    return 1;
}

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

/* 
    Search all the file lines where at least one of the patterns match.
    Print the lines to stdout as soon as there is a match.
*/
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
        fprintf(stderr, "Something went wrong while opening file %s\n", file_path);
        return EXIT_FAILURE;
    }

    while ((read = getline(&line, &len, file)) != read_error) {
        line_number++;
        line_has_match = 0;
        for (int i = 0; i < patterns_count; i++) {
            if (line_has_match > 0) break; // Stop matching process early since we are in 'any' mode and one pattern match is enough
            char *pattern = patterns[i];
            char *match = strstr(line, pattern);
            if (match != NULL) { // Line has at least one match
                // Print match infos and stop matching process
                printf("%s:%d:%s", file_path, line_number, line);
                line_has_match = 1;
            }
        }
    }

    return 0;
}

int search_patterns_in_file_all(char *patterns[], int patterns_count, char *file_path)
{
    FILE *file;
    char *line = NULL;
    int file_has_match = 0;
    size_t len = 0;
    size_t read;
    size_t read_error = -1;

    file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Something went wrong while opening file %s\n", file_path);
        return EXIT_FAILURE;
    }

    int pattern_match_states[patterns_count]; // Track each pattern match state ('0' no match / '1' at least one match)
    memset(pattern_match_states, 0, patterns_count * sizeof(int)); //  All pattern match states set to 0

    while ((read = getline(&line, &len, file)) != read_error) {
        for (int i = 0; i < patterns_count; i++) {

            if (pattern_match_states[i] == 1) continue; // Pattern already matched no need to process it again

            char *pattern = patterns[i];
            char *match = strstr(line, pattern);
            if (match != NULL) { // Pattern has matched
                pattern_match_states[i] = 1; // Keep track that pattern matched
                if (all(pattern_match_states, patterns_count)) { // Stop processing the line and notify that all patterns matched at least once
                    file_has_match = 1;
                    break;
                }
            }
        }

        if (file_has_match == 1) break; // Stop processing the file all patterns matched at least once
    }

    if (file_has_match) { // All patterns matched at least once now we can search them exhaustively in 'any' mode 
        search_patterns_in_file_any(patterns, patterns_count, file_path);
    }

    return 0;
}