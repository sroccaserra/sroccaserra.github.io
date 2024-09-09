#include "testing.h"
#include "text.h"

void test_starts_with(void) {
    assert(starts_with("hello, world", "hello"));
}

void test_is_empty(void) {
    assert(is_empty(""));
    assert(is_empty("  "));
    assert(is_empty("  \t"));
    assert(!is_empty(" o "));
}


int main(void) {
    TEST_BEGIN("text");
    test_starts_with();
    test_is_empty();
    TEST_END;
    return 0;
}
