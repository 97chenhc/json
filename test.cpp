#include "json.h"
#include <cstdio>

using namespace json;

// static: var only used in this file, against extern.
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_parse_null() {
    Value v;
    v.type = FALSE;
    EXPECT_EQ_INT(PARSE_OK, v.parse("null"));
    EXPECT_EQ_INT(NUL, v.get_type());
}

static void test_parse_true() {
    Value v;
    v.type = FALSE;
    EXPECT_EQ_INT(PARSE_OK, v.parse("true"));
    EXPECT_EQ_INT(TRUE, v.get_type());
}

static void test_parse_false() {
    Value v;
    v.type = TRUE;
    EXPECT_EQ_INT(PARSE_OK, v.parse("false"));
    EXPECT_EQ_INT(FALSE, v.get_type());
}

#define TEST_ERROR(error, json)\
    do {\
        Value v;\
        v.type = FALSE;\
        EXPECT_EQ_INT(error, v.parse(json));\
        EXPECT_EQ_INT(NUL, v.get_type());\
    } while(0)

static void test_parse_expect_value() {
    TEST_ERROR(PARSE_EXPECT_VALUE, "");
    TEST_ERROR(PARSE_EXPECT_VALUE, " ");
}

static void test_parse_invalid_value() {
    TEST_ERROR(PARSE_INVALID_VALUE, "nul");
    TEST_ERROR(PARSE_INVALID_VALUE, "?");
}

static void test_parse_root_not_singular() {
    TEST_ERROR(PARSE_ROOT_NOT_SINGULAR, "null x");
}

static void test_parse() {
    test_parse_null();
    test_parse_false();
    test_parse_true();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main() {
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
