#define UNARGS_IMPLEMENTATION
#include "unargs.h"

int main(int argc, char *argv[]) {
    bool b;

    unargs_Param params[] = {
        unargs_int(nullptr, nullptr, 0, nullptr),
        unargs_bool("-b", nullptr, &b),
    };
    int len = sizeof(params) / sizeof(*params);

    if (unargs_parse(argc, argv, len, params) < 0) return 1;

    return 0;
}
