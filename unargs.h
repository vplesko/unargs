#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// user should define all or none
#if !defined(UNARGS_PRINT_STR) || !defined(UNARGS_PRINT_LN)
#include <stdio.h>

#define UNARGS_PRINT_STR(str) fprintf(stderr, str)
#define UNARGS_PRINT_LN() fprintf(stderr, "\n")
#endif

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
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeInt,
        ._dst = dst,
    };
}

unargs_Param unargs_string(const char *name, const char **dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeString,
        ._dst = dst,
    };
}

bool unargs__paramIsOpt(const unargs_Param *param) {
    return param->_name != NULL;
}

void unargs__verifyParams(int len, const unargs_Param *params) {
    assert(len >= 0);
    if (len > 0) assert(params != NULL);
}

int unargs__verifyArgs(int argc, char * const *argv) {
    if (argc < 1) {
        UNARGS_PRINT_STR("@TODO");
        UNARGS_PRINT_LN();
        return -1;
    }
    if (argv == NULL) {
        UNARGS_PRINT_STR("@TODO");
        UNARGS_PRINT_LN();
        return -1;
    }
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == NULL) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }
        if (strlen(argv[i]) == 0) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }
    }

    return 0;
}

bool unargs__isOpt(const char *arg) {
    return arg[0] == '-' && arg[1] != '\0';
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
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }

        int i = (int)l;
        if (i != l) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
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
    int len, const unargs_Param *params) {
    for (int p = 0; p < len; ++p) {
        if (!unargs__paramIsOpt(&params[p])) continue;

        bool found = false;

        for (int a = 1; a < argc;) {
            if (unargs__isOpt(argv[a])) {
                if (strcmp(params[p]._name, unargs__optName(argv[a])) == 0) {
                    if (found) {
                        UNARGS_PRINT_STR("@TODO");
                        UNARGS_PRINT_LN();
                        return -1;
                    }

                    if (a + 1 >= argc) {
                        UNARGS_PRINT_STR("@TODO");
                        UNARGS_PRINT_LN();
                        return -1;
                    }
                    if (unargs__parseVal(argv[a + 1], &params[p]) < 0) {
                        return -1;
                    }

                    found = true;
                }

                a += 2;
            } else {
                a += 1;
            }
        }

        if (!found) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }
    }

    return 0;
}

int unargs__parsePoss(
    int argc, char * const *argv,
    int len, const unargs_Param *params) {
    int a = 1;
    int p = 0;
    while (a < argc && p < len) {
        if (unargs__paramIsOpt(&params[p])) {
            ++p;
            continue;
        }

        if (unargs__isOpt(argv[a])) {
            a += 2;
        } else {
            if (unargs__parseVal(argv[a], &params[p]) < 0) return -1;
            ++p;

            a += 1;
        }
    }

    while (a < argc) {
        if (unargs__isOpt(argv[a])) {
            a += 2;
        } else {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }
    }

    if (p < len) {
        UNARGS_PRINT_STR("@TODO");
        UNARGS_PRINT_LN();
        return -1;
    }

    return 0;
}

int unargs_parse(
    int argc, char * const *argv,
    int len, const unargs_Param *params) {
    unargs__verifyParams(len, params);
    unargs__verifyArgs(argc, argv);

    if (unargs__parseOpts(argc, argv, len, params) < 0) return -1;
    if (unargs__parsePoss(argc, argv, len, params) < 0) return -1;

    return 0;
}
