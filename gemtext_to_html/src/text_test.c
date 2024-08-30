#include "testing.h"
#include "text.h"

void test_starts_with(){
    assert(starts_with("hello, world", "hello"));
}

void test_skip_spaces() {
    char *text = "  hello";
    skip_spaces(&text);

    assert_equals("hello", text);
}

void test_skip_non_spaces() {
    char *text = "hello, world";
    skip_non_spaces(&text);

    assert_equals(" world", text);
}

int main() {
    TEST_BEGIN("text");
    test_starts_with();
    test_skip_spaces();
    test_skip_non_spaces();
    TEST_END;
    return 0;
}
