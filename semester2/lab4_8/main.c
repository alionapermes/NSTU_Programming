#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void inp_str(char* str, int maxlen) {
    int len;
    char start = TRUE;

    len = strlen(str);
    do {
        if (!start) {
            printf("Text length must be less than %d\n", maxlen + 1);
        }
        start = FALSE;
        printf("Enter your text: ");
        gets(str);
    } while (len > maxlen);
}

void out_str(char* str, int amount_of_numbers, int number) {
    printf("String number - %d, %s, amount of numbers = %d", number, str, amount_of_numbers);
}

void sort(char* str) {
    int sizes[32];
    int numbers = 0;
    int index = 0;
    int words_count = 0;
    for (int i = 0; i < 32; i++) {
        sizes[i] = 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            sizes[numbers] = index;
            words_count++;
            numbers = 0;
        } else if (str[i] >= '0' && str[i] <= '9') {
            numbers++;
        }
    }

    int letter;
    char word[32];
    for (int i = 31; i >= 0; i--) {
        if (sizes[i] > 0) {
            numbers = 0;
            for (letter = sizes[i]; str[letter] != ' '; letter++) {
                if (str[letter] >= '0' && str[letter] <= '9') {
                    numbers++;
                }
                word[letter - sizes[i]] = sizes[letter];
            }
            word[letter - sizes[i] + 1] = '\0';
            out_str(word, numbers, words_count++);
        }
    }
}

int main() {
    char string[128];
    inp_str(string, 127);
    sort(string);

    return 0;
}
