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

    bool _found;
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

// @TODO verify that no two params have the same name
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

bool unargs__optNameMatches(const char *arg, const unargs_Param *param) {
    return param->_name != NULL && strcmp(arg + 1, param->_name) == 0;
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

int unargs__parseArgs(
    int argc, char * const *argv,
    int len, unargs_Param *params) {
    for (int p = 0; p < len; ++p) {
        params[p]._found = false;
    }

    int nextPos = 0;
    while (nextPos < len && unargs__paramIsOpt(&params[nextPos])) {
        ++nextPos;
    }

    for (int a = 1; a < argc;) {
        if (unargs__isOpt(argv[a])) {
            bool found = false;
            for (int p = 0; p < len && !found; ++p) {
                if (unargs__optNameMatches(argv[a], &params[p])) {
                    if (params[p]._found) {
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
                    params[p]._found = true;
                    found = true;
                }
            }

            if (!found) {
                UNARGS_PRINT_STR("@TODO");
                UNARGS_PRINT_LN();
                return -1;
            }

            a += 2;
        } else {
            if (nextPos >= len) {
                UNARGS_PRINT_STR("@TODO");
                UNARGS_PRINT_LN();
                return -1;
            }

            if (unargs__parseVal(argv[a], &params[nextPos]) < 0) {
                return -1;
            }
            params[nextPos]._found = true;

            ++nextPos;
            while (nextPos < len && unargs__paramIsOpt(&params[nextPos])) {
                ++nextPos;
            }

            a += 1;
        }
    }

    for (int p = 0; p < len; ++p) {
        if (!params[p]._found) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }
    }

    return 0;
}

int unargs_parse(
    int argc, char * const *argv,
    int len, unargs_Param *params) {
    unargs__verifyParams(len, params);
    if (unargs__verifyArgs(argc, argv) < 0) return -1;

    if (unargs__parseArgs(argc, argv, len, params) < 0) return -1;

    return 0;
}
