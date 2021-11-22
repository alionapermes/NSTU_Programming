#include "../../lib/scrsys/io.h"
#include "../../lib/scrsys/network.h"
#include "tools.h"


int
main(size_t argc, char** argv)
{
    char* target = NULL;
    char* pair = NULL;

    process_args(argc, argv, &target, &pair);

    printf("target: %s\n", target);
    printf("pair: %s\n", pair);

    return 0;
}
