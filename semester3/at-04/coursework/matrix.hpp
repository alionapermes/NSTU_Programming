#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <exception>
#include <stdio.h>

using namespace std;


template <typename DT> // Data Type
class matrix
{
public:
    matrix()
    {
        rows = 0;
        cols = 0;
        data = nullptr;
    }

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

    ~matrix()
    {
        free_data();
    }

    friend ostream& operator<<(ostream& os, const matrix<DT>& m)
    {
        os << m.data_to_string();
        return os;
    }

    matrix<DT>& operator=(const matrix<DT>& m)
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

    friend bool operator==(const matrix<DT>& m1, const matrix<DT>& m2)
    {
        if ((m1.get_rows() != m2.get_rows())
            || (m1.get_cols() != m2.get_cols())
        ) { return false; }

        for (size_t row = 0; row < m1.get_rows(); row++) {
            for (size_t col = 0; col < m1.get_cols(); col++) {
                if ((m1[row][col] != m2[row][col])) {
                    return false;
                }
            }
        }

        return true;
    }

    friend matrix<DT> operator+(const matrix<DT>& m1, const matrix<DT>& m2)
    {
        if ((m1.rows != m2.rows) || (m1.cols != m2.cols)) {
            throw runtime_error("both of matrix must be the same size!");
        }

        matrix<DT> m(m1.rows, m1.cols);

        for (size_t row = 0; row < m.rows; row++) {
            for (size_t col = 0; col < m.cols; col++) {
                m[row][col] += m1[row][col] + m2[row][col];
            }
        }

        return m;
    }

    DT* operator[](size_t row) const
    {
        return data[row];
    }

    void resize(size_t _rows, size_t _cols)
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

    void print() const
    {
        printf(data_to_string().c_str());
    }

    const size_t& get_rows() const
    {
        return rows;
    }

    const size_t& get_cols() const
    {
        return cols;
    }

private:
    DT** data;
    size_t rows;
    size_t cols;

    string data_to_string() const
    {
        string str;

        for (size_t row = 0; row < rows; row++ ) {
            str += "| ";

            for (size_t col = 0; col < cols; col++) {
                str += to_string(data[row][col]) + " ";
            }

            str +="|\n";
        }

        return str;
    }

    void free_data()
    {
        for (size_t row = 0; row < rows; row++) {
            delete[] data[row];
        }
        delete[] data;
    }

    void allocate()
    {
        data = new DT*[rows];
        for (size_t row = 0; row < rows; row++) {
            data[row] = new DT[cols];
        }
    }
};
