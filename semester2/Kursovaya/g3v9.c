/* Курсовая работа по информатике. Вариант 9.
 * Структура: Название фирмы, количество работников, уставной капитал
 * Количество записей: 200
 * Номер поля для сортировки: 3
 * Выделение памяти: статическое
 * Тип сортировки: по возрастанию
 * Вывод: экран
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define NOTES 200
#define NAME_LENGTH 30
#define DATABASE_PATH "database.txt"

typedef struct {
    char name[NAME_LENGTH];
    int workers;
    int capital;
} Firm;

void add_note();
void print_firm();
void sort_by_capital();
void print_database();
void write_database();
void read_database();

Firm firms[NOTES];
bool is_database_sorted;

int main() {
    setlocale(LC_ALL, "RU");

    is_database_sorted = false;
    for (int note = 0; note < NOTES; note++)
        firms[note].capital = -1;

    int cmd_num = 0;
    do {
        printf("\nБаза данных фирм\n");
        printf("1. Ввод записи с произвольным номером\n");
        printf("2. Вывод записи с заданным номером\n");
        printf("3. Сортировка записей по уставному капиталу в порядке возрастания\n");
        printf("4. Вывод на экран всех записей в отсортированном виде\n");
        printf("5. Сохранение всех записей в файле\n");
        printf("6. Чтение записей из файла\n");
        printf("0. Выход из программы\n");

        printf("\nНомер команды: ");
        scanf("%d", &cmd_num);

        if (cmd_num == 0) {
            break;
        } else if (cmd_num == 1) {
            add_note();
        } else if (cmd_num == 2) {
            print_firm();
        } else if (cmd_num == 3) {
            sort_by_capital();
        } else if (cmd_num == 4) {
            print_database();
        } else if (cmd_num == 5) {
            write_database();
        } else if (cmd_num == 6) {
            read_database();
        } else {
            printf("Неверная команда\n");
        }

        printf("\n");
    } while (cmd_num != 0);

    return 0;
}

void add_note() {
    int num;

    printf("Номер записи: ");
    scanf("%d", &num);
    num--;

    printf("> Ввод новой записи\n");

    printf("  Название фирмы: ");
    scanf("%s", firms[num].name);

    printf("  Количество работников: ");
    scanf("%d", &firms[num].workers);

    printf("  Уставной капитал: ");
    scanf("%d", &firms[num].capital);

    is_database_sorted = false;
}

void print_firm() {
    int num;

    printf("Номер записи: ");
    scanf("%d", &num);
    num--;

    if (firms[num].capital > 0) {
        printf("> Запись №%d\n", num+1);
        printf("\tНазвание фирмы: %s\n", firms[num].name);
        printf("\tКоличество работников: %d\n", firms[num].workers);
        printf("\tУставной капитал: %d\n", firms[num].capital);
    } else {
        printf("Нет записей по номеру %d\n", num+1);
    }
}

void sort_by_capital() {
    if (is_database_sorted) {
        printf("Записи не нуждаются в сортировке\n");
    } else {
        for (int sort_num = 0; sort_num < NOTES/2; sort_num++) {
            for (int num = NOTES-1; num > 0; num--) {
                if (firms[num-1].capital < 0 ||
                   (firms[num].capital   > 0 &&
                    firms[num].capital   < firms[num-1].capital))
                {
                    Firm temp = firms[num-1];
                    firms[num-1] = firms[num];
                    firms[num] = temp;
                }
            }
        }

        printf("Записи отсортированны\n");
        is_database_sorted = true;
    }
}

void print_database() {
    if (!is_database_sorted) 
        sort_by_capital();

    for (int num = 0; num < NOTES; num++) {
        if (firms[num].capital > 0) {
            printf("> Запись №%d", num+1);
            printf("  Название фирмы: %s\n", firms[num].name);
            printf("  Количество работников: %d\n", firms[num].workers);
            printf("  Уставной капитал: %d\n", firms[num].capital);
        }
    }
}

void write_database() {
    FILE* database = fopen(DATABASE_PATH, "w");

    if (database != NULL) {
        int added_firms = 0;
        for (int note = 0; note < NOTES; note++) {
            if (firms[note].capital > 0)
                added_firms++;
        }
        fprintf(database, "#%d\n", added_firms);

        for (int num = 0; num < NOTES; num++) {
            if (firms[num].capital > 0) {
                fprintf(database, "%s %d %d\n",
                    firms[num].name, firms[num].workers, firms[num].capital);
            }
        }

        printf("Записи о фирмах сохранены\n");
    } else {
        printf("Ошибка\n");
    }

    fclose(database);
}

void read_database() {
    FILE* database = fopen(DATABASE_PATH, "r");

    if (database != NULL) {
        for (int note = 0; note < NOTES; note++) {
            firms[note].capital = -1;
        }

        int added_firms = 0;
        fscanf(database, "#%d\n", &added_firms);

        for (int num = 0; num < added_firms; num++) {
            fscanf(database, "%s %d %d\n",
                firms[num].name, &firms[num].workers, &firms[num].capital);
        }

        printf("Записи загружены\n");
    } else {
        printf("Ошибка\n");
    }

    fclose(database);
    is_database_sorted = false;
}
