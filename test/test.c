#include "unargs.h"

int testBasic(void) {
    if (unargs_parse() < 0) return -1;

    return 0;
}

int main(void) {
    if (testBasic() != 0) {
        return -1;
    }

    return 0;
}
