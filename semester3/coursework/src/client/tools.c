#include "tools.h"


void
process_args(size_t argc, char** argv, char** target, char** pair)
{
    int opt = 0;
    
    while ((opt = getopt(argc, argv, "t:p:")) != -1) {
        switch (opt)
        {
            case 't':
                *target = optarg;
                break;
            case 'p':
                *pair = optarg;
                break;
            default:
                printf("unknown: %s\n", optarg);
                break;
        }
    }
}
