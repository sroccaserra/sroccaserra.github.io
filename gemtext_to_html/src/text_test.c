#include "testing.h"
#include "text.h"

void test_starts_with(void) {
    assert(starts_with("hello, world", "hello"));
}

int main(void) {
    TEST_BEGIN("text");
    test_starts_with();
    TEST_END;
    return 0;
}
