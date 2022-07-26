package vector

import "fmt"

type Vector struct {
	data []float64
}

func New(data []float64) *Vector {
	return &Vector{data: data}
}

func NewReserved(length int) *Vector {
	return &Vector{data: make([]float64, length)}
}

func Product(v1, v2 *Vector) (float64, error) {
	if v1.Length() != v2.Length() {
		return 0, fmt.Errorf("out of range")
	}

	var prod float64

	for i := 0; i < v1.Length(); i++ {
		prod += v1.Get(i) * v2.Get(i)
	}

	return prod, nil
}

func Omit(vec *Vector, index int) (*Vector, error) {
	if index >= vec.Length() {
		return nil, fmt.Errorf("out of range")
	}

	newVec := NewReserved(vec.Length() - 1)

	for i, item := range vec.Items() {
		if i == index {
			continue
		}
		newVec.Push(item)
	}

	return newVec, nil
}

func (vec *Vector) Accum() float64 {
	var sum float64

	for i := range vec.Items() {
		sum += vec.Get(i)
	}

	return sum
}

func (vec *Vector) Scale(x float64) {
	for i := range vec.Items() {
		*vec.At(i) *= x
	}
}

func (vec *Vector) Add(other *Vector) error {
	if vec.Length() != other.Length() {
		return fmt.Errorf("vectors must be the same length")
	}

	for i := range vec.Items() {
		*vec.At(i) += other.Get(i)
	}

	return nil
}

func (vec *Vector) Items() []float64 {
	return vec.data
}

func (vec *Vector) At(index int) *float64 {
	return &vec.Items()[index]
}

func (vec *Vector) Get(index int) float64 {
	return vec.Items()[index]
}

func (vec *Vector) Push(item float64) {
	vec.data = append(vec.Items(), item)
}

func (vec *Vector) Length() int {
	return len(vec.Items())
}
