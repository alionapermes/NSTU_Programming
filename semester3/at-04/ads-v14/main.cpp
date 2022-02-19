#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>

#define DEBUG

using namespace std;

const int SIZE = 8;
const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz";

int  buble_sort(array<char, SIZE>& keys);
void fill_random(array<char, SIZE>& keys);
bool has_key(const array<char, SIZE>& keys, char key);


int main()
{
    array<char, 8> keys;
    fill_random(keys);
    
#ifdef DEBUG
    for (auto& key : keys)
        cout << key;
    cout << endl;
#endif

    int counter = buble_sort(keys);
    cout << "Потребовалось сравнений: " << counter << endl;

#ifdef DEBUG
    for (auto& key : keys)
        cout << key;
    cout << endl;
#endif

    return 0;
}

int buble_sort(array<char, SIZE>& keys)
{
    bool sorted = false;
    int counter = 0;

    while (!sorted) {
        sorted = true;

        for (int x = 0; x + 1 < SIZE; x++) {
            counter++;

            if (keys[x + 1] < keys[x]) {
                char tmp    = keys[x + 1];
                keys[x + 1] = keys[x];
                keys[x]     = tmp;
                sorted      = false;
            }
        }
    }

    return counter;
}

void fill_random(array<char, SIZE>& keys)
{
    srand(time(nullptr));

    for (int i = 0; i < SIZE; i++) {
        char key;

        do {
            key = ALPHABET[rand() % 26];
        } while (has_key(keys, key));

        keys[i] = key;
    }
}

bool has_key(const array<char, SIZE>& keys, char key)
{
    for (int i = 0; i < SIZE; i++) {
        if (keys[i] == key)
            return true;
    }

    return false;
}

