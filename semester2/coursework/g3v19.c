/* Курсовая работа по информатике. Вариант 3-19.
 * Структура: Название пункта, расстояние, количество рейсов
 * Количество записей: 100
 * Номер поля для сортировки: 1
 * Выделение памяти: динамическое
 * Тип сортировки: по возрастанию
 * Вывод: экран
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define ROUTES 100
#define POINT_SIZE 30
#define ROUTES_FILE "routes_file.txt"

typedef struct {
    char* point_name;
    int   distance;
    int   amount;
} Route;

void append();
void get_by_num();
void sort_by_point_name();
void get_full_db();
void save_routes();
void read_routes();

int str_comp(const char* str1, const char* str2, int offset);

Route* db;

int main() {
    setlocale(LC_ALL, "rus");

    db = calloc(ROUTES, sizeof(Route));

    int cmd = 0;
    while (1) {
        printf("\nСписок команд\n");
        printf("Команда 1:\n");
        printf("\tВвод записи с произвольным номером\n");
        printf("Команда 2:\n");
        printf("\tВывод записи с заданным номером\n");
        printf("Команда 3:\n");
        printf("\tСортировка записей по названию пункта в порядке возрастания\n");
        printf("Команда 4:\n");
        printf("\tВывод на экран всех записей в отсортированном виде\n");
        printf("Команда 5:\n");
        printf("\tСохранение всех записей в файле\n");
        printf("Команда 6:\n");
        printf("\tЧтение записей из файла\n");
        printf("Команда 0:\n");
        printf("\tВыход из программы\n");

        printf("\nНомер команды: ");
        scanf("%d", &cmd);

        switch (cmd) {
            case 0:
                return 0;
                break;
            case 1:
                append();
                break;
            case 2:
                get_by_num();
                break;
            case 3:
                sort_by_point_name();
                break;
            case 4:
                get_full_db();
                break;
            case 5:
                save_routes();
                break;
            case 6:
                read_routes();
                break;
            default:
                printf("Ошибка\n");
                break;
        }
        printf("\n");
    }

    return 0;
}

void append() {
    int num;

    printf("Номер для добавления: ");
    scanf("%d", &num);
    num--;

    db[num].point_name = calloc(POINT_SIZE, sizeof(char));

    printf("\n");

    printf("\tНазвание пункта:\n> ");
    scanf("%s", db[num].point_name);

    printf("\tРасстояние:\n> ");
    scanf("%d", &db[num].distance);

    printf("\tКоличество рейсов:\n> ");
    scanf("%d", &db[num].amount);
}

void get_by_num() {
    int num;

    printf("Номер для печати: ");
    scanf("%d", &num);
    num--;

    if (db[num].point_name != NULL) {
        printf("Данные маршрута %d\n", num+1);
        printf("\tФамилия:\n> %s\n", db[num].point_name);
        printf("\tРасстояние:\n> %d\n", db[num].distance);
        printf("\tКоличество рейсов:\n> %d\n", db[num].amount);
    } else {
        printf("Маршрут %d не записан\n", num+1);
    }
}

void sort_by_point_name() {
    for (int first = 0; first < ROUTES; first++) {
        for (int num = 0; num < ROUTES-1; num++) {
            if  (db[num].point_name   == NULL ||
                (db[num+1].point_name != NULL &&
                 str_comp(db[num].point_name, db[num+1].point_name, 0) > 0))
            {
                Route temp = db[num+1];
                db[num+1]  = db[num];
                db[num]    = temp;
            }
        }
    }
    printf("База данных отсортированна\n");
}

void get_full_db() {
    sort_by_point_name();

    for (int num = 0; num < ROUTES; num++) {
        if (db[num].point_name != NULL) {
            printf("\nДанные маршрута %d\n", num+1);
            printf("\tФамилия:\n> %s\n", db[num].point_name);
            printf("\tРасстояние:\n> %d\n", db[num].distance);
            printf("\tКоличество рейсов:\n> %d\n", db[num].amount);
        }
    }
}

void save_routes() {
    FILE* routes_file = fopen(ROUTES_FILE, "w");

    if (routes_file != NULL) {
        int total_routes = 0;
        for (int route = 0; route < ROUTES; route++) {
            if (db[route].point_name != NULL)
                total_routes++;
        }
        fprintf(routes_file, "> %d\n", total_routes);

        for (int num = 0; num < ROUTES; num++) {
            if (db[num].point_name != NULL) {
                fprintf(routes_file, "%s %d %d\n",
                    db[num].point_name, db[num].distance, db[num].amount);
            }
        }

        printf("Файл маршрутов сохранён\n");
    } else {
        printf("Ошибка\n");
    }

    fclose(routes_file);
}

void read_routes() {
    FILE* routes_file = fopen(ROUTES_FILE, "r");

    if (routes_file != NULL) {
        for (int route = 0; route < ROUTES; route++) {
            if (db[route].point_name != NULL)
                db[route].point_name = NULL;
        }

        int total_routes = 0;
        fscanf(routes_file, "> %d\n", &total_routes);

        for (int num = 0; num < total_routes; num++) {
            db[num].point_name = calloc(POINT_SIZE, sizeof(char));

            fscanf(routes_file, "%s %d %d\n",
                db[num].point_name, &db[num].distance, &db[num].amount);
        }

        printf("Файл маршрутов загружен\n");
    } else {
        printf("Ошибка\n");
    }

    fclose(routes_file);
}

// вернёт -1 если левая строка меньше
// или просто 1 ежели меньше вторая
int str_comp(const char* left, const char* right, int offset) {
    int max_offset = strlen(left) < strlen(right) ? strlen(left) : strlen(right);
    if (left[offset] > right[offset])
        return -1;
    else if (right[offset] > left[offset])
        return 1;
    else {
        if (offset < max_offset)
            return str_comp(left, right, offset+1);
        else
            return (strlen(left) > strlen(right) ? -1 : 1);
    }
}