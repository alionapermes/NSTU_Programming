#include <stdio.h>

/*
int main() {
    char str[50];
    char new_str[50];

    printf("Type text string: ");
    gets(str);
    printf("Old string: %s\n", str);

    for (int i = 0; i < 50; i++) {
        new_str[i] = str[i];
    }

    for (int i = 0; str[i] != '\0'; i++) {
        new_str[i] = (str[i] >= 'A' && str[i] <= 'M') ? (str[i] + 32) : str[i];
        new_str[i] = (str[i] == 'a' || str[i] == 'r' || str[i] == 'h' || str[i] == 'w') ? (str[i] - 32) : new_str[i];
    }
    printf("New string: %s\n", new_str);

    return 0;
}
*/


/*
int main() {
    char str[50];
    char new_str[50];

    printf("Type text string: ");
    gets(str);
    printf("Old string: %s\n", str);

    for (int i = 0; i < 50; i++) {
        new_str[i] = str[i];
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'M') {
            new_str[i] = str[i] + 32;
        } else if (str[i] == 'a' || str[i] == 'r' || str[i] == 'h' || str[i] == 'w') {
            new_str[i] = str[i] - 32;
        }
    }
    printf("New string: %s\n", new_str);

    return 0;
}
*/


/*
int main() {
    char str[50];
    char new_str[50];

    printf("Type text string: ");
    gets(str);
    printf("Old string: %s\n", str);

    for (int i = 0; i < 50; i++) {
        new_str[i] = str[i];
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'M') {
            new_str[i] = str[i] + 32;
        } else {
            switch (str[i]) {
                case 'a':
                    new_str[i] = 'A';
                    break;
                case 'r':
                    new_str[i] = 'R';
                    break;
                case 'h':
                    new_str[i] = 'H';
                    break;
                case 'w':
                    new_str[i] = 'W';
                    break;
            }
        }
    }
    printf("New string: %s\n", new_str);

    return 0;
}
*/
