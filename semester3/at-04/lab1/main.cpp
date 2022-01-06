/**
 * Лабораторная работа №1. Семестр 3
 * Группа АТ-04. Вариант 12
 * Щербакова А.
 * 
 * Т.к. это учебный пример, для определения некоторых
 * значений используются соответствующие стандартные константы
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// стандартные значения
#define BOOKS_COUNT 32
#define TITLE_SIZE  256


typedef struct {
    int   pages;
    char* title;
} Book;

// объявление прототипов функций, их реализация будут описаны ниже
void  save_to_file(const char* filename, const Book* books, int num);
void  find_book(const char* filename, const char* title, Book* book);
void  add_book(const Book* book, FILE* file);
void  print_book(const Book* book);
void  print_help();
int   read_books(Book* books, int limit);
Book* init_books(unsigned int count, unsigned int title_len);
void  free_books(Book* books, unsigned int count);
void  argc2(const char* filename);
void  argc3(const char* filename, const char* title);

int main(int argc, char** argv)
{
    switch (argc) {
        case 2: // обработка вызова с двумя аргументами
            argc2(argv[1]);
            break;
        case 3: // обработка вызова с тремя аргументами
            argc3(argv[1], argv[2]);
            break;
        default:
            printf("Неверное число аргументов!\n");
            print_help();
            return -1;
    }

    return 0;
}

void argc2(const char* filename)
{
    // инициализация массива для записи книг
    Book* books = init_books(BOOKS_COUNT, TITLE_SIZE);
    // считывание данных для книг из консоли
    int num = read_books(books, BOOKS_COUNT);
    // запись байтов массива книг в файл
    save_to_file(filename, books, num);
    // освобождение выделенной памяти
    free_books(books, BOOKS_COUNT);
}

void argc3(const char* filename, const char* title)
{
    Book book;
    // выделение памяти под заголовок
    book.title = (char*)calloc(sizeof(char), TITLE_SIZE);

    // поиск книги с нужным заголовком в файле
    find_book(filename, title, &book);
    // вывод информации о книге
    print_book(&book);

    // освобождение памяти, выделенной под заголовок
    free(book.title);
}

Book* init_books(unsigned int count, unsigned int title_len)
{
    // выделение памяти для массива записи книг
    Book* books = (Book*)calloc(sizeof(Book), count);

    // выделение памяти для заголовка каждой книги
    for (unsigned int u = 0; u < count; u++) {
        books[u].title = (char*)calloc(sizeof(char), title_len);
    }

    return books;
}

void free_books(Book* books, unsigned int count)
{
    // очистка памяти, выделенной под заголовок,
    // каждой из книг (по количеству count)
    for (unsigned int u = 0; u < count; u++) {
        free(books[u].title);
    }

    // очистка памяти самого массива структур книг
    free(books);
}

int read_books(Book* books, int limit)
{
    int books_num = 0;

    while (books_num < limit) {
        int count = 0;
        
        printf("\nКоличество книг для ввода (0 - стоп): ");
        scanf("%d", &count);

        if (count <= 0) {
            return books_num;
        }

        for (int n = 0; n < count; n++) {
            printf(
                "\n"
                "[Ввод информации о книге]\n"
                "Заголовок: "
            );
            scanf("%s", books[n].title);
            printf("Кол-во страниц: ");
            scanf("%d", &books[n].pages);
            printf("[Информация сохранена]\n");

            books_num++;

            if (books_num == limit) {
                break;
            }
        }
    }

    return books_num;
}

void print_book(const Book* book)
{
    printf(
        "\n"
        "/**\n"
        " * [Информация о книге]\n"
        " * Заголовок: %s\n"
        " * Кол-во страниц: %d\n"
        " */"
        "\n",
        book->title,
        book->pages
    );
}

void print_help()
{
    printf(
        "\n"
        "Использование: <имя программы> "
        "<имя файла> [<название книги>]"
        "\n"
    );
}

void add_book(const Book* book, FILE* file)
{
    const char* title = book->title;
    int title_len = strlen(title);
    int pages = book->pages;

    // запись байтов структуры книги вида
    // [[число_страниц][длина_заголовка][заголовок]]
    fwrite(&pages, sizeof(pages), 1, file);
    fwrite(&title_len, sizeof(title_len), 1, file);
    fwrite(title, sizeof(char), title_len, file);
}

void find_book(const char* filename, const char* title, Book* book)
{
    // открытие существующего файла на чтение
    FILE* file    = fopen(filename, "r");
    int title_len = 0;
    int pages     = 0;
    bool found    = false;

    do {
        char* tmp_title;

        // читаем байты для переменной количества страниц книги
        fread(&pages, sizeof(pages), 1, file);
        // читаем байты для переменной длины заголовка
        fread(&title_len, sizeof(title_len), 1, file);

        // выделение памяти и запись в неё заголовка из файла
        tmp_title = (char*)calloc(sizeof(char), title_len);
        fread(tmp_title, sizeof(char), title_len, file);

        // проверка на верность заголовка
        if (strcmp(title, tmp_title) == 0) {
            // копируем заголовок из временной переменной
            // в структуру книги
            strncpy(book->title, tmp_title, title_len);
            book->pages = pages;
            found = true;
        }

        // освобождение памяти временной переменной
        free(tmp_title);
    
    // если книга ещё не найдена и если файл ещё
    // не прочтён целиком, то продолжаем искать
    } while (!found && !feof(file));

    // закрытие файла
    fclose(file);
}

void save_to_file(const char* filename, const Book* books, int num)
{
    FILE* file;
    char* filenamebin = (char*)calloc(sizeof(char), strlen(filename) + 5);
    
    sprintf(filenamebin, "%s.bin", filename);

    // открытие файла на запись (и создание при необходимости)
    file = fopen(filenamebin, "w+");

    for (int n = 0; n < num; n++) {
        add_book(&books[n], file);
    }

    // закрытие файла
    fclose(file);
}
