// Подключение библиотек, необходимых для работы
#include <string>
#include <stdexcept>
#include <cstring>


/**
 * Класс matrix представляет собой
 * контейнер данных в формате матрицы
 */
template <typename T>
class matrix
{
public:
    // Конструктор, инициализирующий поля класса rows и cols значениями
    // принимаемых параметров _rows и _cols соответственно
    // Резервирует память для хранения данных
    matrix(size_t _rows, size_t _cols)
        : rows(_rows), cols(_cols)
    { allocate(); }

    // Конструктор копирования
    // Инициализирует класс копиями значений другого экземпляра этого же класса
    matrix(const matrix& m)
        : matrix(m.rows, m.cols)
    {
        // Копирование строк
        for (size_t row = 0; row < rows; row++) {
            // Копирование элементов из столбца col обрабатываемой строки row
            for (size_t col = 0; col < cols; col++) {
                data[row][col] = m[row][col];
            }
        }
    }

    // Конструктор на основе списка инициализации
    // Позволяет в удобной форме передавать данные для заполнения элементов
    // при иницализации объекта класса
    matrix(const std::initializer_list<std::initializer_list<T>>& i_list)
        : matrix(i_list.size(), i_list.begin()->size())
    {
        // Копирование строк из списка инициализации
        for (size_t row = 0; row < i_list.size(); row++) {
            // Получение содержимого обрабатываемой строки
            auto items_row = i_list.begin() + row;

            // Копирование элементов из столбца col обрабатываемой строки row
            for (size_t col = 0; col < items_row->size(); col++) {
                // Для выбора элемента строки с нужным индексом столбца
                // используется арифметика указателей с разыменованием
                data[row][col] = *(items_row->begin() + col); // m[row][col];
            }
        }
    }

    // Деструктор, освобождающий память, ранее выделенную для хранения данных
    ~matrix()
    { free_data(); }

    // Перегрузка оператора присваивания/копирования =
    // Копирует данные из матрицы правого операнда в матрицу левого операнда,
    // предварительно освободив ранее выделенную память
    matrix&
    operator=(const matrix& m)
    {
        // Освобождение памяти
        free_data();

        // Копирование свойств
        rows = m.rows;
        cols = m.cols;

        // Выделение памяти под новые данные
        allocate();

        // Копирование строк из матрицы правого операнда
        // в матрицу левого операнда
        for (auto row = 0; row < rows; row++) {
            // Копирование элементов из столбца col обрабатываемой строки row
            for (auto col = 0; col < cols; col++) {
                data[row][col] = m[row][col];
            }
        }

        // Возврат ссылки на матрицу левого операнда
        return *this;
    }

    // Перегрузка оператора разыменования по индексу []
    // Возвращает строку матрицы с номером row
    T*
    operator[](size_t row) const
    { return data[row]; }

    // Перегрузка оператора сложения с присваиванием +=
    // Прибавляет к элементам матрицы левого операнда
    // элементы матрицы правого операнда, если это возможно
    // Иначе выбрасывает исключение
    matrix&
    operator+=(const matrix& m)
    {
        // Проверка матриц на возможность сложения
        if ((rows != m.rows) || (cols != m.cols)) {
            throw std::runtime_error("Матрицы должны быть одного размера!");
        }

        // Прибавление значений строк матрицы правого операнда
        // к значениям строк матрицы левого операнда
        for (size_t row = 0; row < rows; row++) {
            // Прибавление элементов матрицы правого операнда
            // из столбца col обрабатываемой строки row
            // к соответствующим элементам матрицы левого операнда
            for (size_t col = 0; col < cols; col++) {
                data[row][col] += m[row][col];
            }
        }

        // Возврат ссылки на матрицу левого операнда
        return *this;
    }

    // Перегрузка оператора вычитания с присваиванием -=
    // Вычитает из элементов матрицы левого операнда
    // элементы матрицы правого операнда, если это возможно
    // Иначе выбрасывает исключение
    matrix&
    operator-=(const matrix& m)
    {
        // Проверка матриц на возможность вычитания
        if ((rows != m.rows) || (cols != m.cols)) {
            throw std::runtime_error("Матрицы должны быть одного размера!");
        }

        // Вычитание элементов строк матрицы равого операнда
        // из элементов строк матрицы левого операнда
        for (size_t row = 0; row < rows; row++) {
            // Вычитание элементов матрицы правого операнда
            // из столбца col обрабатываемой строки row
            // из соответствующих элементов матрицы левого операнда
            for (size_t col = 0; col < cols; col++) {
                data[row][col] -= m[row][col];
            }
        }

        // Возврат ссылки на матрицу левого операнда
        return *this;
    }

    // Перегрузка оператора умножения с присваиванием *=
    // Умножает каждый элемент матрицы левого операнда
    // на значение правого операнда
    matrix&
    operator*=(const T& val)
    {
        // Умножение элементов строк матрицы левого операнда
        // на значение правого операнда
        for (size_t row = 0; row < rows; row++) {
            // Умножение элементов матрицы из столбца col обрабатываемой
            // строки row на значение правого операнда
            for (size_t col = 0; col < cols; col++) {
                data[row][col] *= val;
            }
        }

        // Возврат ссылки на матрицу левого операнда
        return *this;
    }

    // Перегрузка оператора деления с присваиванием /=
    // Делит каждый элемент матрицы левого операнда
    // на значение правого операнда
    matrix&
    operator/=(const T& val)
    {
        // Деление элементов строк матрицы левого операнда
        // на значение правого операнда
        for (size_t row = 0; row < rows; row++) {
            // Деление элементов матрица из столбца col обрабатываемой
            // строки row на значение правого операнда
            for (size_t col = 0; col < cols; col++) {
                data[row][col] /= val;
            }
        }

        // Возврат ссылки на матрицу левого операнда
        return *this;
    }

    // Перегрузка оператора проверки равенства ==
    // Определяет равенство матриц левого и правого операндов
    // Проверяет возможность сравнения матриц
    // Выбрасывает исключение, если сравнение матриц невозможно
    friend bool
    operator==(const matrix& lhs, const matrix& rhs)
    {
        // Проверка возможности сравнения матриц
        if ((lhs.rows != rhs.rows) || (lhs.cols != rhs.cols)) {
            throw std::runtime_error("Матрицы должны быть одного размера!");
        }

        // Сравнение элементов строк матриц
        for (size_t row = 0; row < lhs.get_rows(); row++) {
            // Сравнение соответствующих элементов матриц
            // из столбца col обрабатываемой строки row
            for (size_t col = 0; col < lhs.get_cols(); col++) {
                if (lhs[row][col] != rhs[row][col]) {
                    return false;
                }
            }
        }

        return true;
    }

    // Перегрузка оператора проверки неравенства !=
    // Выполняет проверку, обратную оператору ==
    friend bool
    operator!=(const matrix& lhs, const matrix& rhs)
    { return !(lhs == rhs); }

    // Перегрузка оператора сравнения >
    // Проверяет, является ли матрица левого операнда больше
    // матрицы правого операнда, если это возможно
    // Иначе выбрасывает исключение
    friend bool
    operator>(const matrix& lhs, const matrix& rhs)
    {
        // Проверка возможности сравнения матриц
        if ((lhs.rows != rhs.rows) || (lhs.cols != rhs.cols)) {
            throw std::runtime_error("Матрицы должны быть одного размера!");
        }

        bool first = true;
        bool res   = lhs[0][0] > rhs[0][0];

        for (size_t row = 0; row < lhs.rows; row++) {
            for (size_t col = 0; col < lhs.cols; col++) {
                if (first) {
                    first = false;
                } else {
                    if (res != (lhs[row][col] > rhs[row][col])) {
                        throw std::runtime_error("Некорректное сравнение!");
                    }
                }
            }
        }

        // Возврат результата сравнения
        return res;
    }

    // Перегрузка оператора сравнения <
    // Проверяет, явлется ли матрица левого операнда меньше
    // матрицы правого операнда, если это возможно
    // Иначе выбрасывает исключение
    friend bool
    operator<(const matrix& lhs, const matrix& rhs)
    { return ((lhs != rhs) && !(lhs > rhs)); }

    // Перегрузка оператора сравнения >=
    // Выполняет комбинацию проверок > и ==
    friend bool
    operator>=(const matrix& lhs, const matrix& rhs)
    { return ((lhs == rhs) || (lhs > rhs)); }

    // Перегрузка оператора сравнения <=
    // Выполняет комбинацию проверок < и ==
    friend bool
    operator<=(const matrix& lhs, const matrix& rhs)
    { return ((lhs == rhs) || (lhs < rhs)); }

    // Перегрузка оператора умножения *
    // Возвращает резльтат умножения копии матрицы левого операнда
    // на значение правого операнда
    friend matrix
    operator*(matrix m, const T& value)
    {
        m *= value;
        return m;
    }

    // Перегрузка оператора деления /
    // Возвращает результат деления копии матрицы левого операнда
    // на значение правого операнда
    friend matrix
    operator/(matrix m, const T& value)
    {
        m /= value;
        return m;
    }

    // Перегрузка оператора умножения *
    // Возвращает результат умножения копии матрицы левого операнда
    // на матрицу правого операнда
    friend matrix
    operator*(matrix lhs, const matrix& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    // Перегрузка оператора деления /
    // Возвращает результат деления копии матрицы левого операнда
    // на матрицу правого операнда
    friend matrix
    operator/(matrix lhs, const matrix& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    // Перегрузка оператора сложения +
    // Возвращает результат сложения копии матрицы левого операнда
    // с матрицей правого операнда
    friend matrix
    operator+(matrix lhs, const matrix& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    // Перегрузка оператора вычитания -
    // Возвращает результат вычитания матрицы правого операнда
    // из копии матрицы левого операнда
    friend matrix
    operator-(matrix lhs, const matrix& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // Метод для изменения размерности матрицы
    void
    resize(size_t _rows, size_t _cols)
    {
        T** resized = new T*[_rows];
        for (size_t row = 0; row < _rows; row++) {
            resized[row] = new int[_cols];
        }

        for (size_t row = 0; row < _rows; row++) {
            for (size_t col = 0; col < _cols; col++) {
                if ((row < rows) && (col < cols)) {
                    resized[row][col] = data[row][col];
                }
            }
        }

        free_data();
        
        data = resized;
        rows = _rows;
        cols = _cols;
    }

    // Метод для транспонирования матрицы
    void
    transpose()
    {
        // временная матрица для записи результата транспонирования
        matrix<T> m(cols, rows);

        // транспонирование
        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                m[col][row] = data[row][col];
            }
        }

        // перезапись данных текущей матрицы на транспонированную
        *this = m;
    }

    // Метод для перевода элементов матрицы в текстовый вид
    // Возвращает ссылку на модифицированную строку
    std::string&
    out(std::string& str) const
    {
        for (size_t row = 0; row < rows; row++ ) {
            str += "| ";

            for (size_t col = 0; col < cols; col++) {
                str += to_string(data[row][col]) + " ";
            }

            str += "|\n";
        }

        return str;
    }

    // Метод, возвращающий количество строк матрицы
    size_t
    get_rows() const
    { return rows; }

    // Метод, возвращающий количество столбцов матрицы
    size_t
    get_cols() const
    { return cols; }

private:
    T**    data = nullptr;
    size_t rows = 0;
    size_t cols = 0;


    // Метод для освобождения памяти, занимаемой матрицей
    void
    free_data()
    {
        for (size_t row = 0; row < rows; row++) {
            delete[] data[row];
        }
        delete[] data;
    }

    // Метод для выделение памяти для хранения элементов матрицы
    void
    allocate()
    {
        data = new T*[rows];
        for (size_t row = 0; row < rows; row++) {
            data[row] = new T[cols];
        }
    }
};

