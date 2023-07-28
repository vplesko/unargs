#include "unargs.h"

int main(int argc, char *argv[]) {
    int i;
    const char *str;
    int x;

    unargs_Param params[] = {
        unargs_int("i", &i),
        unargs_string("str", &str),
        unargs_int(NULL, &x),
    };
    int len = sizeof(params) / sizeof(*params);

    if (unargs_parse(argc, argv, len, params) < 0) {
        return 1;
    }

    for (int i = 0; i < len; ++i) {
        printf("%s: ", params[i]._name);

        if (params[i]._dst == NULL) {
            printf("NULL");
        } else if (params[i]._type == unargs__TypeInt) {
            printf("%d", *(int*)params[i]._dst);
        } else if (params[i]._type == unargs__TypeString) {
            printf("\"%s\"", *(const char**)params[i]._dst);
        } else {
            assert(false);
        }

        printf("\n");
    }

    return 0;
}
