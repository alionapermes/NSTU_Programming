/* Курсовая работа по информатике. Вариант 4-8.
 * Структура: Фамилия, номер курса, стипендия
 * Количество записей: 100
 * Номер поля для сортировки: 2
 * Выделение памяти: динамическое
 * Тип сортировки: по возрастанию
 * Вывод: экран
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define STUDENTS_NUMBER 100
#define NAME_SIZE 30
#define DATA "students.db"

typedef struct {
    char* lastname;
    int year;
    int scholarship;
} Student;

void add_new();
void get_student();
void sort_by_name();
void print_full();
void save_database();
void get_data_from_file();

Student* students_db;
bool is_sorted;

int main()
{
    setlocale(LC_ALL, "RU");

    students_db = calloc(STUDENTS_NUMBER, sizeof(Student));
    is_sorted = false;

    int cmd = 0;
    do
    {
        printf("\nДоступные команды\n");
        printf("'1' Ввод записи с произвольным номером\n");
        printf("'2' Вывод записи с заданным номером\n");
        printf("'3' Сортировка записей по году в порядке убывания\n");
        printf("'4' Вывод на экран всех записей в отсортированном виде\n");
        printf("'5' Сохранение всех записей в файле\n");
        printf("'6' Чтение записей из файла\n");
        printf("'0' Выход из программы\n");

        printf("\nКоманда: ");
        scanf("%d", &cmd);

        if (cmd == 0)
            break;
        else if (cmd == 1)
            add_new();
        else if (cmd == 2)
            get_student();
        else if (cmd == 3)
            sort_by_name();
        else if (cmd == 4)
            print_full();
        else if (cmd == 5)
            save_database();
        else if (cmd == 6)
            get_data_from_file();
        else
            printf("Неверная команда\n");

        printf("\n");
    } while (true);

    return 0;
}

void add_new()
{
    int number;

    printf("Номер: ");
    scanf("%d", &number);
    number--;

    students_db[number].lastname = calloc(NAME_SIZE, sizeof(char));

    printf("\n");

    printf("@ Фамилия: ");
    scanf("%s", students_db[number].lastname);

    printf("@ Курс: ");
    scanf("%d", &students_db[number].year);

    printf("@ Стипендия: ");
    scanf("%d", &students_db[number].scholarship);

    is_sorted = false;
}

void get_student()
{
    int num;

    printf("Номер: ");
    scanf("%d", &num);
    num--;

    if (students_db[num].lastname != NULL)
    {
        printf("| Запись %d |\n", num+1);
        printf("- Фамилия: %s\n", students_db[num].lastname);
        printf("- Курс: %d\n", students_db[num].year);
        printf("- Стипендия: %d\n", students_db[num].scholarship);
    }
    else
        printf("Записи №%d нет в базе\n", num+1);
}

void sort_by_name()
{
    if (!is_sorted)
    {
        for (int i = 0; i < STUDENTS_NUMBER; i++)
        {
            for (int num = 0; num < STUDENTS_NUMBER-1; num++)
            {
                if (students_db[ num ].year == 0 ||
                   (students_db[num+1].year != 0 &&
                    students_db[ num ].year > students_db[num+1].year))
                {
                    Student temp = students_db[num+1];
                    students_db[num+1] = students_db[num];
                    students_db[num] = temp;
                }
            }
        }

        printf("БД отсортирована\n");
        is_sorted = true;
    }
}

void print_full()
{
    if (!is_sorted) 
        sort_by_name();

    for (int num = 0; num < STUDENTS_NUMBER; num++)
    {
        if (students_db[num].lastname != NULL)
        {
            printf("\n| Запись %d |\n", num+1);
            printf("- Фамилия: %s\n", students_db[num].lastname);
            printf("- Курс: %d\n", students_db[num].year);
            printf("- Стипендия: %d\n", students_db[num].scholarship);
        }
    }
}

void save_database()
{
    FILE* db_file = fopen(DATA, "w");

    if (db_file != NULL) {
        int stds = 0;
        for (int std = 0; std < STUDENTS_NUMBER; std++)
        {
            if (students_db[std].lastname != NULL)
                stds++;
        }
        fprintf(db_file, "%d\n", stds);

        for (int std = 0; std < STUDENTS_NUMBER; std++)
        {
            if (students_db[std].lastname != NULL)
            {
                fprintf(db_file, "%s %d %d\n",
                    students_db[std].lastname, students_db[std].year, students_db[std].scholarship);
            }
        }

        printf("Сохранено\n");
        fclose(db_file);
    }
    else
        printf("Ошибка\n");
}

void get_data_from_file()
{
    FILE* db_file = fopen(DATA, "r");

    if (db_file != NULL)
    {
        for (int std = 0; std < STUDENTS_NUMBER; std++)
        {
            if (students_db[std].lastname != NULL)
                students_db[std].lastname = NULL;
        }

        int stds = 0;
        fscanf(db_file, "%d\n", &stds);

        for (int std = 0; std < stds; std++)
        {
            students_db[std].lastname = calloc(NAME_SIZE, sizeof(char));

            fscanf(db_file, "%s %d %d\n",
                students_db[std].lastname, &students_db[std].year, &students_db[std].scholarship);
        }

        printf("Загружено\n");
        fclose(db_file);
    }
    else
        printf("Ошибка\n");

    is_sorted = false;
}