#ifndef TESTING_H
#define TESTING_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TEST_BEGIN(s) (fprintf(stderr, s"..."), fflush(stderr))
#define TEST_END (fprintf(stderr, " ✅\n"))

#define gen_format(e) _Generic((e), \
        uint64_t: "%lu", \
        int64_t: "%ld", \
        int: "%d", \
        void *: "%p", \
        char *: "%s")

#define gen_print_failure(e, a) ( \
        fprintf(stderr, "ASSERTION FAILED!\n👉 "), \
        fprintf(stderr, gen_format(e), e), \
        fprintf(stderr, "\n❌ "), \
        fprintf(stderr, gen_format(a), a), \
        fprintf(stderr, "\n"))

#define check_equals(e, a) ((e) == (a) ? 1 : ((gen_print_failure(e, a)), 0))

int check_equals_uint64_t(uint64_t expected, uint64_t actual) {
    return check_equals(expected, actual);
}

int check_equals_int64_t(int64_t expected, int64_t actual) {
    return check_equals(expected, actual);
}

int check_equals_int(int expected, int actual) {
    return check_equals(expected, actual);
}

int check_equals_ptr(void *expected, void *actual) {
    return check_equals(expected, actual);
}

int check_equals_str(char *expected, char *actual) {
    if (0 != strcmp(expected, actual)) {
        gen_print_failure(expected, actual);
        return 0;
    }
    return 1;
}

#define gen_check_equals(e, a) _Generic((e), \
        uint64_t: check_equals_uint64_t, \
        int64_t: check_equals_int64_t, \
        int: check_equals_int, \
        void *: check_equals_ptr, \
        char *: check_equals_str) \
    (e, a)


#define assert_equals(e, a) (assert(gen_check_equals(e, a)))

#define assert_null(p) (assert(gen_check_equals(NULL, p)))

#endif
