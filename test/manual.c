#include "unargs.h"

int main(int argc, char *argv[]) {
    const char *path;
    int n, w, h;
    bool flip, flipH, flipV;
    bool rot, rotH, rotV;
    bool edge, edgeH, edgeV;

    unargs_Param params[] = {
        unargs_stringReq(NULL, &path),
        unargs_intReq("n", &n),
        unargs_intReq("w", &w),
        unargs_intReq("h", &h),
        unargs_bool("flip", &flip),
        unargs_bool("flipH", &flipH),
        unargs_bool("flipV", &flipV),
        unargs_bool("rot", &rot),
        unargs_bool("rotH", &rotH),
        unargs_bool("rotV", &rotV),
        unargs_bool("edge", &edge),
        unargs_bool("edgeH", &edgeH),
        unargs_bool("edgeV", &edgeV),
    };
    int len = sizeof(params) / sizeof(*params);

    if (unargs_parse(argc, argv, len, params) < 0) {
        return 1;
    }

    for (int i = 0; i < len; ++i) {
        printf("%s: ", params[i]._name);

        if (params[i]._dst == NULL) {
            printf("NULL");
        } else if (params[i]._type == unargs__TypeBool) {
            bool val = *(bool*)params[i]._dst;
            if (val) printf("true");
            else printf("false");
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
