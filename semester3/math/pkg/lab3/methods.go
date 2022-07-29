package lab3

import (
	"math"
	. "nstu/semester3/math/pkg/common"
)

func IterationsMethod(
	matrix *Matrix,
	free *Vector,
	eps float64,
) SolutionResult {
	count := 1
	base := NewVectorReserved(free.Length())
	_base := computeIteration(matrix, base, free)

	for i := 0; i < matrix.RowsCount(); i++ {
		for ; math.Abs(_base.Get(i)-base.Get(i)) >= eps; count++ {
			base = _base
			_base = computeIteration(matrix, _base, free)
		}
	}

	return SolutionResult{Variables: _base, IterationsCount: count}
}

func computeIteration(matrix *Matrix, base, free *Vector) *Vector {
	vars := NewVectorReserved(free.Length())

	for i := 0; i < matrix.RowsCount(); i++ {
		tmpRow, _ := Omit(matrix.Rows()[i], i)
		tmpBase, _ := Omit(base, i)
		prod, _ := Product(tmpRow, tmpBase)

		*vars.At(i) = (free.Get(i) - prod) / matrix.Pick(i, i)
	}

	return vars
}
