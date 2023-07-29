#define UNARGS_PRINT_OUT_INT(x)
#define UNARGS_PRINT_OUT_LONG(x)
#define UNARGS_PRINT_OUT_FLOAT(x)
#define UNARGS_PRINT_OUT_DOUBLE(x)
#define UNARGS_PRINT_OUT_STR(x)
#define UNARGS_PRINT_OUT_TAB()
#define UNARGS_PRINT_OUT_LN()

#define UNARGS_PRINT_ERR_INT(x)
#define UNARGS_PRINT_ERR_LONG(x)
#define UNARGS_PRINT_ERR_FLOAT(x)
#define UNARGS_PRINT_ERR_DOUBLE(x)
#define UNARGS_PRINT_ERR_STR(x)
#define UNARGS_PRINT_ERR_TAB()
#define UNARGS_PRINT_ERR_LN()

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
        unargs_bool("bt", &bt),
        unargs_bool("bf", &bf),
        unargs_intReq("i", &i),
        unargs_stringReq("str", &str),
        unargs_string("maybe", "", &maybe),
        unargs_string("absent", "absent", &absent),
        unargs_stringReq(NULL, &pos0),
        unargs_stringReq("dummy", NULL),
        unargs_stringReq(NULL, NULL),
        unargs_string(NULL, "", &pos1),
        unargs_string(NULL, "baz", &pos2),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) < 0) {
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

// When adding new types, update code wherever this comment appears.
int testTypes(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testTypes

    char *argv[] = {
        "main",
        "-b",
        "-i", "1",
        "-l", "9223372036854775807",
        "-f", "1.0",
        "-d", "2.0",
        "-str", "foo",
    };

    bool b, bdef;
    int i, idef;
    long l, ldef;
    float f, fdef;
    double d, ddef;
    const char *str, *strdef;

    unargs_Param params[] = {
        unargs_bool("b", &b),
        unargs_bool("bdef", &bdef),
        unargs_intReq("i", &i),
        unargs_int("idef", -1, &idef),
        unargs_longReq("l", &l),
        unargs_long("ldef", -9223372036854775807, &ldef),
        unargs_floatReq("f", &f),
        unargs_float("fdef", -1.0f, &fdef),
        unargs_doubleReq("d", &d),
        unargs_double("ddef", -2.0, &ddef),
        unargs_stringReq("str", &str),
        unargs_string("strdef", "bar", &strdef),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) < 0) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(b, true);
    EXPECT_EQ(bdef, false);
    EXPECT_EQ(i, 1);
    EXPECT_EQ(idef, -1);
    EXPECT_EQ(l, 9223372036854775807);
    EXPECT_EQ(ldef, -9223372036854775807);
    EXPECT_EQ(f, 1.0f);
    EXPECT_EQ(fdef, -1.0f);
    EXPECT_EQ(d, 2.0);
    EXPECT_EQ(ddef, -2.0);
    EXPECT_STR_EQ(str, "foo");
    EXPECT_STR_EQ(strdef, "bar");

    return 0;
}

// When adding new types, update code wherever this comment appears.
int testHelp(void) {
    prevTest = PREV_TEST;
#undef PREV_TEST
#define PREV_TEST testHelp

    unargs_Param params[] = {
        unargs_bool("b", NULL),
        unargs_intReq("i", NULL),
        unargs_int("idef", 1, NULL),
        unargs_longReq("l", NULL),
        unargs_long("ldef", 1, NULL),
        unargs_floatReq("f", NULL),
        unargs_float("fdef", 0.0f, NULL),
        unargs_doubleReq("d", NULL),
        unargs_double("ddef", 0.0, NULL),
        unargs_stringReq("str", NULL),
        unargs_string("strdef", "1", NULL),

        unargs_intReq(NULL, NULL),
        unargs_longReq(NULL, NULL),
        unargs_floatReq(NULL, NULL),
        unargs_doubleReq(NULL, NULL),
        unargs_stringReq(NULL, NULL),
        unargs_int(NULL, 1, NULL),
        unargs_long(NULL, 1, NULL),
        unargs_float(NULL, 0.0f, NULL),
        unargs_double(NULL, 0.0, NULL),
        unargs_string(NULL, "1", NULL),
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
        unargs_bool("b", &b),
        unargs_bool("begone", NULL),
        unargs_intReq("i", &i),
        unargs_stringReq("str", &str),
        unargs_stringReq(NULL, &pos0),
        unargs_stringReq("dummy", NULL),
        unargs_stringReq(NULL, NULL),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) < 0) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(i, 123);
    EXPECT_STR_EQ(str, "abc");
    EXPECT_STR_EQ(pos0, "foo");

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
            unargs_intReq("i", NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_intReq("i", NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_intReq("i", NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_intReq("i", NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_intReq("i", NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        char *argv[] = {
            "main",
        };

        unargs_Param params[] = {
            unargs_intReq("i", NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_stringReq(NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_stringReq(NULL, NULL),
            unargs_stringReq(NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_stringReq(NULL, NULL),
        };

        if (unargs_parse(
                0, argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }
    {
        unargs_Param params[] = {
            unargs_stringReq(NULL, NULL),
        };

        if (unargs_parse(
                1, NULL,
                sizeof(params) / sizeof(*params), params) >= 0) {
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
            unargs_stringReq(NULL, NULL),
        };

        if (unargs_parse(
                sizeof(argv) / sizeof(*argv), argv,
                sizeof(params) / sizeof(*params), params) >= 0) {
            PRINT_TEST_FAIL();
            return -1;
        }
    }

    return 0;
}

int main(void) {
    TestFunc f = PREV_TEST;
    while (f != NULL) {
        if (f() != 0) return -1;
        f = prevTest;
    }

    return 0;
}
