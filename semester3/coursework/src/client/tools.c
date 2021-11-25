#include "tools.h"


void
print_help(void)
{
    printf(
        "Usage: client [OPTION]... [FILE]...\n\n"
        "\t-t    target chars pair\n"
        "\t-p    chars pair to replace\n"
        "\t-f    file to process\n"
        "\t-h    print this message\n"
    );
}

size_t
process_args(
    size_t argc,
    char** argv,
    char** target,
    char** pair,
    char*** filenames)
{
    size_t files_count = 0;
    int opt = 0;
    bool target_catched = false;
    bool pair_catched = false;


    while ((opt = getopt(argc, argv, "t:p:f:h")) != -1) {
        switch (opt)
        {
            case 't':
                if (target_catched) {
                    printf("dublicate key '-t'\n");
                    print_help();

                    exit(-1);
                }

                *target = optarg;
                target_catched = true;
                break;
            case 'p':
                if (pair_catched) {
                    printf("dublicate key '-p'\n");
                    print_help();
                    
                    exit(-1);
                }

                *pair = optarg;
                pair_catched = true;
                break;
            case 'f':
                (*filenames)[files_count++] = optarg;
                break;
            case 'h':
                print_help();
                exit(0);
                break;
            default:
                break;
        }
    }

    if (!validate_args(*target, *pair)) {
        printf("wrong keys\n");
        print_help();

        exit(-1);
    }

    return files_count;
}

bool
validate_args(const char* target, const char* pair)
{ return ((strlen(target) == 2) && (strlen(pair) == 2)); }

void
send_data(int sockfd, char** filenames, size_t files_count)
{
    s_write(sockfd, &files_count, sizeof(files_count));

    for (size_t n = 0; n < files_count; n++) {
        size_t len = strlen(filenames[n]);

        printf("sending file '%s' to server...\n", filenames[n]);
        s_write(sockfd, &len, sizeof(len));
        s_write(sockfd, filenames[n], len);

        printf("[+] file sended\n");
    }
}

void
receive_data(int sockfd)
{
    size_t len = 0;
    char buf[MAX_ANSWER] = {0};

    printf("reading data from server...\n");
    s_read(sockfd, &len, sizeof(len));
    s_read(sockfd, buf, len);

    printf("[+] received: %s\n", buf);
}

void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
}
