#include "unargs.h"

int main(int argc, char *argv[]) {
    const char *path;
    int n, w, h;
    bool flip, flipH, flipV;
    bool rot, rotH, rotV;
    bool edge, edgeH, edgeV;

    unargs_Param params[] = {
        unargs_stringReq(NULL, "Input image path.", &path),
        unargs_intReq("n", "N parameter.", &n),
        unargs_intReq("w", "Output width.", &w),
        unargs_intReq("h", "Output height.", &h),
        unargs_bool("flip", NULL, &flip),
        unargs_bool("flipH", NULL, &flipH),
        unargs_bool("flipV", NULL, &flipV),
        unargs_bool("rot", NULL, &rot),
        unargs_bool("rotH", NULL, &rotH),
        unargs_bool("rotV", NULL, &rotV),
        unargs_bool("edge", NULL, &edge),
        unargs_bool("edgeH", NULL, &edgeH),
        unargs_bool("edgeV", NULL, &edgeV),
    };
    int len = sizeof(params) / sizeof(*params);

    if (unargs_parse(argc, argv, len, params) < 0) {
        fprintf(stderr, "\n");
        unargs_help("manual", len, params);

        return 1;
    }

    for (int i = 0; i < len; ++i) {
        printf("%s: ", params[i]._name);

        if (params[i]._dst == NULL) {
            printf("NULL");
        } else if (params[i]._type == unargs__typeBool) {
            bool val = *(bool*)params[i]._dst;
            if (val) printf("true");
            else printf("false");
        } else if (params[i]._type == unargs__typeInt) {
            printf("%d", *(int*)params[i]._dst);
        } else if (params[i]._type == unargs__typeString) {
            printf("\"%s\"", *(const char**)params[i]._dst);
        } else {
            assert(false);
        }

        printf("\n");
    }

    return 0;
}
