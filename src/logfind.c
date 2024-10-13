#include <stdio.h>
#include "core.h"


int main(int argc, char **argv)
{

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [PATTERN]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // char *line = argv[1];
    // long line_length = strnlen(line, MAX_STRING_SIZE);
    // char *pattern = argv[2];
    // long pattern_length = strnlen(pattern, MAX_STRING_SIZE);

    
    // int max_matches = get_max_matches(pattern, line);
    // int matches[max_matches];
    // int match_count  = search_pattern_in_line(pattern, line, matches, max_matches);

    // int i;
    // for (i=0; i < match_count; i++) {
    //     printf("Match at index %d\n", matches[i]);
    // }

    // char visual[line_length];
    // visual[line_length] = '\0';
    // for (i=0; i < line_length; i++) {
    //     visual[i] = ' ';
    // }
    // for (i=0; i < match_count; i++) {
    //     int match_index = matches[i];
    //     int j;
    //     for(j=match_index; j < (match_index + pattern_length); j++) {
    //         visual[j] = '^';
    //     }
    // }

    // printf("%s\n", line);
    // printf("%s\n", visual);


    
    char *patterns[argc];
    for (int i = 1; i < argc; i++) {
        patterns[i - 1] = argv[i];
    }
    
    search_patterns_in_file_any(patterns,  argc - 1, "./static/lorem-ipsum.txt");

    return 0;
}
