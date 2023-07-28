#define UNARGS_PRINT_STR(str)
#define UNARGS_PRINT_LN()
#include "unargs.h"

#include <stdio.h>
#include <string.h>

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

int testBasic(void) {
    char *argv[] = {
        "main",
        "-i", "123",
        "-str", "abc",
        "foo",
        "-dummy", "dummy",
        "-",
    };

    int i;
    const char *str;
    const char *posStr;

    unargs_Param params[] = {
        unargs_int("i", &i),
        unargs_string("str", &str),
        unargs_string(NULL, &posStr),
        unargs_string("dummy", NULL),
        unargs_string(NULL, NULL),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) < 0) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(i, 123);
    EXPECT_STR_EQ(str, "abc");
    EXPECT_STR_EQ(posStr, "foo");

    return 0;
}

int testScrambled(void) {
    char *argv[] = {
        "main",
        "-dummy", "dummy",
        "-str", "abc",
        "foo",
        "dummy",
        "-i", "123",
    };

    int i;
    const char *str;
    const char *posStr;

    unargs_Param params[] = {
        unargs_int("i", &i),
        unargs_string("str", &str),
        unargs_string(NULL, &posStr),
        unargs_string("dummy", NULL),
        unargs_string(NULL, NULL),
    };

    if (unargs_parse(
            sizeof(argv) / sizeof(*argv), argv,
            sizeof(params) / sizeof(*params), params) < 0) {
        PRINT_TEST_FAIL();
        return -1;
    }

    EXPECT_EQ(i, 123);
    EXPECT_STR_EQ(str, "abc");
    EXPECT_STR_EQ(posStr, "foo");

    return 0;
}

int testBadArgs(void) {
    {
        char *argv[] = {
            "main",
            "-i", "xyz",
        };

        unargs_Param params[] = {
            unargs_int("i", NULL),
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
            unargs_int("i", NULL),
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
            unargs_int("i", NULL),
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
            unargs_int("i", NULL),
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
            unargs_int("i", NULL),
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
            unargs_string(NULL, NULL),
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
            unargs_string(NULL, NULL),
            unargs_string(NULL, NULL),
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
    if (testBasic() != 0 ||
        testBadArgs() != 0) {
        return -1;
    }

    return 0;
}
