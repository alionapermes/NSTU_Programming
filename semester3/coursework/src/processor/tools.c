#include "tools.h"


void
print_help(void)
{
    printf("Usage: processor [FILE] [TARGET PAIR] [REPLACE PAIR]\n");
}

void
process_args(
    size_t argc,
    char** argv,
    char** filename,
    char** target,
    char** pair)
{
    if ((argc != 4)
        || (strlen(argv[2]) != 2)
        || (strlen(argv[3]) != 2)
    ) {
        printf("wrong args\n");
        print_help();

        exit(-1);
    }

    *filename = argv[1];
    *target = argv[2];
    *pair = argv[3];
}
