#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

const char* unargs__optName(const char *arg) {
    return arg + 1;
}

int unargs__parseVal(const char *arg, const unargs_Param *param) {
    if (param->_type == unargs__TypeInt) {
        long l;
        char *end;
        l = strtol(arg, &end, 0);
        if (*end != '\0') {
            fprintf(stderr, "@TODO\n");
            return -1;
        }

        int i = (int)l;
        if (i != l) {
            fprintf(stderr, "@TODO\n");
            return -1;
        }

        if (param->_dst != NULL) *(int*)param->_dst = i;
    } else if (param->_type == unargs__TypeString) {
        if (param->_dst != NULL) *(const char**)param->_dst = arg;
    } else {
        assert(false);
    }

    return 0;
}

int unargs__parseOpts(
    int argc, char * const *argv,
    size_t len, const unargs_Param *params) {
    for (size_t p = 0; p < len; ++p) {
        bool found = false;

        for (int a = 1; a < argc; a += 2) {
            if (strcmp(params[p]._name, unargs__optName(argv[a])) == 0) {
                if (found) {
                    fprintf(stderr, "@TODO\n");
                    return -1;
                }

                if (unargs__parseVal(argv[a + 1], &params[p]) < 0) return -1;

                found = true;
            }
        }

        if (!found) {
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

    if (unargs__parseOpts(argc, argv, len, params) < 0) return -1;

    return 0;
}
