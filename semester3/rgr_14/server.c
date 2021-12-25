// Заменить все цифры на заданный символ

#include "headers.h"

int main(int argc, char** argv)
{
    writeLog(INFO, "=== SERVER STARTED ===");
    sockaddr_in6 svaddr, claddr;
    int sfd = 0;
    ssize_t bytes = 0;
    socklen_t len = sizeof(sockaddr_in6);
    char buf[BUF_SIZE] = {0};
    char claddr_str[INET6_ADDRSTRLEN] = {0};

    try((sfd = socket(AF_INET6, SOCK_DGRAM, 0)), -1);
    memset(&svaddr, 0, sizeof(sockaddr_in6));

    svaddr.sin6_family = AF_INET6;
    svaddr.sin6_addr = in6addr_any;
    svaddr.sin6_port = htons(PORT);

    try(bind(sfd, (sockaddr*)&svaddr, sizeof(sockaddr_in6)), -1);

    while (true) {
        pid_t pid;
        int status, resp;
        char c[2] = {0};
        char s[80] = {0};

        try(recvfrom(sfd, c, 2, 0, (sockaddr*)&claddr, &len), -1);
        snprintf(s, 79, "Replacesment char received [%c]", *c);
        writeLog(INFO, s);
#ifdef DEBUG
        printf("char: %s\n", c);
#endif
        try((bytes = recvfrom(sfd, buf, BUF_SIZE, 0, (sockaddr*)&claddr, &len)), -1);
        memset(s, 0, 80);
        snprintf(s, 79, "File name received [%s]", buf);
        writeLog(INFO, s);
#ifdef DEBUG
        printf("buf: %s\n", buf);
#endif

        if (inet_ntop(AF_INET6, &claddr.sin6_addr, claddr_str, INET6_ADDRSTRLEN) == NULL) {
            writeLog(ERROR, "Couldn't convert client address to string");
        } else {
            char m[80] = {0};
            snprintf(m, 79, "Server received %ld bytes from (%s, %u)\n", bytes, claddr_str, ntohs(claddr.sin6_port));
            writeLog(INFO, m);
        }

// MAGIC        
        try((pid = fork()), -1);

        if (pid == 0) {
            execl("./child", "child", buf, c, NULL);
        } else {
            pid_t child;
            try((child = wait(&status)), -1);

            resp = WEXITSTATUS(status);
            try(sendto(sfd, &resp, sizeof(resp), 0, (sockaddr*)&claddr, len), -1);
        }
// #####
    }

    return 0;
}
