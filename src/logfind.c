#include <stdio.h>
#include "core.h"

void usage(FILE *stream, char *executable_name)
{
    fprintf(stream, ""
        "Usage: %s [OPTION]... PATTERNS\n"
        "\n"
        "Options:\n"
        "   -h, --help  Help\n"
        "   -a, --all   Search all patterns (default)\n"
        "   -o, --any   Search any patterns\n"
        "\n"
        "Example: search pattern1 AND pattern2\n"
        "   %s Romeo Juliet\n"
        "Example: search pattern1 OR pattern2\n"
        "   %s -o Romeo Juliet\n"
        ,
    executable_name, executable_name, executable_name);
}

int main(int argc, char **argv)
{
    char *pattern_search_mode = "all";

    if (argc < 2) {
        usage(stderr, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *patterns[argc - 1];
    int patterns_count = 0;
    for (int i = 0; i < argc; i++) {
        
        if (i == 0) continue; // Skip executable name

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage(stdout, argv[0]);
            exit(EXIT_SUCCESS);
        }
        
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
            pattern_search_mode = "all";
            continue;
        }
        
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--any") == 0) {
            pattern_search_mode = "any";
            continue;
        }
        
        patterns[patterns_count] = argv[i];
        patterns_count++;
    }

    if (strcmp(pattern_search_mode, "any") == 0) {
        search_patterns_in_file_any(patterns,  patterns_count, "./static/romeo-and-juliet/act1-scene1.txt");
    } else {
        search_patterns_in_file_all(patterns,  patterns_count, "./static/romeo-and-juliet/act1-scene1.txt");
    }

    return 0;
}
