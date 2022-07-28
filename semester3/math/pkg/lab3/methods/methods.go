package methods

import (
	"math"

	"nstu/semester3/math/pkg/common/vector"
)

func Iterations(
	matrix []*vector.Vector,
	free, base *vector.Vector,
	count int,
	eps float64,
) (*vector.Vector, int) {
	_base := vector.NewReserved(base.Length())

	for i := 0; i < free.Length(); i++ {
		tmpRow, _ := vector.Omit(matrix[i], i)
		tmpBase, _ := vector.Omit(base, i)
		prod, _ := vector.Product(tmpRow, tmpBase)

		*_base.At(i) = (free.Get(i) - prod) / matrix[i].Get(i)
	}

	for i := 0; i < free.Length(); i++ {
		if math.Abs(_base.Get(i)-base.Get(i)) >= eps {
			return Iterations(matrix, free, _base, count+1, eps)
		}
	}

	return _base, count + 1
}
