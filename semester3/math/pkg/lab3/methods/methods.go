package methods

import (
	"math"

	. "nstu/semester3/math/pkg/common"
)

func Iterations(
	matrix []*Vector,
	free, base *Vector,
	count int,
	eps float64,
) (*Vector, int) {
	_base := NewVectorReserved(base.Length())

	for i := 0; i < free.Length(); i++ {
		tmpRow, _ := Omit(matrix[i], i)
		tmpBase, _ := Omit(base, i)
		prod, _ := Product(tmpRow, tmpBase)

		*_base.At(i) = (free.Get(i) - prod) / matrix[i].Get(i)
	}

	for i := 0; i < free.Length(); i++ {
		if math.Abs(_base.Get(i)-base.Get(i)) >= eps {
			return Iterations(matrix, free, _base, count+1, eps)
		}
	}

	return _base, count + 1
}
