#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char** argv) {
    /// reading arguments
    int counter = 0;
    while (argv[1][counter++] != '\0') {}
    char* arg_file = malloc(counter * sizeof(char));

    counter = 0;
    while (argv[2][counter++] != '\0') {}
    char* arg_length = malloc(counter * sizeof(char));

    int index = 0;
    do {
        arg_file[index] = argv[1][index];
    } while (argv[1][index++] != '\0');

    index = 0;
    do {
        arg_length[index] = argv[2][index];
    } while (argv[2][index++] != '\0');
    /// arguments read

    char end[5] = ".out\0";
    int  last = 0; // index of the last file's symbol
    int  num = 0;  // max string length
    int  nums = 0; // counter of digits

    // counting arg_'s length
    while (arg_file[last] != '\0') {
        last++;
    }
    while (arg_length[nums] != '\0') {
        nums++;
    }
    // computing max string length
    for (int i = nums - 1; i >= 0; i--) {
        num += (arg_length[nums - 1 - i] - '0') * pow(10, i);
    }

    char* str = malloc(sizeof(char) * (num  + 1)); // pointer for reading string
    char* file_inp = malloc(sizeof(char) * last); // input file
    char* file_out = malloc(last + sizeof(end) / sizeof(char)); // output file

    /// prepearing file names
    int ltr;
    for (ltr = 0; ltr != last; ltr++) {
        file_inp[ltr] = arg_file[ltr];
    }

    for (int i = 0; file_inp[i] != '\0'; i++) {
        file_out[i] = file_inp[i];
    }
    for (int i = 0; end[i] != '\0'; i++) {
        file_out[ltr] = end[i];
        ltr++;
    }
    /// prepearing was finished

    FILE* file = fopen(file_inp, "r");
    FILE* out  = fopen(file_out, "w");

    // file processing
    while (!feof(file)) { // check if end of file
        if (fgets(str, num + 1, file)) { // reading string into str
            int ltr = -1; // index the last symbol of string
            while (str[ltr + 1] != '\0' && str[ltr + 1] != '\n') {
                ltr++;
            }

            if (str[ltr] >= '0' && str[ltr] <= '9') {
                fprintf(out, "%s", str); // writing string into output file
            }
        }
    }

    fclose(file);
    fclose(out);

    free(str);
    free(file_inp);
    free(file_out);
    free(arg_file);
    free(arg_length);

    return 0;
}


/*
int main(int argc, char** argv) {
    /// reading arguments
    int temp = 0;
    while (argv[1][temp++] != '\0') {}
    char* arg_file = malloc(temp * sizeof(char));

    char target = argv[2][0];

    temp = 0;
    do {
        arg_file[temp] = argv[1][temp];
    } while (argv[1][temp++] != '\0');
    /// arguments read

    char end[5] = ".out\0";
    int  length = 0; // index of the last file's symbol

    // counting arg_'s length
    while (arg_file[length] != '\0') {
        length++;
    }

    char* file_inp = malloc(sizeof(char) * length); // input file
    char* file_out = malloc(length + sizeof(end) / sizeof(char)); // output file

    /// prepearing file names
    int ltr;
    for (ltr = 0; ltr != length; ltr++) {
        file_inp[ltr] = arg_file[ltr];
    }

    for (int i = 0; file_inp[i] != '\0'; i++) {
        file_out[i] = file_inp[i];
    }
    for (int i = 0; end[i] != '\0'; i++) {
        file_out[ltr] = end[i];
        ltr++;
    }
    /// prepearing was finished

    FILE* file = fopen(file_inp, "r");
    FILE* out  = fopen(file_out, "w");

    // file processing
    while (!feof(file)) { // check if end of file
        char current = fgetc(file);
        fprintf(out, "%c", (current == target ? ' ' : current)); // writing string into output file
    }

    fclose(file);
    fclose(out);

    free(file_inp);
    free(file_out);
    free(arg_file);

    return 0;
}
*/
