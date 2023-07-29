// @TODO allow user to override assert and bool type
// @TODO add string msgs to asserts
// @TODO allow changing of function prefix
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// When adding new types, update code wherever this comment appears.
// (Add similar macros for the new types.)
#if !defined(UNARGS_PRINT_OUT_INT)
#include <stdio.h>
#define UNARGS_PRINT_OUT_INT(x) fprintf(stdout, "%d", x)
#endif

#if !defined(UNARGS_PRINT_OUT_LONG)
#include <stdio.h>
#define UNARGS_PRINT_OUT_LONG(x) fprintf(stdout, "%ld", x)
#endif

#if !defined(UNARGS_PRINT_OUT_FLOAT)
#include <stdio.h>
#define UNARGS_PRINT_OUT_FLOAT(x) fprintf(stdout, "%f", x)
#endif

#if !defined(UNARGS_PRINT_OUT_DOUBLE)
#include <stdio.h>
#define UNARGS_PRINT_OUT_DOUBLE(x) fprintf(stdout, "%f", x)
#endif

#if !defined(UNARGS_PRINT_OUT_STR)
#include <stdio.h>
#define UNARGS_PRINT_OUT_STR(x) fprintf(stdout, "%s", x)
#endif

#if !defined(UNARGS_PRINT_OUT_TAB)
#include <stdio.h>
#define UNARGS_PRINT_OUT_TAB() fprintf(stdout, "\t")
#endif

#if !defined(UNARGS_PRINT_OUT_LN)
#include <stdio.h>
#define UNARGS_PRINT_OUT_LN() fprintf(stdout, "\n")
#endif

// When adding new types, update code wherever this comment appears.
// (Add similar macros for the new types.)
#if !defined(UNARGS_PRINT_ERR_INT)
#include <stdio.h>
#define UNARGS_PRINT_ERR_INT(x) fprintf(stderr, "%d", x)
#endif

#if !defined(UNARGS_PRINT_ERR_LONG)
#include <stdio.h>
#define UNARGS_PRINT_ERR_LONG(x) fprintf(stderr, "%ld", x)
#endif

#if !defined(UNARGS_PRINT_ERR_FLOAT)
#include <stdio.h>
#define UNARGS_PRINT_ERR_FLOAT(x) fprintf(stderr, "%f", x)
#endif

#if !defined(UNARGS_PRINT_ERR_DOUBLE)
#include <stdio.h>
#define UNARGS_PRINT_ERR_DOUBLE(x) fprintf(stderr, "%f", x)
#endif

#if !defined(UNARGS_PRINT_ERR_STR)
#include <stdio.h>
#define UNARGS_PRINT_ERR_STR(x) fprintf(stderr, "%s", x)
#endif

#if !defined(UNARGS_PRINT_ERR_TAB)
#include <stdio.h>
#define UNARGS_PRINT_ERR_TAB() fprintf(stderr, "\t")
#endif

#if !defined(UNARGS_PRINT_ERR_LN)
#include <stdio.h>
#define UNARGS_PRINT_ERR_LN() fprintf(stderr, "\n")
#endif

// When adding new types, update code wherever this comment appears.
enum unargs__Type {
    unargs__typeBool,
    unargs__typeInt,
    unargs__typeLong,
    unargs__typeFloat,
    unargs__typeDouble,
    unargs__typeString,
};

typedef struct unargs_Param {
    const char *_name;
    enum unargs__Type _type;
    bool _req;
    const char *_desc;

// When adding new types, update code wherever this comment appears.
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

unargs_Param unargs_bool(
    const char *name, const char *desc, bool *dst) {
    assert(name != NULL);
    assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeBool,
        ._req = false,
        ._desc = desc,
        ._def.b = false,
        ._dst = dst,
    };
}

// When adding new types, update code wherever this comment appears.
// (Add similar functions for the new types. Change:
//   function name;
//   type of def and dst arguments;
//   value of _type;
//   assignment to _def.X.)
unargs_Param unargs_int(
    const char *name, const char *desc, int def, int *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeInt,
        ._req = false,
        ._desc = desc,
        ._def.i = def,
        ._dst = dst,
    };
}

// When adding new types, update code wherever this comment appears.
// (Add similar functions for the new types. Change:
//   function name;
//   type of dst argument;
//   value of _type.)
unargs_Param unargs_intReq(
    const char *name, const char *desc, int *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeInt,
        ._req = true,
        ._desc = desc,
        ._dst = dst,
    };
}

unargs_Param unargs_long(
    const char *name, const char *desc, long def, long *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeLong,
        ._req = false,
        ._desc = desc,
        ._def.l = def,
        ._dst = dst,
    };
}

unargs_Param unargs_longReq(
    const char *name, const char *desc, long *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeLong,
        ._req = true,
        ._desc = desc,
        ._dst = dst,
    };
}

unargs_Param unargs_float(
    const char *name, const char *desc, float def, float *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeFloat,
        ._req = false,
        ._desc = desc,
        ._def.f = def,
        ._dst = dst,
    };
}

unargs_Param unargs_floatReq(
    const char *name, const char *desc, float *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeFloat,
        ._req = true,
        ._desc = desc,
        ._dst = dst,
    };
}

unargs_Param unargs_double(
    const char *name, const char *desc, double def, double *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeDouble,
        ._req = false,
        ._desc = desc,
        ._def.d = def,
        ._dst = dst,
    };
}

unargs_Param unargs_doubleReq(
    const char *name, const char *desc, double *dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeDouble,
        ._req = true,
        ._desc = desc,
        ._dst = dst,
    };
}

unargs_Param unargs_string(
    const char *name, const char *desc, const char *def, const char **dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeString,
        ._req = false,
        ._desc = desc,
        ._def.str = def,
        ._dst = dst,
    };
}

unargs_Param unargs_stringReq(
    const char *name, const char *desc, const char **dst) {
    if (name != NULL) assert(strlen(name) > 0);

    return (unargs_Param){
        ._name = name,
        ._type = unargs__typeString,
        ._req = true,
        ._desc = desc,
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
        UNARGS_PRINT_ERR_STR("@TODO");
        UNARGS_PRINT_ERR_LN();
        return -1;
    }
    if (argv == NULL) {
        UNARGS_PRINT_ERR_STR("@TODO");
        UNARGS_PRINT_ERR_LN();
        return -1;
    }
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == NULL) {
            UNARGS_PRINT_ERR_STR("@TODO");
            UNARGS_PRINT_ERR_LN();
            return -1;
        }
        if (strlen(argv[i]) == 0) {
            UNARGS_PRINT_ERR_STR("@TODO");
            UNARGS_PRINT_ERR_LN();
            return -1;
        }
    }

    return 0;
}

bool unargs__optNameMatches(const char *arg, const unargs_Param *param) {
    return unargs__paramIsOpt(param) && strcmp(arg + 1, param->_name) == 0;
}

int unargs__argCnt(const unargs_Param *param) {
    if (unargs__paramIsOpt(param) && param->_type != unargs__typeBool) return 2;
    return 1;
}

// When adding new types, update code wherever this comment appears.
void unargs__writeDef(unargs_Param *param) {
    if (param->_type == unargs__typeBool) {
        if (param->_dst != NULL) *(bool*)param->_dst = param->_def.b;
    } else if (param->_type == unargs__typeInt) {
        if (param->_dst != NULL) *(int*)param->_dst = param->_def.i;
    } else if (param->_type == unargs__typeLong) {
        if (param->_dst != NULL) *(long*)param->_dst = param->_def.l;
    } else if (param->_type == unargs__typeFloat) {
        if (param->_dst != NULL) *(float*)param->_dst = param->_def.f;
    } else if (param->_type == unargs__typeDouble) {
        if (param->_dst != NULL) *(double*)param->_dst = param->_def.d;
    } else if (param->_type == unargs__typeString) {
        if (param->_dst != NULL) *(const char**)param->_dst = param->_def.str;
    } else {
        assert(false);
    }
}

int unargs__parseLong(const char *str, long *l) {
    char *end;
    *l = strtol(str, &end, 0);
    if (*end != '\0') {
        UNARGS_PRINT_ERR_STR("@TODO");
        UNARGS_PRINT_ERR_LN();
        return -1;
    }

    return 0;
}

int unargs__parseFloat(const char *str, float *f) {
    char *end;
    *f = strtof(str, &end);
    if (*end != '\0') {
        UNARGS_PRINT_ERR_STR("@TODO");
        UNARGS_PRINT_ERR_LN();
        return -1;
    }

    return 0;
}

int unargs__parseDouble(const char *str, double *d) {
    char *end;
    *d = strtod(str, &end);
    if (*end != '\0') {
        UNARGS_PRINT_ERR_STR("@TODO");
        UNARGS_PRINT_ERR_LN();
        return -1;
    }

    return 0;
}

// When adding new types, update code wherever this comment appears.
int unargs__parseVal(const char *arg, const unargs_Param *param) {
    if (param->_type == unargs__typeInt) {
        long l;
        if (unargs__parseLong(arg, &l) < 0) return -1;

        int i = (int)l;
        if (i != l) {
            UNARGS_PRINT_ERR_STR("@TODO");
            UNARGS_PRINT_ERR_LN();
            return -1;
        }

        if (param->_dst != NULL) *(int*)param->_dst = i;
    } else if (param->_type == unargs__typeLong) {
        long l;
        if (unargs__parseLong(arg, &l) < 0) return -1;

        if (param->_dst != NULL) *(long*)param->_dst = l;
    } else if (param->_type == unargs__typeFloat) {
        float f;
        if (unargs__parseFloat(arg, &f) < 0) return -1;

        if (param->_dst != NULL) *(float*)param->_dst = f;
    } else if (param->_type == unargs__typeDouble) {
        double d;
        if (unargs__parseDouble(arg, &d) < 0) return -1;

        if (param->_dst != NULL) *(double*)param->_dst = d;
    } else if (param->_type == unargs__typeString) {
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
                        UNARGS_PRINT_ERR_STR("@TODO");
                        UNARGS_PRINT_ERR_LN();
                        return -1;
                    }

                    if (param->_type == unargs__typeBool) {
                        if (param->_dst != NULL) *(bool*)param->_dst = true;
                    } else {
                        if (a + 1 >= argc) {
                            UNARGS_PRINT_ERR_STR("@TODO");
                            UNARGS_PRINT_ERR_LN();
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
                UNARGS_PRINT_ERR_STR("@TODO");
                UNARGS_PRINT_ERR_LN();
                return -1;
            }

            a += unargs__argCnt(param);
        } else {
            if (nextPos >= len) {
                UNARGS_PRINT_ERR_STR("@TODO");
                UNARGS_PRINT_ERR_LN();
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
            UNARGS_PRINT_ERR_STR("@TODO");
            UNARGS_PRINT_ERR_LN();
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

// When adding new types, update code wherever this comment appears.
void unargs__printType(enum unargs__Type type) {
    if (type == unargs__typeInt) UNARGS_PRINT_OUT_STR("<int>");
    else if (type == unargs__typeLong) UNARGS_PRINT_OUT_STR("<long>");
    else if (type == unargs__typeFloat) UNARGS_PRINT_OUT_STR("<float>");
    else if (type == unargs__typeDouble) UNARGS_PRINT_OUT_STR("<double>");
    else if (type == unargs__typeString) UNARGS_PRINT_OUT_STR("<string>");
    else assert(false);
}

// When adding new types, update code wherever this comment appears.
void unargs__printDef(const unargs_Param *param) {
    if (param->_type == unargs__typeInt) {
        UNARGS_PRINT_OUT_INT(param->_def.i);
    } else if (param->_type == unargs__typeLong) {
        UNARGS_PRINT_OUT_LONG(param->_def.l);
    } else if (param->_type == unargs__typeFloat) {
        UNARGS_PRINT_OUT_FLOAT(param->_def.f);
    } else if (param->_type == unargs__typeDouble) {
        UNARGS_PRINT_OUT_DOUBLE(param->_def.d);
    } else if (param->_type == unargs__typeString) {
        UNARGS_PRINT_OUT_STR(param->_def.str);
    } else {
        assert(false);
    }
}

void unargs__printUsage(
    const char *program, int len, const unargs_Param *params) {
    UNARGS_PRINT_OUT_STR("Usage: ");

    if (program != NULL) UNARGS_PRINT_OUT_STR(program);

    for (int i = 0; i < len; ++i) {
        const unargs_Param *param = &params[i];

        if (unargs__paramIsPos(param) && param->_req) {
            UNARGS_PRINT_OUT_STR(" ");
            unargs__printType(param->_type);
        }
    }

    for (int i = 0; i < len; ++i) {
        const unargs_Param *param = &params[i];

        if (unargs__paramIsOpt(param) && param->_req) {
            UNARGS_PRINT_OUT_STR(" -");
            UNARGS_PRINT_OUT_STR(param->_name);
            UNARGS_PRINT_OUT_STR(" ");
            unargs__printType(param->_type);
        }
    }

    bool hasNonReqPos = false;
    for (int i = 0; i < len; ++i) {
        const unargs_Param *param = &params[i];

        if (unargs__paramIsPos(param) && !param->_req) {
            hasNonReqPos = true;
            break;
        }
    }
    if (hasNonReqPos) UNARGS_PRINT_OUT_STR(" [positionals]");

    bool hasNonReqOpt = false;
    for (int i = 0; i < len; ++i) {
        const unargs_Param *param = &params[i];

        if (unargs__paramIsOpt(param) && !param->_req) {
            hasNonReqOpt = true;
            break;
        }
    }
    if (hasNonReqOpt) UNARGS_PRINT_OUT_STR(" [options]");

    UNARGS_PRINT_OUT_LN();
}

void unargs__printRequired(const unargs_Param *param) {
    if (param->_req) {
        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_STR("(required)");
        UNARGS_PRINT_OUT_LN();
    }
}

void unargs__printDescription(const unargs_Param *param) {
    if (param->_desc != NULL) {
        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_STR(param->_desc);
        UNARGS_PRINT_OUT_LN();
    }
}

void unargs__printDefault(const unargs_Param *param) {
    if (!param->_req && param->_type != unargs__typeBool) {
        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_STR("Default: ");
        unargs__printDef(param);
        UNARGS_PRINT_OUT_LN();
    }
}

void unargs__printPositionals(int len, const unargs_Param *params) {
    bool hasPos = false;
    for (int i = 0; i < len; ++i) {
        if (unargs__paramIsPos(&params[i])) {
            hasPos = true;
            break;
        }
    }
    if (!hasPos) return;

    UNARGS_PRINT_OUT_STR("Positionals:");
    UNARGS_PRINT_OUT_LN();
    for (int i = 0; i < len; ++i) {
        const unargs_Param *param = &params[i];
        if (!unargs__paramIsPos(param)) continue;

        UNARGS_PRINT_OUT_TAB();
        unargs__printType(param->_type);
        UNARGS_PRINT_OUT_LN();

        unargs__printRequired(param);
        unargs__printDescription(param);
        unargs__printDefault(param);
    }
}

void unargs__printOptions(int len, const unargs_Param *params) {
    bool hasOpt = false;
    for (int i = 0; i < len; ++i) {
        if (unargs__paramIsOpt(&params[i])) {
            hasOpt = true;
            break;
        }
    }
    if (!hasOpt) return;

    UNARGS_PRINT_OUT_STR("Options:");
    UNARGS_PRINT_OUT_LN();
    for (int i = 0; i < len; ++i) {
        const unargs_Param *param = &params[i];
        if (!unargs__paramIsOpt(param)) continue;

        UNARGS_PRINT_OUT_TAB();
        UNARGS_PRINT_OUT_STR("-");
        UNARGS_PRINT_OUT_STR(param->_name);
        if (param->_type != unargs__typeBool) {
            UNARGS_PRINT_OUT_STR(" ");
            unargs__printType(param->_type);
        }
        UNARGS_PRINT_OUT_LN();

        unargs__printRequired(param);
        unargs__printDescription(param);
        unargs__printDefault(param);
    }
}

void unargs_help(const char *program, int len, const unargs_Param *params) {
    unargs__verifyParams(len, params);

    unargs__printUsage(program, len, params);
    unargs__printPositionals(len, params);
    unargs__printOptions(len, params);
}
