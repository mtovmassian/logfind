#include "../unity/src/unity.h"
#include "../src/calc.h"

void test_add()
{
    int output = add(10, 20);
    TEST_ASSERT_EQUAL(30, output);
}

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_add);
    
    UNITY_END();
    
    return 0;   
}