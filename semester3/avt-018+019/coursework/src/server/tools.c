#include "tools.h"


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
}

size_t
receive_data(int sockfd, char*** filenames, char target[3], char pair[3])
{
    size_t files_count = 0;

    s_read(sockfd, &files_count, sizeof(files_count));
    
    if (files_count == 0)
        return files_count;

    s_read(sockfd, target, 2);
    s_read(sockfd, pair, 2);


#ifdef DEBUG
    char log_msg[LOGMSG_SIZE] = {0};
    sprintf(
        log_msg,
        "count: %lu; target: %s; pair: %s",
        files_count, target, pair
    );

    write_log(PATH_DEBUGLOG, log_msg, strlen(log_msg));
#endif

    *filenames = calloc(sizeof(char*), files_count);

    for (size_t n = 0; n < files_count; n++) {
        size_t len = 0;
        char log_msg[LOGMSG_SIZE] = {0};

        (*filenames)[n] = calloc(sizeof(char), MAX_NAME);

        write_log(PATH_ACTLOG, "reading from client...", 0);
        s_read(sockfd, &len, sizeof(len));

        if (len > MAX_NAME) {
            write_log(PATH_ERRORLOG, "filename is too long", 0);
            
            while (n >= 0)
                free((*filenames)[n--]);

            exit(-1);
        }

        s_read(sockfd, (*filenames)[n], len);

        sprintf(log_msg, "[+] received: %s", (*filenames)[n]);
        write_log(PATH_ACTLOG, log_msg, 0);

#ifdef DEBUG
        memset(log_msg, 0, LOGMSG_SIZE);
        sprintf(
            log_msg,
            "RECEIVE len: %lu; filename: %s",
            len, (*filenames)[n]
        );

        write_log(PATH_DEBUGLOG, log_msg, strlen(log_msg));
#endif
    }

    return files_count;
}

char*
process_file(char* filename, char* target, char* pair)
{
    pid_t pid;
    int status;
    char* result_msg = calloc(sizeof(char), MAX_RESULT);


    if ((pid = fork()) < 0) {
        write_log(PATH_ERRORLOG, "bad fork", 0);
        free(result_msg);
        exit(-1);
    }

    if (pid == 0) {
        execl(PROCESSOR_PATH, PROCESSOR_NAME, filename, target, pair, NULL);
        throw_error(errno);
    } else {
        pid_t child = wait(&status);

        if (child > 0) {
            status_msg(status, result_msg);
        } else if (child == -1) {
            throw_error(errno);
        }
    }

    return result_msg;
}

void
status_msg(int status, char* buf)
{
    int length  = 0;


    if (WIFEXITED(status))
        length = sprintf(buf, "replaces: %d", WEXITSTATUS(status));

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
}
