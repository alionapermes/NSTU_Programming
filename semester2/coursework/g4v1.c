/* Курсовая работа по информатике. Вариант 4-1.
 * Структура: Наименование детали, количество, вес
 * Количество записей: 100
 * Номер поля для сортировки: 1
 * Выделение памяти: статическое
 * Тип сортировки: по возрастанию
 * Вывод: принтер
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

#define DETAILS_COUNT 100
#define LETTERS_COUNT 30
#define DB_LOCATION   "detailsDb.txt"
#define OUTPUT_FILE   "outputFile.txt"

typedef struct {
    char name[LETTERS_COUNT];
    int  amount;
    int  weight;
} Detail;

void newDetail();
void getDetail();
void sortDetails();
void getAll();
void putDbToFile();
void getDbFromFile();

int longerString(const char* s1, const char* s2, int letter);

Detail warehouse[DETAILS_COUNT];
bool isSorted;

int main()
{
    setlocale(LC_ALL, "RU");
    isSorted = false;

    int commandNum;
    while (true) {
        printf("\nДоступные команды\n");
        printf("=> 1 Ввод записи с произвольным номером\n");
        printf("=> 2 Вывод записи с заданным номером\n");
        printf("=> 3 Сортировка записей по наименованию в порядке возрастания\n");
        printf("=> 4 Вывод в принтер всех записей в отсортированном виде\n");
        printf("=> 5 Сохранение всех записей в файле\n");
        printf("=> 6 Чтение записей из файла\n");
        printf("=> 0 Выход из программы\n");

        printf("\nКоманда:\n> ");
        scanf("%d", &commandNum);

        if      (commandNum == 0) break;
        else if (commandNum == 1) newDetail();
        else if (commandNum == 2) getDetail();
        else if (commandNum == 3) sortDetails();
        else if (commandNum == 4) getAll();
        else if (commandNum == 5) putDbToFile();
        else if (commandNum == 6) getDbFromFile();

        printf("\n");
    }

    return 0;
}

void newDetail()
{
    int detail;

    printf("Номер детали: ");
    scanf("%d", &detail);
    detail--;

    printf("\n");

    printf("Наименование: ");
    scanf("%s", warehouse[detail].name);

    printf("Количество: ");
    scanf("%d", &warehouse[detail].amount);

    printf("Вес: ");
    scanf("%d", &warehouse[detail].weight);

    isSorted = false;
}

void getDetail()
{
    int detail;

    printf("Номер детали: ");
    scanf("%d", &detail);
    detail--;

    FILE* outputFile = fopen(OUTPUT_FILE, "w");

    if (outputFile != NULL) {
        if (warehouse[detail].amount > 0) {
            fprintf(outputFile, "=> Деталь %d\n", detail+1);
            fprintf(outputFile, "Наименование: %s\n", warehouse[detail].name);
            fprintf(outputFile, "..Количество: %d\n", warehouse[detail].amount);
            fprintf(outputFile, ".........Вес: %d\n", warehouse[detail].weight);
        }
        else
            printf("Деталь №%d отсутствует в базе\n", detail+1);

        fclose(outputFile);
    }
}

void sortDetails()
{
    if (!isSorted) {
        for (int n = 0; n < DETAILS_COUNT; n++) {
            for (int detail = 0; detail < DETAILS_COUNT-1; detail++) {
                if (warehouse[ detail ].amount == 0 ||
                   (warehouse[detail+1].amount != 0 &&
                    longerString(warehouse[detail].name, warehouse[detail+1].name, 0) < 0))
                {
                    Detail temp         = warehouse[detail+1];
                    warehouse[detail+1] = warehouse[ detail ];
                    warehouse[ detail ] = temp;
                }
            }
        }

        printf("Детали отсортированы\n");
        isSorted = true;
    }
}

void getAll()
{
    if (!isSorted) 
        sortDetails();

    FILE* outputFile = fopen(OUTPUT_FILE, "w");

    if (outputFile != NULL) {
        for (int detail = 0; detail < DETAILS_COUNT; detail++) {
            if (warehouse[detail].amount > 0) {
                fprintf(outputFile, "\n=> Деталь %d\n", detail+1);
                fprintf(outputFile, "Наименование: %s\n", warehouse[detail].name);
                fprintf(outputFile, "..Количество: %d\n", warehouse[detail].amount);
                fprintf(outputFile, ".........Вес: %d\n", warehouse[detail].weight);
            }
        }

        fclose(outputFile);
    }
}

void putDbToFile()
{
    FILE* detailsDb = fopen(DB_LOCATION, "w");

    if (detailsDb != NULL) {
        int notes = 0;
        for (int note = 0; note < DETAILS_COUNT; note++)
            if (warehouse[note].amount > 0) notes++;
        fprintf(detailsDb, "%d\n", notes);

        for (int note = 0; note < DETAILS_COUNT; note++)
            if (warehouse[note].amount > 0) fprintf(detailsDb, "%s %d %d\n", warehouse[note].name, warehouse[note].amount, warehouse[note].weight);
        printf("Сохранение выполнено\n");

        fclose(detailsDb);
    }
    else
        printf("Что-то пошло не так\n");
}

void getDbFromFile()
{
    FILE* detailsDb = fopen(DB_LOCATION, "r");

    if (detailsDb != NULL) {
        for (int note = 0; note < DETAILS_COUNT; note++)
            if (warehouse[note].amount > 0) warehouse[note].amount = 0;

        int notes = 0;
        fscanf(detailsDb, "%d\n", &notes);

        for (int note = 0; note < notes; note++)
            fscanf(detailsDb, "%s %d %d\n", warehouse[note].name, &warehouse[note].amount, &warehouse[note].weight);

        printf("Загрузка выполнена\n");
        fclose(detailsDb);
    }
    else
        printf("Что-то пошло не так\n");

    isSorted = false;
}

// возвращаемое значение зависит от того,
// какая из строк больше в посимвольном сравнении
// -1 если первая, и 1 если вторая
int longerString(const char* s1, const char* s2, int letter)
{
    int letterNum = letter;
    int maxLength = strlen(s1) < strlen(s2) ? strlen(s1) : strlen(s2);

    if (s1[letterNum] > s2[letterNum])
        return -1;
    else if (s2[letterNum] > s1[letterNum])
        return 1;
    else
        return (letterNum < maxLength ? longerString(s1, s2, letterNum+1) : (strlen(s1) > strlen(s2) ? -1 : 1));
}