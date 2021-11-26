#include "tools.h"


char*
status_msg(int status, char* buf)
{
    int length  = 0;


    if (WIFEXITED(status))
        length = sprintf(buf, "return status: %d", WEXITSTATUS(status));

    if (WIFSIGNALED(status)) {
        length = sprintf(
            buf,
            "killed by signal: %d%s",
            WTERMSIG(status),
            (WCOREDUMP(status) ? " (dumped core)" : "")
        );
    }

    if (WIFSTOPPED(status))
        length = sprintf(buf, "stopped by signal: %d", WSTOPSIG(status));

    if (WIFCONTINUED(status))
        length = sprintf(buf, "continued");


    if (length <= 0)
        throw_error(errno);

    buf = realloc(buf, (size_t)length);
    return buf;
}

