#include "testing.h"
#include "gemtext_to_html.h"

// x text line
// x text line with chars to convert to html, like & and <
// - text line with chars not to convert to html ? like &nbsp;
// x link line
// x link line with description
// x heading line
// x list item
// x add opening and closing <ul> tags around lists?
// o quote line
// o preformated toggle line

void test_an_empty_line_of_text(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "";
    char *result = convert(a, &state, line);
    assert_equals("<br/>", result);
    arena_discard(a);
}

void test_a_line_of_text(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "a line of text";
    char *result = convert(a, &state, line);
    assert_equals("a line of text<br/>", result);
    arena_discard(a);
}

void test_a_line_of_text_with_an_amp(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "this & that";
    char *result = convert(a, &state, line);
    assert_equals("this &amp; that<br/>", result);
    arena_discard(a);
}

void test_a_line_of_text_with_two_amps(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "good && bad";
    char *result = convert(a, &state, line);
    assert_equals("good &amp;&amp; bad<br/>", result);
    arena_discard(a);
}

void test_a_line_of_text_with_an_lt(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "1 < 2";
    char *result = convert(a, &state, line);
    assert_equals("1 &lt; 2<br/>", result);
    arena_discard(a);
}

void test_a_line_of_text_with_a_gt(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "1 > 2";
    char *result = convert(a, &state, line);
    assert_equals("1 &gt; 2<br/>", result);
    arena_discard(a);
}


void test_a_link_without_description_1(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://example.com";
    char *result = convert(a, &state, line);
    assert_equals("<a href=\"https://example.com\">https://example.com</a>", result);
    arena_discard(a);
}

void test_a_link_without_description_2(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://geminiprotocol.net";
    char *result = convert(a, &state, line);
    assert_equals("<a href=\"https://geminiprotocol.net\">https://geminiprotocol.net</a>", result);
    arena_discard(a);
}

void test_a_link_without_description_without_space(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=>https://example.com";
    char *result = convert(a, &state, line);
    assert_equals("<a href=\"https://example.com\">https://example.com</a>", result);
    arena_discard(a);
}

void test_a_link_with_a_description(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://example.com An example";
    char *result = convert(a, &state, line);
    assert_equals("<a href=\"https://example.com\">An example</a>", result);
    arena_discard(a);
}

void test_a_heading_line(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "# Section 1";
    char *result = convert(a, &state, line);
    assert_equals("<h1>Section 1</h1>", result);
    arena_discard(a);
}

void test_a_heading_line_without_space(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "###Section 3";
    char *result = convert(a, &state, line);
    assert_equals("<h3>Section 3</h3>", result);
    arena_discard(a);
}

void test_an_opening_list_item(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "* item 1";
    char *result = convert(a, &state, line);
    assert_equals("<ul>\n<li>item 1</li>", result);
    assert(state.is_in_list);
    arena_discard(a);
}

void test_a_list_item(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *previous_line = "* item 1";
    convert(a, &state, previous_line);

    char *line = "* item 2";
    char *result = convert(a, &state, line);
    assert_equals("<li>item 2</li>", result);

    arena_discard(a);
}

void test_a_text_line_after_a_list_item(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *list_item = "* list item";
    convert(a, &state, list_item);

    char *line = "a text line";
    char *result = convert(a, &state, line);
    assert_equals("</ul>\na text line<br/>", result);
    assert_equals(false, state.is_in_list);

    arena_discard(a);
}

int main(void) {
    TEST_BEGIN("gemtext_to_html");
    test_an_empty_line_of_text();
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
    test_an_opening_list_item();
    test_a_list_item();
    test_a_text_line_after_a_list_item();
    TEST_END;
    return 0;
}
