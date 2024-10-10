#include "../unity/src/unity.h"
#include "../src/core.h"


void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_search_matches_in_line()
{
    char *line = "alpha bravo charly character braveheart alphabet";
    char *pattern = "alp";
    long line_length = strnlen(line, MAX_STRING_SIZE);
    long pattern_length = strnlen(pattern, MAX_STRING_SIZE);
    int max_matches = line_length / pattern_length;
    int matches[max_matches];
    int match_count  = search_matches_in_line(pattern, line, matches, max_matches);
    TEST_ASSERT_EQUAL(2, match_count);
    TEST_ASSERT_EQUAL(0, matches[0]);
    TEST_ASSERT_EQUAL(40, matches[1]);
}

int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_search_matches_in_line);
    
    UNITY_END();
    
    return 0;   
}