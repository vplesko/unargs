// @TODO allow user to override assert and bool type
// @TODO add string msgs to asserts
// @TODO allow changing of function prefix
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
    unargs__TypeBool,
    unargs__TypeInt,
    unargs__TypeLong,
    unargs__TypeFloat,
    unargs__TypeDouble,
    unargs__TypeString,
};

// @TODO param descriptions
typedef struct unargs_Param {
    const char *_name;
    enum unargs__Type _type;
    bool _req;
    union {
        bool b;
        int i;
        long l;
        float f;
        double d;
        const char *str;
    } _def;

    void *_dst;

    bool _found;
} unargs_Param;

unargs_Param unargs_bool(const char *name, bool *dst) {
    assert(name != NULL);
    assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeBool,
        ._req = false,
        ._def.b = false,
        ._dst = dst,
    };
}

unargs_Param unargs_int(const char *name, int def, int *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeInt,
        ._req = false,
        ._def.i = def,
        ._dst = dst,
    };
}

unargs_Param unargs_intReq(const char *name, int *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeInt,
        ._req = true,
        ._dst = dst,
    };
}

unargs_Param unargs_long(const char *name, long def, long *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeLong,
        ._req = false,
        ._def.l = def,
        ._dst = dst,
    };
}

unargs_Param unargs_longReq(const char *name, long *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeLong,
        ._req = true,
        ._dst = dst,
    };
}

unargs_Param unargs_float(const char *name, float def, float *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeFloat,
        ._req = false,
        ._def.f = def,
        ._dst = dst,
    };
}

unargs_Param unargs_floatReq(const char *name, float *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeFloat,
        ._req = true,
        ._dst = dst,
    };
}

unargs_Param unargs_double(const char *name, double def, double *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeDouble,
        ._req = false,
        ._def.d = def,
        ._dst = dst,
    };
}

unargs_Param unargs_doubleReq(const char *name, double *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeDouble,
        ._req = true,
        ._dst = dst,
    };
}

unargs_Param unargs_string(
    const char *name, const char *def, const char **dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeString,
        ._req = false,
        ._def.str = def,
        ._dst = dst,
    };
}

unargs_Param unargs_stringReq(const char *name, const char **dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__TypeString,
        ._req = true,
        ._dst = dst,
    };
}

bool unargs__paramIsOpt(const unargs_Param *param) {
    return param->_name != NULL;
}

bool unargs__paramIsPos(const unargs_Param *param) {
    return param->_name == NULL;
}

void unargs__verifyParams(int len, const unargs_Param *params) {
    assert(len >= 0);
    if (len > 0) assert(params != NULL);

    bool posNonReqFound = false;
    for (int i = 0; i < len; ++i) {
        if (unargs__paramIsPos(&params[i])) {
            if (params[i]._req) assert(!posNonReqFound);
            else posNonReqFound = true;
        }
    }

    for (int i = 0; i < len; ++i) {
        if (!unargs__paramIsOpt(&params[i])) continue;

        for (int j = i + 1; j < len; ++j) {
            if (!unargs__paramIsOpt(&params[j])) continue;

            assert(strcmp(params[i]._name, params[j]._name) != 0);
        }
    }

    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (params[i]._dst != NULL && params[j]._dst != NULL) {
                assert(params[i]._dst != params[j]._dst);
            }
        }
    }
}

bool unargs__isOpt(const char *arg) {
    return arg[0] == '-' && arg[1] != '\0';
}

const char* unargs__optName(const char *arg) {
    return arg + 1;
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

bool unargs__optNameMatches(const char *arg, const unargs_Param *param) {
    return unargs__paramIsOpt(param) && strcmp(arg + 1, param->_name) == 0;
}

int unargs__argCnt(const unargs_Param *param) {
    if (unargs__paramIsOpt(param) && param->_type != unargs__TypeBool) return 2;
    return 1;
}

void unargs__writeDef(unargs_Param *param) {
    if (param->_type == unargs__TypeBool) {
        if (param->_dst != NULL) *(bool*)param->_dst = param->_def.b;
    } else if (param->_type == unargs__TypeInt) {
        if (param->_dst != NULL) *(int*)param->_dst = param->_def.i;
    } else if (param->_type == unargs__TypeLong) {
        if (param->_dst != NULL) *(long*)param->_dst = param->_def.l;
    } else if (param->_type == unargs__TypeFloat) {
        if (param->_dst != NULL) *(float*)param->_dst = param->_def.f;
    } else if (param->_type == unargs__TypeDouble) {
        if (param->_dst != NULL) *(double*)param->_dst = param->_def.d;
    } else if (param->_type == unargs__TypeString) {
        if (param->_dst != NULL) *(const char**)param->_dst = param->_def.str;
    } else {
        assert(false);
    }
}

int unargs__parseLong(const char *str, long *l) {
    char *end;
    *l = strtol(str, &end, 0);
    if (*end != '\0') {
        UNARGS_PRINT_STR("@TODO");
        UNARGS_PRINT_LN();
        return -1;
    }

    return 0;
}

int unargs__parseFloat(const char *str, float *f) {
    char *end;
    *f = strtof(str, &end);
    if (*end != '\0') {
        UNARGS_PRINT_STR("@TODO");
        UNARGS_PRINT_LN();
        return -1;
    }

    return 0;
}

int unargs__parseDouble(const char *str, double *d) {
    char *end;
    *d = strtod(str, &end);
    if (*end != '\0') {
        UNARGS_PRINT_STR("@TODO");
        UNARGS_PRINT_LN();
        return -1;
    }

    return 0;
}

int unargs__parseVal(const char *arg, const unargs_Param *param) {
    if (param->_type == unargs__TypeInt) {
        long l;
        if (unargs__parseLong(arg, &l) < 0) return -1;

        int i = (int)l;
        if (i != l) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }

        if (param->_dst != NULL) *(int*)param->_dst = i;
    } else if (param->_type == unargs__TypeLong) {
        long l;
        if (unargs__parseLong(arg, &l) < 0) return -1;

        if (param->_dst != NULL) *(long*)param->_dst = l;
    } else if (param->_type == unargs__TypeFloat) {
        float f;
        if (unargs__parseFloat(arg, &f) < 0) return -1;

        if (param->_dst != NULL) *(float*)param->_dst = f;
    } else if (param->_type == unargs__TypeDouble) {
        double d;
        if (unargs__parseDouble(arg, &d) < 0) return -1;

        if (param->_dst != NULL) *(double*)param->_dst = d;
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
        if (!params[p]._req) unargs__writeDef(&params[p]);
    }

    int nextPos = 0;
    while (nextPos < len && unargs__paramIsOpt(&params[nextPos])) {
        ++nextPos;
    }

    for (int a = 1; a < argc;) {
        if (unargs__isOpt(argv[a])) {
            unargs_Param *param = NULL;
            for (int p = 0; p < len && param == NULL; ++p) {
                if (unargs__optNameMatches(argv[a], &params[p])) {
                    param = &params[p];

                    if (param->_found) {
                        UNARGS_PRINT_STR("@TODO");
                        UNARGS_PRINT_LN();
                        return -1;
                    }

                    if (param->_type == unargs__TypeBool) {
                        if (param->_dst != NULL) *(bool*)param->_dst = true;
                    } else {
                        if (a + 1 >= argc) {
                            UNARGS_PRINT_STR("@TODO");
                            UNARGS_PRINT_LN();
                            return -1;
                        }

                        if (unargs__parseVal(argv[a + 1], param) < 0) {
                            return -1;
                        }
                    }

                    param->_found = true;
                }
            }

            if (param == NULL) {
                UNARGS_PRINT_STR("@TODO");
                UNARGS_PRINT_LN();
                return -1;
            }

            a += unargs__argCnt(param);
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
        if (params[p]._req && !params[p]._found) {
            UNARGS_PRINT_STR("@TODO");
            UNARGS_PRINT_LN();
            return -1;
        }
    }

    return 0;
}

// @TODO help text
int unargs_parse(
    int argc, char * const *argv,
    int len, unargs_Param *params) {
    unargs__verifyParams(len, params);
    if (unargs__verifyArgs(argc, argv) < 0) return -1;

    if (unargs__parseArgs(argc, argv, len, params) < 0) return -1;

    return 0;
}
