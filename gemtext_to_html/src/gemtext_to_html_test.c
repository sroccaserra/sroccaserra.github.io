#include "testing.h"
#include "gemtext_to_html.h"

// x text line
// x text line with chars to convert to html, like & and <
// - text line with chars not to convert to html ? like &nbsp;
// x link line
// x link line with description
// x heading line
// x list item
// o add opening and closing <ul> tags around lists?
// o quote line
// o preformated toggle line

void test_a_line_of_text() {
    struct arena *a = arena_init(256);
    char *line = "a line of text";
    char *result = convert(a, line);
    assert_equals("a line of text", result);
    arena_discard(a);
}

void test_a_line_of_text_with_an_amp() {
    struct arena *a = arena_init(256);
    char *line = "this & that";
    char *result = convert(a, line);
    assert_equals("this &amp; that", result);
    arena_discard(a);
}

void test_a_line_of_text_with_two_amps() {
    struct arena *a = arena_init(256);
    char *line = "good && bad";
    char *result = convert(a, line);
    assert_equals("good &amp;&amp; bad", result);
    arena_discard(a);
}

void test_a_line_of_text_with_an_lt() {
    struct arena *a = arena_init(256);
    char *line = "1 < 2";
    char *result = convert(a, line);
    assert_equals("1 &lt; 2", result);
    arena_discard(a);
}

void test_a_line_of_text_with_a_gt() {
    struct arena *a = arena_init(256);
    char *line = "1 > 2";
    char *result = convert(a, line);
    assert_equals("1 &gt; 2", result);
    arena_discard(a);
}


void test_a_link_without_description_1() {
    struct arena *a = arena_init(256);
    char *line = "=> https://example.com";
    char *result = convert(a, line);
    assert_equals("<a href=\"https://example.com\">https://example.com</a>", result);
    arena_discard(a);
}

void test_a_link_without_description_2() {
    struct arena *a = arena_init(256);
    char *line = "=> https://geminiprotocol.net";
    char *result = convert(a, line);
    assert_equals("<a href=\"https://geminiprotocol.net\">https://geminiprotocol.net</a>", result);
    arena_discard(a);
}

void test_a_link_without_description_without_space() {
    struct arena *a = arena_init(256);
    char *line = "=>https://example.com";
    char *result = convert(a, line);
    assert_equals("<a href=\"https://example.com\">https://example.com</a>", result);
    arena_discard(a);
}

void test_a_link_with_a_description() {
    struct arena *a = arena_init(256);
    char *line = "=> https://example.com An example";
    char *result = convert(a, line);
    assert_equals("<a href=\"https://example.com\">An example</a>", result);
    arena_discard(a);
}

void test_a_heading_line() {
    struct arena *a = arena_init(256);
    char *line = "# Section 1";
    char *result = convert(a, line);
    assert_equals("<h1>Section 1</h1>", result);
    arena_discard(a);
}

void test_a_heading_line_without_space() {
    struct arena *a = arena_init(256);
    char *line = "###Section 3";
    char *result = convert(a, line);
    assert_equals("<h3>Section 3</h3>", result);
    arena_discard(a);
}

void test_a_list_item() {
    struct arena *a = arena_init(256);
    char *line = "* item 1";
    char *result = convert(a, line);
    assert_equals("<li>item 1</li>", result);
    arena_discard(a);
}

int main() {
    TEST_BEGIN("gemtext_to_html");
    test_a_line_of_text();
    test_a_line_of_text_with_an_amp();
    test_a_line_of_text_with_two_amps();
    test_a_line_of_text_with_an_lt();
    test_a_line_of_text_with_a_gt();
    test_a_link_without_description_1();
    test_a_link_without_description_2();
    test_a_link_without_description_without_space();
    test_a_link_with_a_description();
    test_a_heading_line();
    test_a_heading_line_without_space();
    test_a_list_item();
    TEST_END;
    return 0;
}
