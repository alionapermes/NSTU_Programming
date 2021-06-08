/* Курсовая работа по информатике. Вариант 4-20.
 * Структура: Фамилия, номер курса, стипендия
 * Количество записей: 300
 * Номер поля для сортировки: 1
 * Выделение памяти: динамическое
 * Тип сортировки: по убыванию
 * Вывод: экран
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define NOTES 300
#define NAME_SIZE 40
#define DATABASE_FILE "database.txt"

typedef struct {
    char* lastname;
    int year;
    int scholarship;
} Student;

void input_student();
void print_student();
void sort_by_name();
void print_students();
void save_students();
void get_students();

int btr_str(const char* s1, const char* s2, int l);

Student* students;
bool sorted;

int main() {
    setlocale(LC_ALL, "RUS");

    students = calloc(NOTES, sizeof(Student));
    sorted = false;

    int cmd = 0;
    do {
        printf("\n\tВозможные команды\n");
        printf("#1 Ввод записи с произвольным номером\n");
        printf("#2 Вывод записи с заданным номером\n");
        printf("#3 Сортировка записей по фамилии в порядке убывания\n");
        printf("#4 Вывод на экран всех записей в отсортированном виде\n");
        printf("#5 Сохранение всех записей в файле\n");
        printf("#6 Чтение записей из файла\n");
        printf("#0 Выход из программы\n");

        printf("\nНомер команды: ");
        scanf("%d", &cmd);

        if (cmd == 0)
            break;
        else if (cmd == 1)
            input_student();
        else if (cmd == 2)
            print_student();
        else if (cmd == 3)
            sort_by_name();
        else if (cmd == 4)
            print_students();
        else if (cmd == 5)
            save_students();
        else if (cmd == 6)
            get_students();
        else
            printf("Неверный номер комманды\n");

        printf("~~~~~~~~~~~~~~~~\n");
    } while (cmd != 0);

    return 0;
}

void input_student() {
    int number;

    printf("Номер: ");
    scanf("%d", &number);
    number--;

    students[number].lastname = calloc(NAME_SIZE, sizeof(char));

    printf("\n");

    printf("@ Фамилия: ");
    scanf("%s", students[number].lastname);

    printf("@ Курс: ");
    scanf("%d", &students[number].year);

    printf("@ Стипендия: ");
    scanf("%d", &students[number].scholarship);

    sorted = false;
}

void print_student() {
    int number;

    printf("Номер: ");
    scanf("%d", &number);
    number--;

    if (students[number].lastname != NULL) {
        printf("~ Запись %d ~\n", number+1);
        printf("@ Фамилия: %s\n", students[number].lastname);
        printf("@ Курс: %d\n", students[number].year);
        printf("@ Стипендия: %d\n", students[number].scholarship);
    } else {
        printf("Такой записи нет\n");
    }
}

void sort_by_name() {
    if (!sorted) {
        for (int loop = 0; loop < NOTES/2; loop++) {
            for (int number = 0; number < NOTES-1; number++) {
                if (students[ number ].lastname == NULL ||
                   (students[number+1].lastname != NULL &&
                    btr_str(students[number].lastname, students[number+1].lastname, 0) > 0))
                {
                    Student temp = students[number+1];
                    students[number+1] = students[number];
                    students[number] = temp;
                }
            }
        }

        printf("База данных отсортированна\n");
        sorted = true;
    }
}

void print_students() {
    if (!sorted) 
        sort_by_name();

    for (int number = 0; number < NOTES; number++) {
        if (students[number].lastname != NULL) {
            printf("\n~ Запись %d ~\n", number+1);
            printf("@ Фамилия: %s\n", students[number].lastname);
            printf("@ Курс: %d\n", students[number].year);
            printf("@ Стипендия: %d\n", students[number].scholarship);
        }
    }
}

void save_students() {
    FILE* file = fopen(DATABASE_FILE, "w");

    if (file != NULL) {
        int notes = 0;
        for (int note = 0; note < NOTES; note++) {
            if (students[note].lastname != NULL)
                notes++;
        }
        fprintf(file, "(%d)\n", notes);

        for (int note = 0; note < NOTES; note++) {
            if (students[note].lastname != NULL) {
                fprintf(file, "%s %d %d\n",
                    students[note].lastname, students[note].year, students[note].scholarship);
            }
        }

        printf("Сохранено\n");
    } else {
        printf("Ошибка сохранения\n");
    }

    fclose(file);
}

void get_students() {
    FILE* file = fopen(DATABASE_FILE, "r");

    if (file != NULL) {
        for (int note = 0; note < NOTES; note++) {
            if (students[note].lastname != NULL)
                students[note].lastname = NULL;
        }

        int notes = 0;
        fscanf(file, "(%d)\n", &notes);

        for (int note = 0; note < notes; note++) {
            students[note].lastname = calloc(NAME_SIZE, sizeof(char));

            fscanf(file, "%s %d %d\n",
                students[note].lastname, &students[note].year, &students[note].scholarship);
        }

        printf("Данные загружены\n");
    } else {
        printf("Ошибка чтения\n");
    }

    fclose(file);
    sorted = false;
}

// возвращает -1, если первая строка больше
// возвращает  1, если больше вторая
int btr_str(const char* s1, const char* s2, int l) {
    int ltr = l;
    int max_ltr = strlen(s1) < strlen(s2) ? strlen(s1) : strlen(s2);

    if (s1[ltr] > s2[ltr])
        return -1;
    else if (s2[ltr] > s1[ltr])
        return 1;
    else {
        if (ltr < max_ltr)
            return btr_str(s1, s2, ltr+1);
        else
            return (strlen(s1) > strlen(s2) ? -1 : 1);
    }
}