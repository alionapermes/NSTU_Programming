#include "../../lib/scrsys/io.h"
#include "../../lib/scrsys/proc.h"
#include "../../lib/scrsys/network.h"
#include "tools.h"

#define PORT 5000


void
server_daemon(void);


int
main(int argc, char** argv)
{
    int pid = fork();

    if (pid == -1) {
        throw_error(errno);
        exit(-1);
    } else if (pid == 0) {
        umask(0);
        s_setsid();

        s_close(STDIN_FILENO);
        s_close(STDOUT_FILENO);
        s_close(STDERR_FILENO);

    
        server_daemon();
    }
}

void
server_daemon(void)
{
    write_log(PATH_ACTLOG, "[+] server started", 0);

    struct sockaddr_in addr;
    size_t files_count = 0;
    int listenfd = 0;
    int connfd = 0;
    char** files = NULL;
    char target[3] = {0};
    char pair[3] = {0};


    init_sockaddr_in(&addr, PORT);
    listenfd = s_socket(AF_INET, SOCK_STREAM, 0);
    write_log(PATH_ACTLOG, "[+] socket created", 0);


    s_bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    s_listen(listenfd, 10);
    write_log(PATH_ACTLOG, "[+] listening started", 0);


    while (true) {
        connfd = s_accept(listenfd, NULL, NULL);
        write_log(PATH_ACTLOG, "[+] connection accepted", 0);
        files_count = receive_data(connfd, &files, &target, &pair);

        for (size_t n = 0; n < files_count; n++) {
            char log_buf[LOGMSG_SIZE] = {0};
            char* msg = NULL;
            size_t len = 0;

            sprintf(log_buf, "processing '%s'...", files[n]);
            write_log(PATH_ACTLOG, log_buf, strlen(log_buf));

            msg = process_file(files[n], target, pair);
            len = strlen(msg);
            write_log(PATH_ACTLOG, "[+] processed successful", 0);

#ifdef DEBUG
            char log_msg[LOGMSG_SIZE] = {0};
            sprintf(log_msg, "SEND (%d) len: %lu; msg: %s", getpid(), len, msg);

            write_log(PATH_DEBUGLOG, log_msg, strlen(log_msg));
#endif

            s_write(connfd, &len, sizeof(len));
            s_write(connfd, msg, len);
            write_log(PATH_ACTLOG, "[+] result sended to client", 0);

            free(msg);
        }

        if (files_count > 0) {
            for (size_t n = 0; n < files_count; n++)
                free(files[n]);
            free(files);
        }

        close(connfd);
    }


    //s_close(connfd);
    write_log(PATH_ACTLOG, "[+] connection closed*", 0);

    return 0;
}
