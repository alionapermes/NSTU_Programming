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
    pair<const string, list_v3<int>>* current = nullptr;
    unordered_map<string, list_v3<int>> containers;

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
                create_new(0);
                break;
            } case 2: {
                int capacity = read_positive();
                create_new(capacity);
                break;
            } case 3: {
                create_based(current->second);
                break;
            } case 4: {
                int index = read_positive();

                try {
                    if (check_index(index))
                        print_by_index(index);
                } catch (const exception& e) {
                    cout << "ошибка: " << e.what() << endl;
                }
                break;
            } case 5: {
                int index = read_positive();
                
                try {
                    if (check_index(index))
                        cin >> current->second[index];
                } catch (const exception& e) {
                    cout << "ошибка: " << e.what() << endl;
                }
                break;
            } case 6: {
                cout
                    << current_name_with("items")
                    << current->second << endl;
                break;
            } case 7: {
                cout
                    << current_name_with("size")
                    << current->second.size() << endl;
                break;
            } case 8: {
                cout
                    << current_name_with("capacity")
                    << current->second.capacity() << endl;
                break;
            } case 9: {
                cout
                    << current_name_with("empty")
                    << (current->second.empty() ? "пустой" : "не пустой")
                    << endl;
                break;
            } case 10: {
                current->second.clear();
                break;
            } case 11: {
                int value = read_number();
                current->second.push_back(value);
                break;
            } case 12: {
                int value = read_number();
                current->second.push_front(value);
                break;
            } case 13: {
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
            } case 14: {
                insert_value();
                break;
            } case 15: {
                delete_value();
                break;
            } case 16: {
                switch_container(read_name(false));
                break;
            } case 17: {
                delete_container(read_name(false));
                break;
            } case 18: {
                show_list();
                break;
            } case 19: {
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
    create_based(const list_v3<int>& ev)
    {
        string name      = read_name();
        containers[name] = ev;
        current          = &*containers.find(name);
    }

    void
    create_new(int capacity)
    {
        string name      = read_name();
        containers[name] = list_v3<int>(capacity);
        current          = &*containers.find(name);
    }

    void
    show_help()
    {
        cout
            << "1.  Новый пустой контейнер\n"
            << "2.  Новый контейнер заданного размера\n"
            << "3.  Новый контейнер на основе текущего\n"
            << "4.  Получение элемента по индексу\n"
            << "5.  Запись элемента по индексу\n"
            << "6.  Вывод элементов контейнера\n"
            << "7.  Получение количества элементов в контейнере\n"
            << "8.  Получение объёма контейнера\n"
            << "9.  Проверка на пустоту\n"
            << "10. Очистка контейнера\n"
            << "11. Добавление в конец контейнера\n"
            << "12. Добавление в начало контейнера\n"
            << "13. Поиск по значению\n"
            << "14. Вставка перед позицией\n"
            << "15. Удаление позиции\n"
            << "16. Переключение контейнера\n"
            << "17. Удаление контейнера\n"
            << "18. Список контейнеров\n"
            << "19. Вывод подсказок\n"
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

