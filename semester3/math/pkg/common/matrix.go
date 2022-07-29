package common

import (
	"errors"
	"math"
)

type Matrix struct {
	rows []*Vector
}

func NewMatrix(rows []*Vector) *Matrix {
	return &Matrix{rows: rows}
}

func (m *Matrix) IsDiagonallyDominant() (bool, error) {
	rowsCount, colsCount := m.Size()

	if rowsCount != colsCount {
		return false, errors.New("matrix isn't square")
	}

	for i := 0; i < rowsCount; i++ {
		var ii, sum float64

		for n := 0; n < rowsCount; n++ {
			if n == i {
				ii = math.Abs(m.Rows()[i].Get(n))
			} else {
				sum += math.Abs(m.Rows()[i].Get(n))
			}
		}

		if sum > ii {
			return false, nil
		}
	}

	return true, nil
}

func (m *Matrix) Rows() []*Vector {
	return m.rows
}

func (m *Matrix) RowsCount() int {
	return len(m.Rows())
}

func (m *Matrix) Size() (rowsCount int, colsCount int) {
	return m.RowsCount(), m.Rows()[0].Length()
}

func (m *Matrix) Pick(row, col int) float64 {
	return m.rows[row].Get(col)
}
