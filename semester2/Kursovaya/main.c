#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

#define NOTES 200

void add_with_user_input(int number);
void print_by_number(int number);
void sort_by_weigth();
void print_sorted();
void save_to_file(char* path);
void load_from_file(char* path);

int   ask_number();
char* ask_filepath();

struct Detail {
    char* name;
    int   amount;
    int   weight;
};

static bool   sorted;
static struct Detail** box;

int main() {
    setlocale(LC_ALL, "ru");
    
    sorted = false;
    box = calloc(NOTES, sizeof(struct Detail*));
    for (int i = 0; i < NOTES; i++) {
        box[i] = malloc(sizeof(struct Detail));
    }

    char input = 0;
    do {
        printf("\n[1] Ввод записи с произвольным номером");
        printf("\n[2] Вывод записи с заданным номером");
        printf("\n[3] Сортировка по убыванию по полю weight");
        printf("\n[4] Вывод записей в отсортированном порядке");
        printf("\n[5] Сохранкне всех записей в файле");
        printf("\n[6] Чтение записей файла");
        
        scanf("\n\nВыполнить функцию №%c", &input);
        
        switch (input) {
        case '1':
            add_with_user_input(ask_number());
            break;
        case '2':
            print_by_number(ask_number());
            break;
        case '3':
            sort_by_weigth();
            break;
        case '4':
            print_sorted();
        case '5':
            save_to_file(ask_filepath());
            break;
        case '6':
            load_from_file(ask_filepath());
            break;
        default:
            printf("Введите корректный номер функции\n");
            break;
        }
    } while (input >= '1' && input <= '6');
    
    return 0;
}

void add_with_user_input(int number) {
    box[number - 1]->name = calloc(20, sizeof(char));
    
    printf("\n[Параметры детали]\n");
    scanf("\tНазвание: %s",    box[number - 1]->name);
    scnaf("\tКоличество: %d", &box[number - 1]->amount);
    scanf("\tВес: %d",        &box[number - 1]->weight);
}

void print_by_number(int number) {
    printf("\n[Деталь №%d]\n",   number);
    printf("\tНазвание: %s\n",   box[number - 1]->name);
    printf("\tКоличество: %d\n", box[number - 1]->amount);
    printf("\tВес: %d\n",        box[number - 1]->weight);
}

void sort_by_weight() {
    if (!sorted) {
        int start_from = 0;
        int index_max;
        int max_weight;
        
        while (start_from < NOTES) {
            index_max  = -1;
            max_weight = -1;
            
            for (int i = start_from; i < NOTES; i++) {
                if (box[i]->weight > max_weight) {
                    max_weight = box[i]->weight;
                    index_max  = i;
                }
            }
            
            struct Detail* temp = box[start_from];
            box[start_from]     = box[index_max];
            box[index_max]      = temp;
            
            start_from++;
            free(temp);
        }
        
        sorted = true;
    }
    else {
        printf("\n>> База данных уже отсортированна\n");
    }
}

void print_sorted() {
    if (!sorted) {
        sort_by_weight();
    }
    
    for (int i = 0; i < NOTES; i++) {
        printf("\n[Деталь №%d]\n",   i + 1);
        printf("\tНазвание: %s\n",   box[i]->name);
        printf("\tКоличество: %d\n", box[i]->amount);
        printf("\tВес: %d\n",        box[i]->weight);
    }
}

void save_to_file(char* path) {
    FILE* db = fopen(path, "w");
    
    for (int i = 0; i < NOTES; i++) {
        fprintf(db, "{n=%s;a=%d;w=%d;}\n", box[i]->name, box[i]->amount, box[i]->weight);
    }
    
    fclose(db);
}

void load_from_file(char* path) {
    FILE* db   = fopen(path, "r");
    char* data = calloc(40 * 200, sizeof(char));
    
    struct Detail* detail;
    
    bool read_value  = false;
    bool read_name   = false;
    bool read_amount = false;
    bool read_weight = false;
    
    int rev = 0;
    int num = 0;
    int ltr = 0;
    double rank = 0;
    
    fscanf(db, "%s", data);
    fclose(db);
    
    for (int i = 0; data[i] != '\0'; i++) {
        switch (data[i]) {
        case '{':
            detail = malloc(sizeof(struct Detail));
            break;
        case '}':
            free(box[num]);
            box[num] = detail;
            num++;
            break;
        case '=':
            read_value = true;
            break;
        case ';':
            read_value = false;
            
            int value = 0;
            while (rev > 0) {
                value += (rev % 10) * pow(10, rank);
                rank--;
                rev /= 10;
            }
            
            if (read_amount) {
                detail->amount = value;
            } else if (read_weight) {
                detail->weight = value;
            }
            break;
        case 'n':
            if (!read_value) {
                ltr = 0;
                detail->name = calloc(20, sizeof(char));
                read_weight  = false;
                read_name    = true;
            }
            break;
        case 'a':
            if (!read_value) {
                rev         = 0;
                read_name   = false;
                read_amount = true;
            }
            break;
        case 'w':
            if (!read_value) {
                rev = 0;
                read_amount = false;
                read_weight = true;
            }
            break;
        default:
            if (!read_value) {
                continue;
            }
            break;
        }
        
        if (read_value) {
            if (read_name && data[i] != '=') {
                detail->name[ltr] = data[i];
            } else if (data[i] >= '0' && data[i] <= '9'){
                rev += (data[i] - '0') * pow(10, rank);
                rank++;
            }
        }
    }
    
    free(data);
}

int ask_number() {
    int value;
    scanf("\nВведите номер детали: %d", &value);
    return value;
}

char* ask_filepath() {
    char* path = calloc(200, sizeof(char));
    scanf("\nВведите путь файла: %s", path);
    return path;
}
