#define UNARGS_PRINT_OUT_INT(x)
#define UNARGS_PRINT_OUT_UNSIGNED(x)
#define UNARGS_PRINT_OUT_FLOAT(x)
#define UNARGS_PRINT_OUT_STR(x)
#define UNARGS_PRINT_OUT_TAB()
#define UNARGS_PRINT_OUT_LN()

#define UNARGS_PRINT_ERR_INT(x)
#define UNARGS_PRINT_ERR_UNSIGNED(x)
#define UNARGS_PRINT_ERR_FLOAT(x)
#define UNARGS_PRINT_ERR_STR(x)
#define UNARGS_PRINT_ERR_TAB()
#define UNARGS_PRINT_ERR_LN()

#define UNARGS_IMPLEMENTATION
#include "unargs.h"

#include <stdio.h>
#include <string.h>

typedef int (*TestFunc)(void);

#define PRINT_TEST_FAIL() \
    fprintf(stderr, "Test failed: %s:%d %s\n", __FILE__, __LINE__, __func__)

#define EXPECT_EQ(a, b) \
    do { \
        if ((a) != (b)) { \
            PRINT_TEST_FAIL(); \
            return -1; \
        } \
    } while (0)

#define EXPECT_STR_EQ(a, b) \
    do { \
        if (strcmp(a, b) != 0) { \
            PRINT_TEST_FAIL(); \
            return -1; \
        } \
    } while (0)

#define PREV_TEST NULL
TestFunc prevTest = NULL;

int testBasic(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testBasic

    char *argv[] = {
        "main",
        "-bt",
        "-i", "123",
        "-str", "abc",
        "-maybe", "maybe",
        "foo",
        "-dummy", "dummy",
        "-",
        "bar",
    };

    bool bt;
    bool bf;
    int i;
    const char *str;
    const char *maybe;
    const char *absent;
    const char *pos0;
    const char *pos1;
    const char *pos2;

    unargs_Param params[] = {
        unargs_bool("bt", NULL, &bt),
        unargs_bool("bf", NULL, &bf),
        unargs_intReq("i", NULL, &i),
        unargs_stringReq("str", NULL, &str),
        unargs_string("maybe", NULL, "", &maybe),
        unargs_string("absent", NULL, "absent", &absent),
        unargs_stringReq(NULL, NULL, &pos0),
        unargs_stringReq("dummy", NULL, NULL),
        unargs_stringReq(NULL, NULL, NULL),
        unargs_string(NULL, NULL, "", &pos1),
        unargs_string(NULL, NULL, "baz", &pos2),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) != UNARGS_OK) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(bt, true);
    EXPECT_EQ(bf, false);
    EXPECT_EQ(i, 123);
    EXPECT_STR_EQ(str, "abc");
    EXPECT_STR_EQ(maybe, "maybe");
    EXPECT_STR_EQ(absent, "absent");
    EXPECT_STR_EQ(pos0, "foo");
    EXPECT_STR_EQ(pos1, "bar");
    EXPECT_STR_EQ(pos2, "baz");

    return 0;
}

int testNoParams(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testNoParams

    char *argv[] = {
        "main",
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            0, NULL) != UNARGS_OK) {
        PRINT_TEST_FAIL();
        return -1;
    }

    return 0;
}

int testTypes(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testTypes

    char *argv[] = {
        "main",
        "-b",
        "-i", "1",
        "-u", "2",
        "-f", "1.0",
        "-str", "foo",
    };

    bool b, bdef;
    int i, idef;
    unsigned u, udef;
    float f, fdef;
    const char *str, *strdef;

    unargs_Param params[] = {
        unargs_bool("b", NULL, &b),
        unargs_bool("bdef", NULL, &bdef),
        unargs_intReq("i", NULL, &i),
        unargs_int("idef", NULL, -1, &idef),
        unargs_unsignedReq("u", NULL, &u),
        unargs_unsigned("udef", NULL, (unsigned)-2, &udef),
        unargs_floatReq("f", NULL, &f),
        unargs_float("fdef", NULL, -1.0f, &fdef),
        unargs_stringReq("str", NULL, &str),
        unargs_string("strdef", NULL, "bar", &strdef),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) != UNARGS_OK) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(b, true);
    EXPECT_EQ(bdef, false);
    EXPECT_EQ(i, 1);
    EXPECT_EQ(idef, -1);
    EXPECT_EQ(u, 2);
    EXPECT_EQ(udef, (unsigned)-2);
    EXPECT_EQ(f, 1.0f);
    EXPECT_EQ(fdef, -1.0f);
    EXPECT_STR_EQ(str, "foo");
    EXPECT_STR_EQ(strdef, "bar");

    return 0;
}

int testHelp(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testHelp

    unargs_Param params[] = {
        unargs_bool("b", NULL, NULL),
        unargs_intReq("i", "desc", NULL),
        unargs_int("idef", NULL, 1, NULL),
        unargs_unsignedReq("u", "desc", NULL),
        unargs_unsigned("udef", NULL, 1, NULL),
        unargs_floatReq("f", NULL, NULL),
        unargs_float("fdef", NULL, 0.0f, NULL),
        unargs_stringReq("str", NULL, NULL),
        unargs_string("strdef0", NULL, "1", NULL),
        unargs_string("strdef1", NULL, "", NULL),
        unargs_string("strdef2", NULL, NULL, NULL),

        unargs_intReq(NULL, NULL, NULL),
        unargs_unsignedReq(NULL, NULL, NULL),
        unargs_floatReq(NULL, "desc", NULL),
        unargs_stringReq(NULL, NULL, NULL),
        unargs_int(NULL, NULL, 1, NULL),
        unargs_unsigned(NULL, NULL, 1, NULL),
        unargs_float(NULL, NULL, 0.0f, NULL),
        unargs_string(NULL, NULL, "1", NULL),
        unargs_string(NULL, NULL, "", NULL),
        unargs_string(NULL, NULL, NULL, NULL),
    };

    unargs_help("test", sizeof(params) / sizeof(*params), params);

    return 0;
}

int testScrambled(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testScrambled

    char *argv[] = {
        "main",
        "-dummy", "dummy",
        "-b",
        "-str", "abc",
        "foo",
        "dummy",
        "-i", "123",
    };

    bool b;
    int i;
    const char *str;
    const char *pos0;

    unargs_Param params[] = {
        unargs_bool("b", NULL, &b),
        unargs_bool("begone", NULL, NULL),
        unargs_intReq("i", NULL, &i),
        unargs_stringReq("str", NULL, &str),
        unargs_stringReq(NULL, NULL, &pos0),
        unargs_stringReq("dummy", NULL, NULL),
        unargs_stringReq(NULL, NULL, NULL),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) != UNARGS_OK) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(i, 123);
    EXPECT_STR_EQ(str, "abc");
    EXPECT_STR_EQ(pos0, "foo");

    return 0;
}

int testBadParams(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testBadParams

    {
        char *argv[] = {
            "main",
            "-i", "1",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                -1, params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "-i", "1",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), NULL) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_bool(NULL, NULL, NULL),
        };

        if (unargs_help(
                NULL,
                sizeof(params) / sizeof(*params),
                params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_bool("", NULL, NULL),
        };

        if (unargs_help(
                NULL,
                sizeof(params) / sizeof(*params),
                params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_intReq("", NULL, NULL),
        };

        if (unargs_help(
                NULL,
                sizeof(params) / sizeof(*params),
                params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_int(NULL, NULL, 0, NULL),
            unargs_intReq(NULL, NULL, NULL),
        };

        if (unargs_help(
                NULL,
                sizeof(params) / sizeof(*params),
                params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
            unargs_int("i", NULL, 0, NULL),
        };

        if (unargs_help(
                NULL,
                sizeof(params) / sizeof(*params),
                params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        int i;

        unargs_Param params[] = {
            unargs_intReq("i1", NULL, &i),
            unargs_int("i2", NULL, 0, &i),
        };

        if (unargs_help(
                NULL,
                sizeof(params) / sizeof(*params),
                params) != UNARGS_ERR_PARAMS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }

    return 0;
}

int testBadArgs(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testBadArgs

    {
        char *argv[] = {
            "main",
            "-i", "xyz",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "-i", "9223372036854775807",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "-u", "9223372036854775807",
        };

        unargs_Param params[] = {
            unargs_unsignedReq("u", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "-i", "123",
            "-i", "123",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "-i", "123",
            "-j", "123",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "-i",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "foo",
            "bar",
        };

        unargs_Param params[] = {
            unargs_stringReq(NULL, NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "foo",
        };

        unargs_Param params[] = {
            unargs_stringReq(NULL, NULL, NULL),
            unargs_stringReq(NULL, NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "foo",
        };

        unargs_Param params[] = {
            unargs_stringReq(NULL, NULL, NULL),
        };

        if (unargs_parse(
                0, argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_stringReq(NULL, NULL, NULL),
        };

        if (unargs_parse(
                1, NULL,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
            "",
        };

        unargs_Param params[] = {
            unargs_stringReq(NULL, NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) != UNARGS_ERR_ARGS) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }

    return 0;
}

int main(void) {
    int ret = 0;

    TestFunc f = PREV_TEST;
    while (f != NULL) {
        if (f() != 0) ret = 1;
        f = prevTest;
    }

    return ret;
}
