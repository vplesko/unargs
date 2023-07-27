#include <assert.h>
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

int unargs_parse(
    int argc, char * const *argv,
    size_t len, const unargs_Param *params) {
    assert(argc >= 1);
    assert(argv != NULL);
    for (int i = 0; i < argc; ++i) {
        assert(argv[i] != NULL);
        assert(strlen(argv[i]) > 0);
    }
    if (len > 0) assert(params != NULL);

    return 0;
}
