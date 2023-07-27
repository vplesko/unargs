#include <assert.h>
#include <stdio.h>
#include <string.h>

enum unargs__Type {
    unargs__TypeInt,
    unargs__TypeString,
};

typedef struct unargs_Param {
    const char *_name;
    enum unargs__Type _type;

    void *_dst;
} unargs_Param;

unargs_Param unargs_int(const char *name, int *dst) {
    assert(name != NULL);
    assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeInt,
        ._dst = dst,
    };
}

unargs_Param unargs_string(const char *name, const char **dst) {
    assert(name != NULL);
    assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeString,
        ._dst = dst,
    };
}

void unargs__verifyParams(size_t len, const unargs_Param *params) {
    if (len > 0) assert(params != NULL);
}

int unargs__verifyArgs(int argc, char * const *argv) {
    if (argc < 1) {
        fprintf(stderr, "@TODO\n");
        return -1;
    }
    if (argv == NULL) {
        fprintf(stderr, "@TODO\n");
        return -1;
    }
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == NULL) {
            fprintf(stderr, "@TODO\n");
            return -1;
        }
        if (strlen(argv[i]) == 0) {
            fprintf(stderr, "@TODO\n");
            return -1;
        }
    }

    return 0;
}

int unargs_parse(
    int argc, char * const *argv,
    size_t len, const unargs_Param *params) {
    unargs__verifyParams(len, params);
    unargs__verifyArgs(argc, argv);

    return 0;
}
