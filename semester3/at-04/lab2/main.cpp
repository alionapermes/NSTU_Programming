/**
 * Лабораторная работа №2. Семестр 3
 * Группа АТ-04. Вариант 9
 * Щербакова А.
 * 
 * Т.к. это учебный пример, для определения некоторых
 * значений используются соответствующие стандартные константы
 */

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>

#define LINE_SIZE 1024

using namespace std;

typedef vector<string> Strings;

void read_file(const char* filename, map<char, Strings>& text);
void print_strings(const Strings& lines);
void save_strings(const string& filename, const Strings& lines);
void print_help();

int main(int argc, char** argv)
{
    try {
        char max_ltr;
        string filename;
        map<char, Strings> Text;

        if (argc != 2) {
            print_help();
            throw runtime_error("Неверные аргументы!");
        }

        read_file(argv[1], Text);
        auto max_it = max_element(Text.cbegin(), Text.cend(),
            [](const pair<char, Strings>& p1, const pair<char, Strings>& p2) {
                return p2.second.size() > p1.second.size();
            }
        );

        cout << "Файл считан\n"
            << "Способ вывода (имя файла или 0 для вывода на экран): ";
        cin >> filename;

        if ((filename[0] == '0') && (filename.length() == 1)) {
            print_strings(max_it->second);
        } else {
            save_strings(filename, max_it->second);
            cout << "Вывод сохранён в файл " << filename << endl;
        }
    } catch (const exception& e) {
        cout << e.what() << endl;
        return -1;
    }

    return 0;
}

void print_help()
{
    cout << "Использование: <имя программы> <имя файла>\n";
}

void print_strings(const Strings& lines)
{
    for (auto cit = lines.cbegin(); cit != lines.cend(); cit++) {
        cout << *cit << endl;
    }
    cout << endl;
}

void save_strings(const string& filename, const Strings& lines)
{
    ofstream file(filename);

    for (auto cit = lines.cbegin(); cit != lines.cend(); cit++) {
        file << *cit << endl;
    }

    file.close();
}

void read_file(const char* filename, map<char, Strings>& text)
{
    ifstream file(filename);
    char line[LINE_SIZE] = {0};

    while (file.getline(line, LINE_SIZE)) {
        int non_space = 0;
        for (; line[non_space] == ' '; non_space++);

        char first = tolower(line[non_space]);
        text[first].push_back(string(line));
    }

    file.close();
}

