#include "tools.h"


void
print_help(void)
{
    printf("Usage: processor [FILE] [CHARS PAIR]\n");
}

void
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

void
process_args(size_t argc, char** argv, char** filename, char** pair)
{
    if ((argc != 3) || (strlen(argv[2]) != 2)) {
        printf("wrong args\n");
        print_help();

        exit(-1);
    }

    *filename = argv[1];
    *pair = argv[2];
}
