#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <exception>
#include <cstring>

using namespace std;


template <typename DT> // Data Type
class matrix
{
public:
    matrix();

    matrix(size_t _rows, size_t _cols);

    matrix(const matrix& m);

    matrix(const initializer_list<initializer_list<DT>>& m);

    ~matrix();

    matrix& operator=(const matrix& m);

    DT* operator[](size_t row) const;

    matrix& operator+=(const matrix& m);

    matrix& operator-=(const matrix& m);

    matrix& operator*=(const DT& val);

    matrix& operator/=(const DT& val);

    matrix& operator+(matrix& m);

    template <typename T>
    friend bool operator==(const matrix<T>& m1, const matrix<T>& m2);

    template <typename T>
    friend bool operator!=(const matrix<T>& m1, const matrix<T>& m2);

    template <typename T>
    friend bool operator>(const matrix<T>& m1, const matrix<T>& m2);

    template <typename T>
    friend bool operator<(const matrix<T>& m1, const matrix<T>& m2);

    template <typename T>
    friend bool operator>=(const matrix<T>& m1, const matrix<T>& m2);

    template <typename T>
    friend bool operator<=(const matrix<T>& m1, const matrix<T>& m2);

    template <typename T>
    friend matrix<T> operator*(matrix<T> m, const matrix<T>& cm);

    template <typename T>
    friend matrix<T> operator/(matrix<T> m, const matrix<T>& cm);

    template <typename T>
    friend matrix<T> operator+(matrix<T> m, const matrix<T>& cm);

    template <typename T>
    friend matrix<T> operator-(matrix<T> m, const matrix<T>& cm);

    void resize(size_t _rows, size_t _cols);

    void transpose();

    string& out(string& str) const;

    const size_t& get_rows() const;

    const size_t& get_cols() const;

private:
    DT** data;
    size_t rows;
    size_t cols;


    void free_data();

    void allocate();
};


template <typename DT>
matrix<DT>::matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}

template <typename DT>
matrix<DT>::matrix(size_t _rows, size_t _cols)
{
    rows = _rows;
    cols = _cols;

    allocate();
}

template <typename DT>
matrix<DT>::matrix(const initializer_list<initializer_list<DT>>& m)
: matrix(m.size(), m.begin()->size())
{
    for (size_t row = 0; row < m.size(); row++) {
        auto m_row = m.begin() + row;

        for (size_t col = 0; col < m_row->size(); col++) {
            data[row][col] = *(m_row->begin() + col); // m[row][col];
        }
    }
}

template <typename DT>
matrix<DT>::matrix(const matrix& m)
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

template <typename DT>
matrix<DT>::~matrix()
{ free_data(); }

template <typename DT>
DT* matrix<DT>::operator[](size_t row) const
{ return data[row]; }

template <typename DT>
matrix<DT>& matrix<DT>::operator=(const matrix<DT>& m)
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

template <typename DT>
matrix<DT>& matrix<DT>::operator+=(const matrix<DT>& m)
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

template <typename DT>
matrix<DT>& matrix<DT>::operator-=(const matrix<DT>& m)
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

template <typename DT>
matrix<DT>& matrix<DT>::operator*=(const DT& val)
{
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            data[row][col] *= val;
        }
    }

    return *this;
}

template <typename DT>
matrix<DT>& matrix<DT>::operator/=(const DT& val)
{
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            data[row][col] /= val;
        }
    }

    return *this;
}

template <typename T>
bool operator==(const matrix<T>& m1, const matrix<T>& m2)
{
    if ((m1.rows != m2.rows) || (m1.cols != m2.cols)) {
        throw runtime_error("Матрицы должны быть одного размера!");
    }

    for (size_t row = 0; row < m1.get_rows(); row++) {
        for (size_t col = 0; col < m1.get_cols(); col++) {
            if (m1[row][col] != m2[row][col]) {
                return false;
            }
        }
    }

    return true;
}

template <typename T>
bool operator!=(const matrix<T>& m1, const matrix<T>& m2)
{ return !(m1 == m2); }

template <typename T>
bool operator>(const matrix<T>& m1, const matrix<T>& m2)
{
    if ((m1.rows != m2.rows) || (m1.cols != m2.cols)) {
        throw runtime_error("Матрицы должны быть одного размера!");
    }

    bool first = true;
    bool res   = m1[0][0] > m2[0][0];

    for (size_t row = 0; row < m1.rows; row++) {
        for (size_t col = 0; col < m1.cols; col++) {
            if (first) {
                first = false;
            } else {
                if (res != (m1[row][col] > m2[row][col])) {
                    throw runtime_error("Некорректное сравнение!");
                }
            }
        }
    }

    return res;
}

template <typename T>
bool operator<(const matrix<T>& m1, const matrix<T>& m2)
{ return ((m1 != m2) && !(m1 > m2)); }

template <typename T>
bool operator>=(const matrix<T>& m1, const matrix<T>& m2)
{ return ((m1 == m2) || (m1 > m2)); }

template <typename T>
bool operator<=(const matrix<T>& m1, const matrix<T>& m2)
{ return ((m1 == m2) || (m1 < m2)); }

template <typename T>
matrix<T> operator*(matrix<T> m, const T& cm)
{
    m *= cm;
    return m;
}

template <typename T>
matrix<T> operator/(matrix<T> m, const T& cm)
{
    m /= cm;
    return m;
}

template <typename T>
matrix<T> operator+(matrix<T> m, const matrix<T>& cm)
{
    m += cm;
    return m;
}

template <typename T>
matrix<T> operator-(matrix<T> m, const matrix<T>& cm)
{
    m -= cm;
    return m;
}

template <typename DT>
void matrix<DT>::resize(size_t _rows, size_t _cols)
{
    DT** resized = new DT*[_rows];
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

template <typename DT>
void matrix<DT>::transpose()
{
    matrix<DT> m(cols, rows);

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            m[col][row] = data[row][col];
        }
    }

    *this = m;
}

template <typename DT>
const size_t& matrix<DT>::get_rows() const
{ return rows; }

template <typename DT>
const size_t& matrix<DT>::get_cols() const
{ return cols; }

template <typename DT>
string& matrix<DT>::out(string& str) const
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

template <typename DT>
void matrix<DT>::free_data()
{
    for (size_t row = 0; row < rows; row++) {
        delete[] data[row];
    }
    delete[] data;
}

template <typename DT>
void matrix<DT>::allocate()
{
    data = new DT*[rows];
    for (size_t row = 0; row < rows; row++) {
        data[row] = new DT[cols];
    }
}
