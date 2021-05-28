/* Курсовая работа по информатике. Вариант 4-11.
 * Структура: Название фирмы, количество работников, уставной капитал
 * Количество записей: 200
 * Номер поля для сортировки: 3
 * Выделение памяти: статическое
 * Тип сортировки: по убыванию
 * Вывод: экран
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define FIRMS 200
#define SIZE 30
#define FIRMSDB "FirmsDb.txt"

void input_info();
void output_one_company();
void sort_by_stock();
void output_full_db();
void save_data();
void load_data();

struct Firm {
    char name[SIZE];
    int staff;
    int stock;
};

struct Firm firms[FIRMS];
bool need_sort;

int main() {
    setlocale(LC_ALL, "ru");

    need_sort = true;
    for (int firm_num = 0; firm_num < FIRMS; firm_num++)
        firms[firm_num].stock = -1;

    int func_num = 0;
    do {
        printf("\nБаза данных фирм\n");
        printf("1) Ввод записи с произвольным номером\n");
        printf("2) Вывод записи с заданным номером\n");
        printf("3) Сортировка записей по уставному капиталу в порядке возрастания\n");
        printf("4) Вывод на экран всех записей в отсортированном виде\n");
        printf("5) Сохранение всех записей в файле\n");
        printf("6) Чтение записей из файла\n");
        printf("0) Выход из программы\n");

        printf("\nНомер команды: ");
        scanf("%d", &func_num);

        switch (func_num) {
            case 1:
                input_info();
                break;
            case 2:
                output_one_company();
                break;
            case 3:
                sort_by_stock();
                break;
            case 4:
                output_full_db();
                break;
            case 5:
                save_data();
                break;
            case 6:
                load_data();
                break;
            case 0:
                printf("Завершение программы\n");
                break;
            default:
                printf("Команды под номером %d не существует\n", func_num);
                break;
        }

        printf("\n");
    } while (func_num != 0);

    return 0;
}

void input_info() {
    int note;

    printf("Номер фирмы: ");
    scanf("%d", &note);
    note--;

    printf("## Ввод записи о фирме №%d ##\n", note);

    printf("Название фирмы: ");
    scanf("%s", firms[note].name);

    printf("Количество работников: ");
    scanf("%d", &firms[note].staff);

    printf("Уставной капитал: ");
    scanf("%d", &firms[note].stock);

    need_sort = true;
}

void output_one_company() {
    int firm;

    printf("Номер записи: ");
    scanf("%d", &firm);
    firm--;

    if (firms[firm].stock > 0) {
        printf("\nИнформация о фирме №%d\n", firm+1);
        printf(" Название фирмы: %s\n",        firms[firm].name);
        printf(" Количество работников: %d\n", firms[firm].staff);
        printf(" Уставной капитал: %d\n",      firms[firm].stock);
    } else {
        printf("О компании №%d нет информации\n", firm+1);
    }
}

void sort_by_stock() {
    if (!need_sort) {
        printf("Сортировка уже проведена\n");
    } else {
        for (int i = 0; i < FIRMS/2; i++) {
            for (int firm = 0; firm   < FIRMS-1; firm++) {
                if (firms[firm].stock < firms[firm+1].stock) {
                    struct Firm temp  = firms[firm];
                    firms[firm]       = firms[firm+1];
                    firms[firm+1]     = temp;
                }
            }
        }

        printf("База данных отсортированна\n");
        need_sort = false;
    }
}

void output_full_db() {
    if (need_sort)
        sort_by_stock();

    for (int firm = 0; firm < FIRMS; firm++) {
        if (firms[firm].stock > 0) {
        printf("\nИнформация о фирме №%d\n", firm+1);
        printf(" Название фирмы: %s\n",        firms[firm].name);
        printf(" Количество работников: %d\n", firms[firm].staff);
        printf(" Уставной капитал: %d\n",      firms[firm].stock);
        }
    }
}

void save_data() {
    FILE* firms_db = fopen(FIRMSDB, "w");

    if (firms_db != NULL) {
        int saved = 0;
        for (int note = 0; note < FIRMS; note++) {
            if (firms[note].stock > 0)
                saved++;
        }
        fprintf(firms_db, "#%d\n", saved);

        for (int num = 0; num < FIRMS; num++) {
            if (firms[num].stock > 0) {
                fprintf(firms_db, "%s %d %d\n",
                    firms[num].name, firms[num].staff, firms[num].stock);
            }
        }

        printf("Информация о фирмах сохранена\n");
    } else {
        printf("Ошибка\n");
    }

    fclose(firms_db);
}

void load_data() {
    FILE* firms_db = fopen(FIRMSDB, "r");

    if (firms_db != NULL) {
        for (int note = 0; note < FIRMS; note++) {
            firms[note].stock = -1;
        }

        int saved = 0;
        fscanf(firms_db, "#%d\n", &saved);

        for (int num = 0; num < saved; num++) {
            fscanf(firms_db, "%s %d %d\n",
                firms[num].name, &firms[num].staff, &firms[num].stock);
        }

        printf("Информация о фирмах загружена\n");
    } else {
        printf("Ошибка\n");
    }

    fclose(firms_db);
    need_sort = true;
}
