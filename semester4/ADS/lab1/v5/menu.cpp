#include "container.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class test_menu
{
public:
    void start()
    {
        show_help();

        while (true) {
            int cmd = command();

            if (!cmd) {
                cout << "Завершение программы\n";
                exit(0);
            } else if (cmd == -1) {
                cout << "Неверная команда\n";
                show_help();
            }
        }
    }

private:
    pair<const string, bidir_list<int>>* current = nullptr;
    unordered_map<string, bidir_list<int>> containers;

    int
    command()
    {
        string tak_nado = "[" + (current ? current->first : "*") + "]: ";
        int command = read_positive(tak_nado);

        switch (command) {
            case 0:
            case 1:
            case 2:
            case 18:
            case 19:
                break;
            default:
                cout << "Создайте сперва контейнер\n";
                return 1;
                break;
        }

        if (!command)
            return 0;
        else if (command > 21)
            return -1;

        switch (command) {
            case 1: {
                create_new();
                break;
            } case 2: {
                create_based(current->second);
                break;
            } case 3: {
                int index = read_positive();

                try {
                    if (check_index(index))
                        print_by_index(index);
                } catch (const exception& e) {
                    cout << "ошибка: " << e.what() << endl;
                }
                break;
            } case 4: {
                int index = read_positive();
                
                try {
                    if (check_index(index))
                        cin >> current->second[index];
                } catch (const exception& e) {
                    cout << "ошибка: " << e.what() << endl;
                }
                break;
            } case 5: {
                cout
                    << current_name_with("items")
                    << current->second << endl;
                break;
            } case 6: {
                cout
                    << current_name_with("size")
                    << current->second.size() << endl;
                break;
            } case 7: {
                cout
                    << current_name_with("empty")
                    << (current->second.empty() ? "пустой" : "не пустой")
                    << endl;
                break;
            } case 8: {
                current->second.clear();
                break;
            } case 9: {
                int value = read_number();
                current->second.push_back(value);
                break;
            } case 10: {
                int value = read_number();
                current->second.push_front(value);
                break;
            } case 11: {
                cout << "(Искомое значение) ";
                int value = read_number();
                auto iter = current->second.find(value);

                string result = "Элемент ";
                result += (
                    iter != current->second.end()
                    ? "существет"
                    : "не существует"
                );
                cout << current_name_with("find") << result << endl;
                break;
            } case 12: {
                insert_value();
                break;
            } case 13: {
                delete_value();
                break;
            } case 14: {
                switch_container(read_name(false));
                break;
            } case 15: {
                delete_container(read_name(false));
                break;
            } case 16: {
                show_list();
                break;
            } case 17: {
                show_help();
                break;
            }
        }

        return command;
    }

    void
    delete_value()
    {
        if (!current) {
            cout << "Создайте сперва контейнер\n";
            return;
        }

        int elem = 0;

        cout << "Введите элемент, который необходимо удалить: ";
        cin >> elem;

        auto iter = current->second.find(elem);
        if (iter == current->second.end()) {
            cout << "Нет такого элемента в текущем контейнере\n";
            return;
        }

        current->second.erase(iter);
    }

    void
    insert_value()
    {
        if (!current) {
            cout << "Создайте сперва контейнер\n";
            return;
        }

        int elem = 0, value = 0;

        cout
            << "Введите элемент, после которого "
            << "будет произведена вставка: ";
        cin >> elem;

        auto iter = current->second.find(elem);
        if (iter == current->second.end()) {
            cout << "Нет такого элемента в текущем контейнере\n";
            return;
        }

        cout << "Введите значение для вставки: ";
        cin >> value;

        current->second.insert(iter, value);
    }

    void
    switch_container(const string& name)
    {
        auto iter = containers.find(name);

        if (iter == containers.end()) {
            cout << "Нет такого контейнера\n";
            return;
        }

        current = &*iter;
    }

    void
    show_list()
    {
        if (!current) {
            cout << "Создайте сперва контейнер\n";
            return;
        }

        int num = 0;

        for (const auto& [name, container] : containers)
            cout << "[" << num++ << "] " << name << endl;
    }

    void
    delete_container(const string& name)
    {
        auto iter = containers.find(name);

        if (iter == containers.end()) {
            cout << "Нет такого контейнера\n";
            return;
        }

        if (iter->first == name || containers.size() == 1)
            current = nullptr;

        containers.erase(iter);
    }

    string
    current_name_with(const string& with)
    { return "[" + current->first + ":" + with + "]: "; }

    bool
    check_index(int index)
    { return index < current->second[index]; }

    void
    print_by_index(int index)
    {
        cout
            << current->first << "[" << index << "]: "
            << current->second[index] << endl;
    }

    void
    create_based(const bidir_list<int>& ev)
    {
        string name      = read_name();
        containers[name] = ev;
        current          = &*containers.find(name);
    }

    void
    create_new()
    {
        string name      = read_name();
        containers[name] = bidir_list<int>();
        current          = &*containers.find(name);
    }

    void
    show_help()
    {
        cout
            << "1.  Новый пустой контейнер\n"
            << "2.  Новый контейнер на основе текущего\n"
            << "3.  Получение элемента по индексу\n"
            << "4.  Запись элемента по индексу\n"
            << "5.  Вывод элементов контейнера\n"
            << "6.  Получение количества элементов в контейнере\n"
            << "7.  Проверка на пустоту\n"
            << "8.  Очистка контейнера\n"
            << "9.  Добавление в конец контейнера\n"
            << "10. Добавление в начало контейнера\n"
            << "11. Поиск по значению\n"
            << "12. Вставка перед позицией\n"
            << "13. Удаление позиции\n"
            << "14. Переключение контейнера\n"
            << "15. Удаление контейнера\n"
            << "16. Список контейнеров\n"
            << "17. Вывод подсказок\n"
            << "0.  Выход\n";
    }

    string
    read_name(bool mode = true)
    {
        bool correct = false;
        string name;

        do {
            cout << "Введите имя контейнера (1-8 символов): ";
            cin >> name;

            if (mode) {
                if (containers.find(name) != containers.end()) {
                    cout << "Контейнер с таким имененм уже существует\n";
                    continue;
                }
            } else {
                if (containers.find(name) == containers.end()) {
                    cout << "Контейнер с таким именем не сещуствует\n";
                    continue;
                }
            }

            if (name.empty() || name.length() > 8)
                cout << "Неверный ввод, попробуйте снова\n";
            else
                correct = true;
        } while (!correct);

        return name;
    }

    int
    read_positive(string tak_nado = "Введите число > 0: ")
    {
        string input;
        int cap      = 0;
        bool correct = false;

        do {
            cout << tak_nado;
            cin >> input;

            try {
                cap = stoi(input);

                if ((cap < 0) || (to_string(cap) != input))
                    cout << "Неверный ввод, попробуйте снова\n";
                else
                    correct = true;
            } catch (std::invalid_argument&) {
                cout << "Неверный ввод, попробуйте снова\n";
            }
        } while (!correct);

        return cap;
    }

    int
    read_number()
    {
        string input;
        int cap      = 0;
        bool correct = false;

        do {
            cout << "Введите число: ";
            cin >> input;

            try {
                cap = stoi(input);

                if (to_string(cap) != input)
                    cout << "Неверный ввод, попробуйте снова\n";
                else
                    correct = true;
            } catch (std::invalid_argument&) {
                cout << "Неверный ввод, попробуйте снова\n";
            }
        } while (!correct);

        return cap;
    }
};


int main()
{
    test_menu menu;
    menu.start();

    return 0;
}

