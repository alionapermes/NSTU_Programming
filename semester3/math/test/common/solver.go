package common

import (
	"nstu/semester3/math/pkg/common/matrix"
	"nstu/semester3/math/pkg/common/vector"
)

type Solver interface {
	Solve(matrix *matrix.Matrix, free *vector.Vector) SolutionResult
}
