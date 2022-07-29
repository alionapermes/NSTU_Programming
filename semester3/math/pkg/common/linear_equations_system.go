package common

type (
	SolverFunc func(matrix *Matrix, free *Vector, eps float64) SolutionResult

	LinearEquationsSystem struct {
		Equations *Matrix
		Free      *Vector
		Eps       float64
	}

	SolutionResult struct {
		Variables       *Vector
		IterationsCount int
	}
)

func (sr *SolutionResult) Equals(other SolutionResult) bool {
	return (sr.IterationsCount == other.IterationsCount) &&
		sr.Variables.Equals(other.Variables)
}

func (les *LinearEquationsSystem) Solve(method SolverFunc) SolutionResult {
	return method(les.Equations, les.Free, les.Eps)
}
