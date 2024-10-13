#include "../unity/src/unity.h"
#include "../src/core.h"
#include <string.h>


void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_search_pattern_in_line()
{
    char *line;
    char *pattern;
    long line_length;
    long pattern_length;
    int max_matches;

    line = "The painter is painting with no main pain.";
    line_length = strnlen(line, MAX_STRING_SIZE);
    
    pattern = "ain";
    pattern_length = strnlen(pattern, MAX_STRING_SIZE);
    max_matches = get_max_matches(pattern, line);
    int matches1[max_matches];
    memset(matches1, 0, max_matches);
    int match_count1  = search_pattern_in_line(pattern, line, matches1, max_matches);
    TEST_ASSERT_EQUAL(4, match_count1); // Found 4 matches
    TEST_ASSERT_EQUAL(5, matches1[0]); // First match starts at index 5
    TEST_ASSERT_EQUAL(16, matches1[1]); // Second match starts at index 16
    TEST_ASSERT_EQUAL(33, matches1[2]); // Third match starts at index 33
    TEST_ASSERT_EQUAL(38, matches1[3]); // Fourth match starts at index 38

    pattern = "pain";
    pattern_length = strnlen(pattern, MAX_STRING_SIZE);
    max_matches = get_max_matches(pattern, line);
    int matches2[max_matches];
    int match_count2  = search_pattern_in_line(pattern, line, matches2, max_matches);
    TEST_ASSERT_EQUAL(3, match_count2); // Found 3 matches
    TEST_ASSERT_EQUAL(4, matches2[0]); // First match starts at index 4
    TEST_ASSERT_EQUAL(15, matches2[1]); // Second match starts at index 15
    TEST_ASSERT_EQUAL(37, matches2[2]); // Third match starts at index 37

    pattern = "paint";
    pattern_length = strnlen(pattern, MAX_STRING_SIZE);
    max_matches = get_max_matches(pattern, line);
    int matches3[max_matches];
    int match_count3  = search_pattern_in_line(pattern, line, matches3, max_matches);
    TEST_ASSERT_EQUAL(2, match_count3); // Found 2 matches
    TEST_ASSERT_EQUAL(4, matches3[0]); // First match starts at index 4
    TEST_ASSERT_EQUAL(15, matches3[1]); // Second match starts at index 15
}

int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_search_pattern_in_line);
    
    UNITY_END();
    
    return 0;   
}