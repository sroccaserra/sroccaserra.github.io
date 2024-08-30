#include "testing.h"
#include "gemtext_to_html.h"

// x text line
// o text line with chars to convert to html, like & and <
// - text line with chars not to convert to html ? like &nbsp;
// o heading line
// x link line
// o link line with description
// o list item
// o quote line
// o preformated toggle line
//
////
// function to escape html chars (see above)
//
// dans une text line on va encoder certains & et certains < :
// "toto & tata" > "toto &amp; tata"
// "toto &amp; tata" > "toto &amp; tata"
// mais si on veut supporter l'html déjà dans l'input on doit :
// "toto&nbsp;: tata" > "toto&nbsp;: tata"
// Dans markdown c'est fait par une regex de l'enfer
// Decision : I don't support html in the input
//
// Dans une preformated line :
// "toto & tata" > "toto &amp; tata"
// "toto&nbsp;: tata" > "toto&amp;nbsp;: tata"
//
////

void test_a_line_of_text() {
    char *line = "a line of text";
    char *result = convert(line);
    assert_equals("a line of text", result);
}

void test_a_link_without_description_1() {
    char *line = "=> https://example.com";
    char *result = convert(line);
    assert_equals("<a href=\"https://example.com\">https://example.com</a>", result);
}

void test_a_link_without_description_2() {
    char *line = "=> https://geminiprotocol.net";
    char *result = convert(line);
    assert_equals("<a href=\"https://geminiprotocol.net\">https://geminiprotocol.net</a>", result);
}

void test_a_link_without_description_without_space() {
    char *line = "=>https://example.com";
    char *result = convert(line);
    assert_equals("<a href=\"https://example.com\">https://example.com</a>", result);
}

void test_a_link_with_a_description() {
    char *line = "=> https://example.com An example";
    char *result = convert(line);
    assert_equals("<a href=\"https://example.com\">An example</a>", result);
}

int main() {
    TEST_BEGIN("gemtext_to_html");
    test_a_line_of_text();
    test_a_link_without_description_1();
    test_a_link_without_description_2();
    test_a_link_without_description_without_space();
    // test_a_link_with_a_description();
    TEST_END;
    return 0;
}
