#include "testing.h"
#include "text.h"

void test_starts_with(){
    assert(starts_with("hello, world", "hello"));
}

int main() {
    TEST_BEGIN("text");
    test_starts_with();
    TEST_END;
    return 0;
}
