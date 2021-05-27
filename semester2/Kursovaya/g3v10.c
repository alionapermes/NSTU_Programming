/* Курсовая работа по информатике. Вариант 10.
 * Структура: Фамилия, год рождения, оклад
 * Количество записей: 300
 * Номер поля для сортировки: 2
 * Выделение памяти: динамическое
 * Тип сортировки: по убыванию
 * Вывод: экран
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define AMOUNT 300
#define STR_LENGTH 40
#define FILE_PATH "local.db"

typedef struct {
    char* lastname;
    int year;
    int salary;
} Employee;

void input();
void print_one();
void sort_by_year();
void print_all();
void write_file();
void read_file();

Employee* db;
bool already_sorted;

int main() {
    setlocale(LC_ALL, "rus");

    db = calloc(AMOUNT, sizeof(Employee));
    already_sorted = false;

    int command = 0;
    do {
        printf("\n\t[Меню]\n");
        printf("<1> Ввод записи с произвольным номером\n");
        printf("<2> Вывод записи с заданным номером\n");
        printf("<3> Сортировка записей по году в порядке убывания\n");
        printf("<4> Вывод на экран всех записей в отсортированном виде\n");
        printf("<5> Сохранение всех записей в файле\n");
        printf("<6> Чтение записей из файла\n");
        printf("<0> Выход из программы\n");

        printf("\nНомер команды: ");
        scanf("%d", &command);

        if (command == 0)
            break;
        else if (command == 1)
            input();
        else if (command == 2)
            print_one();
        else if (command == 3)
            sort_by_year();
        else if (command == 4)
            print_all();
        else if (command == 5)
            write_file();
        else if (command == 6)
            read_file();
        else
            printf("Неверный номер комманды, попробуйте ещё раз\n");

        printf("################\n");
    } while (command != 0);

    return 0;
}

void input() {
    int number;

    printf("Введите номер: ");
    scanf("%d", &number);
    number--;

    db[number].lastname = calloc(STR_LENGTH, sizeof(char));

    printf("[Ввод данные сотрудника]\n");

    printf("\tФамилия: ");
    scanf("%s", db[number].lastname);

    printf("\tГод рождения: ");
    scanf("%d", &db[number].year);

    printf("\tОклад: ");
    scanf("%d", &db[number].salary);

    already_sorted = false;
}

void print_one() {
    int number;

    printf("Введите номер: ");
    scanf("%d", &number);
    number--;

    if (db[number].lastname != NULL) {
        printf("[Запись №%d]\n", number+1);
        printf("\tФамилия: %s\n", db[number].lastname);
        printf("\tГод рождения: %d\n", db[number].year);
        printf("\tОклад: %d\n", db[number].salary);
    } else {
        printf("Запись с номером %d не существует\n", number+1);
    }
}

void sort_by_year() {
    if (already_sorted) {
        printf("Данные уже отсортированны\n");
    } else {
        for (int loop = 0; loop < AMOUNT/2; loop++) {
            for (int number = 0; number < AMOUNT; number++) {
                if (db[number].lastname   == NULL ||
                   (db[number+1].lastname != NULL &&
                    db[number+1].year > db[number].year))
                {
                    Employee temp = db[number+1];
                    db[number+1]  = db[number];
                    db[number]    = temp;
                }
            }
        }

        printf("База данных отсортированна\n");
        already_sorted = true;
    }
}

void print_all() {
    if (!already_sorted) 
        sort_by_year();

    for (int number = 0; number < AMOUNT; number++) {
        if (db[number].lastname != NULL) {
            printf("[№%d] Фамилия: %s\t", number+1, db[number].lastname);
            printf("Год рождения: %d\t", db[number].year);
            printf("Оклад: %d\n", db[number].salary);
        }
    }
}

void write_file() {
    FILE* file = fopen(FILE_PATH, "w");

    if (file != NULL) {
        int notes = 0;
        for (int emp = 0; emp < AMOUNT; emp++) {
            if (db[emp].lastname != NULL)
                notes++;
        }
        fprintf(file, "[%d]\n", notes);

        for (int number = 0; number < AMOUNT; number++) {
            if (db[number].lastname != NULL) {
                fprintf(file, "%s %d %d\n",
                    db[number].lastname, db[number].year, db[number].salary);
            }
        }

        printf("Записи сохранены\n");
    } else {
        printf("Ошибка сохранения файла\n");
    }

    fclose(file);
}

void read_file() {
    FILE* file = fopen(FILE_PATH, "r");

    if (file != NULL) {
        for (int emp = 0; emp < AMOUNT; emp++) {
            if (db[emp].lastname != NULL)
                db[emp].lastname = NULL;
        }

        int notes = 0;
        fscanf(file, "[%d]\n", &notes);

        for (int number = 0; number < notes; number++) {
            db[number].lastname = calloc(STR_LENGTH, sizeof(char));

            fscanf(file, "%s %d %d\n",
                db[number].lastname, &db[number].year, &db[number].salary);
        }

        printf("Данные загружены из файла\n");
    } else {
        printf("Ошибка чтения файла\n");
    }

    fclose(file);
    already_sorted = false;
}
