#include "headers.h"

int main(int argc, char** argv)
{
    sockaddr_in6 svaddr;
    int sfd, resp = 0;
    size_t msglen = 0;
    ssize_t bytes = 0;

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s <char> <filename[, ...]>\n", argv[0]);
        return 0;
    }

    if (strlen(argv[1]) != 1) {
        printf("first arg must be a char\n");
        return -1;
    }

    try((sfd = socket(AF_INET6, SOCK_DGRAM, 0)), -1);

    memset(&svaddr, 0, sizeof(sockaddr_in6));
    svaddr.sin6_family = AF_INET6;
    svaddr.sin6_port = htons(PORT);

    try(inet_pton(AF_INET, "::1", &svaddr.sin6_addr), -1);

    for (int n = 2; n < argc; n++) {
        msglen = strlen(argv[n]);
        try(sendto(sfd, argv[1], 2, 0, (sockaddr*)&svaddr, sizeof(sockaddr_in6)), -1);
        try(sendto(sfd, argv[n], msglen, 0, (sockaddr*)&svaddr, sizeof(sockaddr_in6)), -1);

        try((bytes = recvfrom(sfd, &resp, sizeof(resp), 0, NULL, NULL)), -1);
        printf("response: %d\n", resp);
    }

    return 0;
}
