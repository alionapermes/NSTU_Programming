#include "proc.h"


pid_t
s_setsid(void)
{
    pid_t result = setsid();

    if (result == -1)
        throw_error(errno);

    return result;
}
