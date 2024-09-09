#include "testing.h"
#include "gemtext_to_html.h"

// x text line
// x text line with chars to convert to html, like & and <
// - text line with chars not to convert to html ? like &nbsp;
// x link line
// x link line with description
// x heading line
// x list item
// x add opening and closing <ul> tags around lists
// x quote line
// x preformated toggle line
// x render links as list items
// x use <p> tags for text blocks.
// x if a link is local to an image, generate an img tag

///////////////////////////////////////////////////////////////////////////////
// Text

void test_an_empty_line_of_text(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "";
    char *result = convert(a, &state, line);
    assert_equals("", result);
    arena_discard(a);
}

void test_a_line_of_text(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "a line of text";
    char *result = convert(a, &state, line);
    assert_equals("<p>\na line of text", result);
    arena_discard(a);
}

void test_a_line_of_text_with_an_amp(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "this & that";
    char *result = convert(a, &state, line);
    assert_equals("<p>\nthis &amp; that", result);
    arena_discard(a);
}

void test_a_line_of_text_with_two_amps(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "good && bad";
    char *result = convert(a, &state, line);
    assert_equals("<p>\ngood &amp;&amp; bad", result);
    arena_discard(a);
}

void test_a_line_of_text_with_an_lt(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "1 < 2";
    char *result = convert(a, &state, line);
    assert_equals("<p>\n1 &lt; 2", result);
    arena_discard(a);
}

void test_a_line_of_text_with_a_gt(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "1 > 2";
    char *result = convert(a, &state, line);
    assert_equals("<p>\n1 &gt; 2", result);
    arena_discard(a);
}

void test_a_paragraph_of_text_after_a_heading(void) {
    char *input[4] = {
        "# Title",
        "",
        "some text",
        "",
    };

    char *expected[4] = {
        "<h1>Title</h1>",
        "",
        "<p>\nsome text",
        "</p>\n",
    };
    struct arena *a = arena_init(256);
    struct convert_state state = {0};

    assert_equals(expected[0], convert(a, &state, input[0]));
    assert_equals(expected[1], convert(a, &state, input[1]));
    assert_equals(expected[2], convert(a, &state, input[2]));
    assert_equals(expected[3], convert(a, &state, input[3]));

    arena_discard(a);
}

void test_a_paragraph_of_two_lines_of_text_after_a_heading(void) {
    char *input[5] = {
        "# Title",
        "",
        "first line",
        "second line",
        "",
    };

    char *expected[5] = {
        "<h1>Title</h1>",
        "",
        "<p>\nfirst line",
        "<br/>\nsecond line",
        "</p>\n",
    };
    struct arena *a = arena_init(256);
    struct convert_state state = {0};

    assert_equals(expected[0], convert(a, &state, input[0]));
    assert_equals(expected[1], convert(a, &state, input[1]));
    assert_equals(expected[2], convert(a, &state, input[2]));
    assert_equals(expected[3], convert(a, &state, input[3]));
    assert_equals(expected[4], convert(a, &state, input[4]));

    arena_discard(a);
}

void test_a_blockquote_after_a_paragraph_of_text(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};

    assert_equals("<p>\nfirst line", convert(a, &state, "first line"));
    assert_equals("<p/>\n<blockquote>quote", convert(a, &state, "> a quote"));

    arena_discard(a);
}

///////////////////////////////////////////////////////////////////////////////
// Link

void test_a_link_without_description_1(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://example.com";
    char *result = convert(a, &state, line);
    assert_equals("<ul>\n<li><a href=\"https://example.com\">https://example.com</a></li>", result);
    arena_discard(a);
}

void test_a_link_without_description_2(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://geminiprotocol.net";
    char *result = convert(a, &state, line);
    assert_equals("<ul>\n<li><a href=\"https://geminiprotocol.net\">https://geminiprotocol.net</a></li>", result);
    arena_discard(a);
}

void test_a_link_without_description_without_space(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=>https://example.com";
    char *result = convert(a, &state, line);
    assert_equals("<ul>\n<li><a href=\"https://example.com\">https://example.com</a></li>", result);
    arena_discard(a);
}

void test_a_link_with_a_description(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://example.com An example";
    char *result = convert(a, &state, line);
    assert_equals("<ul>\n<li><a href=\"https://example.com\">An example</a></li>", result);
    arena_discard(a);
}

void test_a_second_link(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "=> https://example.com";
    convert(a, &state, line);

    char *result = convert(a, &state, line);
    assert_equals("<li><a href=\"https://example.com\">https://example.com</a></li>", result);
    arena_discard(a);
}

void test_a_text_line_after_a_link(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *link_line = "=> https://example.com";
    convert(a, &state, link_line);

    char *line = "a text line";
    char *result = convert(a, &state, line);
    assert_equals("</ul>\n<p>\na text line", result);
    arena_discard(a);
}

void test_a_link_to_a_local_image(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *link_line = "=> /images/example.png";

    char *result = convert(a, &state, link_line);

    assert_equals("<img src=\"/images/example.png\" />", result);
    arena_discard(a);
}

///////////////////////////////////////////////////////////////////////////////
// Heading

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

///////////////////////////////////////////////////////////////////////////////
// List

void test_an_opening_list_item(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "* item 1";
    char *result = convert(a, &state, line);
    assert_equals("<ul>\n<li>item 1</li>", result);
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
    assert_equals("</ul>\n<p>\na text line", result);

    arena_discard(a);
}

///////////////////////////////////////////////////////////////////////////////
// Quote

void test_an_opening_quote(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "> quote";
    char *result = convert(a, &state, line);
    assert_equals("<blockquote>\nquote", result);
    arena_discard(a);
}

void test_a_quote(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *previous_line = "> quote 1";
    convert(a, &state, previous_line);

    char *line = "> quote 2";
    char *result = convert(a, &state, line);
    assert_equals("<br/>\nquote 2", result);

    arena_discard(a);
}

void test_quotes_without_space(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};

    char *previous_line = ">quote 1";
    char *result = convert(a, &state, previous_line);
    assert_equals("<blockquote>\nquote 1", result);

    char *line = ">quote 2";
    result = convert(a, &state, line);
    assert_equals("<br/>\nquote 2", result);

    arena_discard(a);
}

void test_a_closing_quote(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *previous_line = "> quote";
    convert(a, &state, previous_line);

    char *line = "a non quote line";
    char *result = convert(a, &state, line);
    assert_equals("</blockquote>\n<p>\na non quote line", result);

    arena_discard(a);
}

///////////////////////////////////////////////////////////////////////////////
// Preformated

void test_entering_preformated_mode(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *line = "```";
    char *result = convert(a, &state, line);
    assert_equals("<pre>", result);
    arena_discard(a);
}

void test_adding_preformated_text(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *previous_line = "```";
    convert(a, &state, previous_line);

    char *line = "int f(int a, int b) {";
    char *result = convert(a, &state, line);
    assert_equals("int f(int a, int b) {", result);

    line = "    return 1 && 2;";
    result = convert(a, &state, line);
    assert_equals("    return 1 && 2;", result);

    arena_discard(a);
}

void test_leaving_preformated_mode(void) {
    struct arena *a = arena_init(256);
    struct convert_state state = {0};
    char *previous_line = "```";
    convert(a, &state, previous_line);
    char *line = "```";
    char *result = convert(a, &state, line);
    assert_equals("</pre>", result);
    arena_discard(a);
}

#define MODULE "gemtext_to_html"

int main(void) {
    TEST_BEGIN(MODULE":text");
    test_an_empty_line_of_text();
    test_a_line_of_text();
    test_a_line_of_text_with_an_amp();
    test_a_line_of_text_with_two_amps();
    test_a_line_of_text_with_an_lt();
    test_a_line_of_text_with_a_gt();
    TEST_END;

    TEST_BEGIN(MODULE":link");
    test_a_link_without_description_1();
    test_a_link_without_description_2();
    test_a_link_without_description_without_space();
    test_a_link_with_a_description();
    test_a_second_link();
    test_a_text_line_after_a_link();
    test_a_paragraph_of_text_after_a_heading();
    test_a_paragraph_of_two_lines_of_text_after_a_heading();
    test_a_link_to_a_local_image();
    TEST_END;

    TEST_BEGIN(MODULE":heading");
    test_a_heading_line();
    test_a_heading_line_without_space();
    TEST_END;

    TEST_BEGIN(MODULE":list");
    test_an_opening_list_item();
    test_a_list_item();
    test_a_text_line_after_a_list_item();
    TEST_END;

    TEST_BEGIN(MODULE":quote");
    test_an_opening_quote();
    test_a_quote();
    test_quotes_without_space();
    test_a_closing_quote();
    TEST_END;

    TEST_BEGIN(MODULE":preformated");
    test_entering_preformated_mode();
    test_adding_preformated_text();
    test_leaving_preformated_mode();
    TEST_END;

    return 0;
}
