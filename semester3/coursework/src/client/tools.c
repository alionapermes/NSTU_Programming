#include "tools.h"


void
process_args(size_t argc, char** argv, char** target, char** pair)
{
    int opt = 0;
    
    while ((opt = getopt(argc, argv, "t:p:h")) != -1) {
        switch (opt)
        {
            case 't':
                *target = optarg;
                break;
            case 'p':
                *pair = optarg;
                break;
            case 'h':
                print_help();
                exit(0);
                break;
            default:
                printf("unknown: %s\n", optarg);
                break;
        }
    }

    if (!validate_args(*target, *pair)) {
        printf("wrong key\n");
        exit(-1);
    }
}

bool
validate_args(const char* target, const char* pair)
{ return ((strlen(target) == 2) && (strlen(pair) == 2)); }

void
print_help(void)
{
    printf(
        "Usage: client [OPTION]... [FILE]...\n\n"
        "\t-t    target chars pair"
        "\t-p    chars pair to replace"
        "\t-h    print this message"
    );
}
