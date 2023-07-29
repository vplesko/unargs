#include "test_multi.h"

#define UNARGS_IMPLEMENTATION
#include "unargs.h"

int parseArgs(int argc, char *argv[]) {
    unargs_Param params[] = {
        unargs_int(NULL, NULL, 0, NULL),
    };
    int len = sizeof(params) / sizeof(*params);

    return unargs_parse(argc, argv, len, params);
}
