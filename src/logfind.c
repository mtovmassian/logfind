#include <stdio.h>
#include "core.h"

void usage(FILE *stream, char *script_name)
{
    fprintf(stream, ""
        "Usage: %s [OPTIONS] [PATTERN]\n\n"
        "Options:\n"
        "       -h, --help  Help\n"
        "       -a          Search all patterns (i.e. PATERN1 AND PATTERN2) (default)\n"
        "       -o          Search any patterns (i.e. PATTERN1 OR PATTERN2)\n",
    script_name);
}

int main(int argc, char **argv)
{
    char *pattern_search_mode = "all";

    if (argc < 2) {
        usage(stderr, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *patterns[argc];
    for (int i = 1; i < argc; i++) {
        // if (strcmp(argv[i], "-h") == 0) {
        //     usage(stdout, argv[0]);
        //     exit(EXIT_SUCCESS);
        // }
        // if (strcmp(argv[i], "-a")) continue;
        // if (strcmp(argv[i], "-o")) pattern_search_mode = "any";
        patterns[i - 1] = argv[i];
    }

    if (strcmp(pattern_search_mode, "any") == 0) {
        search_patterns_in_file_any(patterns,  argc - 1, "./static/romeo-and-juliet/act1-scene1.txt");
    } else {
        search_patterns_in_file_all(patterns,  argc - 1, "./static/romeo-and-juliet/act1-scene1.txt");
    }

    return 0;
}
