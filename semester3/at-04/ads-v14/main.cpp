#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

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
    for (int i = 0; i < 5; i++) {
        amount = amounts[i];
        vector<int> keys(amount);

        cout << "[Трудоёмкость алгоритма для " << amount << " кнопок]\n";

        fill_random(keys);
        cout << "Средний случай: " << buble_sort(keys) << endl;
        
        fill_best(keys);
        cout << "Лучший случай: " << buble_sort(keys) << endl;

        fill_worst(keys);
        cout << "Худший случай: " << buble_sort(keys) << endl;

        cout << endl;
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

