int doWork(char* str, int count)
{
    int n = 0;

    for (int i = 0; str[i] != '\0' && n < count; i++) {
        if (i > 1 && str[i - 1] == str[i]) {
            str[i] = ' ';
            n++;
            i++;
        }
    }

    return n;
}

