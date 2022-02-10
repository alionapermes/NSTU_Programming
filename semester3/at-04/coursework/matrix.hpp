#include <string>
#include <exception>
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
    // Стандартный конструктор
    // Ничего не выполняет
    // matrix() {}

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

        // Установка свойств матрицы
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

    // Перегрузка оператор сложения с присваиванием +=
    // Прибавляет к значениям матрицы левого операнда
    // значения матрицы правого операнда, если это возможно
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
            // Прибавление значений элементов из столбца col обрабатываемой
            // строки row к значениям соответствующих элементов матрицы
            // левого операнда
            for (size_t col = 0; col < cols; col++) {
                data[row][col] += m[row][col];
            }
        }

        // Возврат ссылки на матрицу левого операнда
        return *this;
    }

    matrix&
    operator-=(const matrix& m)
    {
        if ((rows != m.rows) || (cols != m.cols)) {
            throw std::runtime_error("Матрицы должны быть одного размера!");
        }

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                data[row][col] -= m[row][col];
            }
        }

        return *this;
    }

    matrix&
    operator*=(const T& val)
    {
        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                data[row][col] *= val;
            }
        }

        return *this;
    }

    matrix&
    operator/=(const T& val)
    {
        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                data[row][col] /= val;
            }
        }

        return *this;
    }

    friend bool
    operator==(const matrix& lhs, const matrix& rhs)
    {
        if ((lhs.rows != rhs.rows) || (lhs.cols != rhs.cols)) {
            throw std::runtime_error("Матрицы должны быть одного размера!");
        }

        for (size_t row = 0; row < lhs.get_rows(); row++) {
            for (size_t col = 0; col < lhs.get_cols(); col++) {
                if (lhs[row][col] != rhs[row][col]) {
                    return false;
                }
            }
        }

        return true;
    }

    friend bool
    operator!=(const matrix& lhs, const matrix& rhs)
    { return !(lhs == rhs); }
   
    friend bool
    operator>(const matrix& lhs, const matrix& rhs)
    {
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

        return res;
    }

    friend bool
    operator<(const matrix& lhs, const matrix& rhs)
    { return ((lhs != rhs) && !(lhs > rhs)); }

    friend bool
    operator>=(const matrix& lhs, const matrix& rhs)
    { return ((lhs == rhs) || (lhs > rhs)); }

    friend bool
    operator<=(const matrix& lhs, const matrix& rhs)
    { return ((lhs == rhs) || (lhs < rhs)); }

    friend matrix
    operator*(matrix m, const T& value)
    {
        m *= value;
        return m;
    }

    friend matrix
    operator/(matrix m, const T& value)
    {
        m /= value;
        return m;
    }

    friend matrix
    operator*(matrix lhs, const matrix& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend matrix
    operator/(matrix lhs, const matrix& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    friend matrix
    operator+(matrix lhs, const matrix& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend matrix
    operator-(matrix lhs, const matrix& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

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

    void
    transpose()
    {
        matrix<T> m(cols, rows);

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                m[col][row] = data[row][col];
            }
        }

        *this = m;
    }

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

    size_t
    get_rows() const
    { return rows; }

    size_t
    get_cols() const
    { return cols; }

private:
    T**    data = nullptr;
    size_t rows = 0;
    size_t cols = 0;


    void
    free_data()
    {
        for (size_t row = 0; row < rows; row++) {
            delete[] data[row];
        }
        delete[] data;
    }

    void
    allocate()
    {
        data = new T*[rows];
        for (size_t row = 0; row < rows; row++) {
            data[row] = new T[cols];
        }
    }
};

