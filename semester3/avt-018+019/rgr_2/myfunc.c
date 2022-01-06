int replace_last(char* str, char symbol)
{
    int replaces = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == '\n') && (i > 0) && (str[i - 1] != '\n')) {
            str[i - 1] = symbol;
            replaces++;
        }
    }

    return replaces;
}
