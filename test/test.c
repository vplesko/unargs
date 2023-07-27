#include <stdio.h>

#include "unargs.h"

#define PRINT_TEST_FAIL() \
    fprintf(stderr, "Test failed: %s:%d %s\n", __FILE__, __LINE__, __func__)

int testBasic(void) {
    char *argv[] = {
        "main",
    };
    int argc = sizeof(argv) / sizeof(*argv);

    unargs_Param params[] = {
        unargs_int("i", NULL),
        unargs_string("str", NULL),
    };

    if (unargs_parse(argc, argv,
            sizeof(params) / sizeof(*params), params) < 0) {
        PRINT_TEST_FAIL();
        return -1;
    }

    return 0;
}

int main(void) {
    if (testBasic() != 0) {
        return -1;
    }

    return 0;
}
