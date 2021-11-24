#include "error.h"


void
throw_error(int err)
{
    char* msg = strerror(err);

    write_log(PATH_ERRORLOG, msg, strlen(msg));
    printf("error %d: %s\n", err, msg);

    exit(-1);
}
