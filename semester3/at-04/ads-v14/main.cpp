/**
 * 1. Реализовать функцию для решения задачи:
 * Друзья решили подшутить над Василием и переставили
 * в его клавиатуре 8 кнопок местами.
 * Сколько сравнений необходимо выполнить Василию,
 * чтобы найти все перестановки.
 *
 * 2. Написать функцию, которая оценивает трудоемкость алгоритмов из п. 1
 * для следующего количества кнопок: 8, 32, 64, 88, 108
 * для худшего, лучшего и среднего
 * (например, генерация выборки случайным образом) случаев.
 *
 * Оцените асимптотическую сложность реализованных алгоритмов.
 * Выведите на экран значения в соответствии с таблицей.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

#define DEBUG

using namespace std;

int  buble_sort(vector<int>& keys);
void fill_random(vector<int>& keys);
void fill_best(vector<int>& keys);
void fill_worst(vector<int>& keys);
bool has_key(const vector<int>& keys, int key);


int amounts[] = {8, 32, 64, 88, 108};
int amount;


int main()
{
    const string border   = " | ";
    const int col_width   = 8;
    const int total_width = col_width * 7 + border.length() * 6;

    cout
        << setw(col_width) << "num"      << border
        << setw(col_width) << "Te1"      << border
        << setw(col_width) << "Te2"      << border
        << setw(col_width) << "T1"       << border
        << setw(col_width) << "T2"       << border
        << setw(col_width) << "Te1 / T1" << border
        << setw(col_width) << "Te2 / T2" << endl;

    for (int i = 0; i < total_width; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < 5; i++) {
        amount = amounts[i];
        vector<int> keys(amount);

        fill_random(keys);
        int avg = buble_sort(keys);

        fill_best(keys);
        int best = buble_sort(keys);

        fill_worst(keys);
        int worst = buble_sort(keys);

        cout
            << setw(col_width) << amount << border
            << setw(col_width) << best   << border
            << setw(col_width) << best   << border
            << setw(col_width) << worst  << border
            << setw(col_width) << worst  << border
            << setw(col_width) << avg    << border
            << setw(col_width) << avg    << endl;
    }

    return 0;
}

int buble_sort(vector<int>& keys)
{
    bool sorted = false;
    int counter = 0;

    for (int i = 0; i + 1 < amount; i++) {
        sorted = true;

        for (int x = 0; x + 1 < amount; x++) {
            counter++;

            if (keys[x + 1] < keys[x]) {
                int tmp     = keys[x + 1];
                keys[x + 1] = keys[x];
                keys[x]     = tmp;
                sorted      = false;
            }
        }

        if (sorted)
            break;
    }

    return counter;
}

void fill_random(vector<int>& keys)
{
    srand(time(nullptr));

    for (int i = 0; i < amount; i++) {
        int key;

        do {
            key = rand() % amount + 1;
        } while (has_key(keys, key));

        keys[i] = key;
    }
}

void fill_worst(vector<int>& keys)
{
    for (int i = 0; i < amount; i++) {
        keys[i] = amount - i;
    }
}

void fill_best(vector<int>& keys)
{
    for (int i = 0; i < amount; i++) {
        keys[i] = i;
    }
}

bool has_key(const vector<int>& keys, int key)
{
    for (int i = 0; i < amount; i++) {
        if (keys[i] == key)
            return true;
    }

    return false;
}

