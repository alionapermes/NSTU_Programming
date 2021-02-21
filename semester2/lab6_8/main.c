#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
    printf("File name: %s\n", argv[1]);
    printf("Max string length: %s\n", argv[2]);
    return 0;

    char end[4] = ".out";
    int  last = 0;
    int  num = 0;

    while (argv[1][last] != '\0') {
        last++;
    }
    for (int i = last; i >= 0; i++) {
        num += (argv[2][i] - '0') * pow(10, i);
    }

    char* str = malloc(sizeof(char) * num);
    char* file_inp = malloc(sizeof(argv[1]));
    char* file_out = malloc(sizeof(argv[1]) + sizeof(end) / sizeof(char));

    int ltr;
    for (ltr = 0; ltr != last; ltr++) {
        file_inp[ltr] = argv[1][ltr];
    }

    for (int i = 0; end[i] != '\0'; i++) {
        ltr++;
        file_out[ltr] = end[i];
    }

    FILE* file = fopen(file_inp, "r");
    FILE* out  = fopen(file_out, "w");

    while (fgets(str, sizeof(str) / sizeof(char), file) != NULL)
    {
        int ltr = 0;
        while (str[ltr] != '\0') {
            ltr++;
        }

        if (str[ltr] > '0' && str[ltr] < '9') {
            fprintf(out, "%s", str);
        }
    }

    fclose(file);
    fclose(out);

    free(str);
    free(file_inp);
    free(file_out);
    free(file);
    free(out);

    return 0;
}
