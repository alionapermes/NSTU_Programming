/* Курсовая работа по информатике. Вариант 3-3.
 * Структура: Название фирмы, количество работников, уставной капитал
 * Количество записей: 200
 * Номер поля для сортировки: 3
 * Выделение памяти: динамическое
 * Тип сортировки: по возрастанию
 * Вывод: принтер
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define FIRMS 200
#define FIRM_NAME 30
#define FILE_DB "file.db"
#define FILE_PRINTER "file.printer"

struct Firm {
    char* name;
    int workers;
    int stock;
};

void write_new_firm();
void print_firm_by_num();
void sort();
void print_all_firms();
void save_file();
void load_from_file();

struct Firm* database;
bool db_sorted;

int main() {
    setlocale(LC_ALL, "RUS");

    database = calloc(FIRMS, sizeof(struct Firm));
    db_sorted = false;

    for (int id = 0; id < FIRMS; id++)
        database[id].stock = -1;

    int command = 0;
    do
    {
        printf("\nМеню управления базой данных\n");
        printf("1 - Ввод записи с произвольным номером\n");
        printf("2 - Вывод записи с заданным номером\n");
        printf("3 - Сортировка записей по уставному капиталу в порядке возрастания\n");
        printf("4 - Вывод в принтер всех записей в отсортированном виде\n");
        printf("5 - Сохранение всех записей в файле\n");
        printf("6 - Чтение записей из файла\n");
        printf("0 - Выход из программы\n");

        printf("\nВвод комманды: ");
        scanf("%d", &command);

        if (command == 0)
            break;
        else if (command == 1)
            write_new_firm();
        else if (command == 2)
            print_firm_by_num();
        else if (command == 3)
            sort();
        else if (command == 4)
            print_all_firms();
        else if (command == 5)
            save_file();
        else if (command == 6)
            load_from_file();
        else
            printf("Неверный ввод\n");

        printf("================\n");
    } while (command != 0);

    return 0;
}

void write_new_firm() {
    int id;

    printf("Ввод номера: ");
    scanf("%d", &id);
    id--;

    database[id].name = calloc(FIRM_NAME, sizeof(char));

    printf("Ввод информации о фирме\n");

    printf("* Название: ");
    scanf("%s", database[id].name);

    printf("* Количество работников: ");
    scanf("%d", &database[id].workers);

    printf("* Уставной капитал: ");
    scanf("%d", &database[id].stock);

    db_sorted = false;
}

void print_firm_by_num() {
    int id;

    printf("Ввод номера: ");
    scanf("%d", &id);
    id--;

    if (database[id].name != NULL)
    {
        FILE* file_printer = fopen(FILE_PRINTER, "w");

        if (file_printer != NULL)
        {
            fprintf(file_printer, "Информация о фирме №%d\n",      id+1);
            fprintf(file_printer, "* Название: %s\n",              database[id].name);
            fprintf(file_printer, "* Количество работников: %d\n", database[id].workers);
            fprintf(file_printer, "* Уставной капитал: %d\n",      database[id].stock);
        }
        else
            printf("Не удалось вывести данные в принтер\n");


        fclose(file_printer);
    }
    else
        printf("Информация о компании №%d отсутствует\n", id+1);
}

void sort() {
    if (!db_sorted)
    {
        for (int i = 0; i < FIRMS/2; i++)
        {
            for (int id = FIRMS-1; id > 0; id--)
            {
                if (database[id-1].stock < 0 ||
                   (database[id].stock   > 0 &&
                    database[id].stock   < database[id-1].stock))
                {
                    struct Firm temp = database[id-1];
                    database[id-1] = database[id];
                    database[id] = temp;
                }
            }
        }

        printf("Сортировка выполнена\n");
        db_sorted = true;
    }
}

void print_all_firms() {
    if (!db_sorted) 
        sort();

    FILE* file_printer = fopen(FILE_PRINTER, "w");

    if (file_printer != NULL)
    {
        for (int id = 0; id < FIRMS; id++)
        {
            if (database[id].name != NULL)
            {
                fprintf(file_printer, "Информация о фирме №%d\n",      id+1);
                fprintf(file_printer, "* Название: %s\n",              database[id].name);
                fprintf(file_printer, "* Количество работников: %d\n", database[id].workers);
                fprintf(file_printer, "* Уставной капитал: %d\n",      database[id].stock);
            }
        }
    }
    else
        printf("Не удалось вывести данные в принтер\n");

    fclose(file_printer);
}

void save_file()
{
    FILE* file_db = fopen(FILE_DB, "w");

    if (file_db != NULL)
    {
        int saved_firms = 0;
        for (int id = 0; id < FIRMS; id++)
        {
            if (database[id].name != NULL)
                saved_firms++;
        }
        fprintf(file_db, "<%d>\n", saved_firms);

        for (int id = 0; id < FIRMS; id++)
        {
            if (database[id].name != NULL)
            {
                fprintf(file_db, "%s %d %d\n",
                    database[id].name, database[id].workers, database[id].stock);
            }
        }

        printf("Записи сохранены\n");
    }
    else
        printf("Не удалось сохранить данные\n");

    fclose(file_db);
}

void load_from_file() {
    FILE* file_db = fopen(FILE_DB, "r");

    if (file_db != NULL)
    {
        for (int id = 0; id < FIRMS; id++)
        {
            if (database[id].name != NULL)
                database[id].name  = NULL;
        }

        int saved_firms = 0;
        fscanf(file_db, "<%d>\n", &saved_firms);

        for (int id = 0; id < saved_firms; id++)
        {
            database[id].name = calloc(FIRM_NAME, sizeof(char));

            fscanf(file_db, "%s %d %d\n",
                database[id].name, &database[id].workers, &database[id].stock);
        }

        printf("Данные загружены из файла\n");
    }
    else
        printf("Не удалось загрузить данные\n");

    fclose(file_db);
    db_sorted = false;
}
