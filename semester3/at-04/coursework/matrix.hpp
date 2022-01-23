#include <string>
#include <exception>
#include <cstring>

using namespace std;


template <typename T>
class matrix
{
public:
    matrix() {}

    matrix(size_t _rows, size_t _cols)
    {
        rows = _rows;
        cols = _cols;

        allocate();
    }

    matrix(const matrix& m)
    {
        rows = m.rows;
        cols = m.cols;
        
        allocate();

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                data[row][col] = m[row][col];
            }
        }
    }

    matrix(const initializer_list<initializer_list<T>>& m)
    : matrix(m.size(), m.begin()->size())
    {
        for (size_t row = 0; row < m.size(); row++) {
            auto m_row = m.begin() + row;

            for (size_t col = 0; col < m_row->size(); col++) {
                data[row][col] = *(m_row->begin() + col); // m[row][col];
            }
        }
    }

    ~matrix()
    { free_data(); }

    matrix&
    operator=(const matrix& m)
    {
        free_data();

        rows = m.rows;
        cols = m.cols;

        allocate();

        for (auto row = 0; row < rows; row++) {
            for (auto col = 0; col < cols; col++) {
                data[row][col] = m[row][col];
            }
        }

        return *this;
    }

    T*
    operator[](size_t row) const
    { return data[row]; }

    matrix&
    operator+=(const matrix& m)
    {
        if ((rows != m.rows) || (cols != m.cols)) {
            throw runtime_error("both of matrix must be the same size!");
        }

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                data[row][col] += m[row][col];
            }
        }

        return *this;
    }

    matrix&
    operator-=(const matrix& m)
    {
        if ((rows != m.rows) || (cols != m.cols)) {
            throw runtime_error("both of matrix must be the same size!");
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
            throw runtime_error("Матрицы должны быть одного размера!");
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
            throw runtime_error("Матрицы должны быть одного размера!");
        }

        bool first = true;
        bool res   = lhs[0][0] > rhs[0][0];

        for (size_t row = 0; row < lhs.rows; row++) {
            for (size_t col = 0; col < lhs.cols; col++) {
                if (first) {
                    first = false;
                } else {
                    if (res != (lhs[row][col] > rhs[row][col])) {
                        throw runtime_error("Некорректное сравнение!");
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

    string&
    out(string& str) const
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

