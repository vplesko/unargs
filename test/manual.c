#define UNARGS_IMPLEMENTATION
#include "unargs.h"

int main(int argc, char *argv[]) {
    int i1, i2, i3, i4;
    bool b;

    unargs_Param params[] = {
        unargs_intReq("i1", "Description.", &i1),
        unargs_int("i2", "Description.", 100, &i2),
        unargs_intReq(NULL, "Description.", &i3),
        unargs_int(NULL, "Description.", 200, &i4),
        unargs_bool("b", "Description.", &b),
    };
    int len = sizeof(params) / sizeof(*params);

    unargs_Status status = unargs_parse(argc, argv, len, params);
    if (status != unargs_ok) {
        if (status == unargs_err_args) {
            fprintf(stderr, "\n");
            unargs_help("manual", len, params);
        }

        return 1;
    }

    printf("i1=%d i2=%d i3=%d i4=%d b=%s\n",
        i1, i2, i3, i4, b ? "true" : "false");

    return 0;
}
