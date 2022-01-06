int func(char c, char* buf) {
    int x = 0;

    for (int n = 0; buf[n] != '\0'; n++) {
        if (buf[n] >= '0' && buf[n] <= '9') {
            buf[n] = c;
            x++;
        }
    }

    return x;
}
