package common

import (
	"fmt"
	"math"
)

type Vector struct {
	data []float64
}

func NewVector(data []float64) *Vector {
	return &Vector{data: data}
}

func NewVectorReserved(length int) *Vector {
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

func Omit(v *Vector, index int) (*Vector, error) {
	if index >= v.Length() {
		return nil, fmt.Errorf("out of range")
	}

	newVec := NewVectorReserved(v.Length() - 1)

	for i, item := range v.Items() {
		if i == index {
			continue
		}
		newVec.Push(item)
	}

	return newVec, nil
}

func (v *Vector) Accum() float64 {
	var sum float64

	for i := range v.Items() {
		sum += v.Get(i)
	}

	return sum
}

func (v *Vector) Scale(x float64) {
	for i := range v.Items() {
		*v.At(i) *= x
	}
}

func (v *Vector) Add(other *Vector) error {
	if v.Length() != other.Length() {
		return fmt.Errorf("vtors must be the same length")
	}

	for i := range v.Items() {
		*v.At(i) += other.Get(i)
	}

	return nil
}

func (v *Vector) Items() []float64 {
	return v.data
}

func (v *Vector) At(index int) *float64 {
	return &v.Items()[index]
}

func (v *Vector) Get(index int) float64 {
	return v.Items()[index]
}

func (v *Vector) Push(item float64) {
	v.data = append(v.Items(), item)
}

func (v *Vector) Length() int {
	return len(v.Items())
}

func (v *Vector) Equals(other *Vector) bool {
	if v.Length() != other.Length() {
		return false
	}

	for i := range v.Items() {
		if v.Get(i) != other.Get(i) {
			return false
		}
	}

	return true
}

func (v *Vector) RoundItems(accur float64) {
	x := math.Pow(10, accur)

	for i := range v.Items() {
		*v.At(i) = math.Round(v.Get(i)*x) / x
	}
}
