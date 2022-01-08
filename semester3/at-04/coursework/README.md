# Курсовой проект

В файле `matrix.hpp` описан класс `matrix<T>`, представляющий матрицу произвольной размерности. Этот класс поддерживает следующие публичные методы:

* `void resize(size_t rows, size_t cols)`

* `void transpose()`

* `string& out(string& str) const`

* `size_t get_rows() const`

* `size_t get_cols() const`

А также некоторые операторы: `+, -, *, /, +=, -=, *=, /=, ==, !=, >, >=, <. <=`

И конструкторы:

* `matrix()`

* `matrix(size_t rows, size_t cols)`

* `matrix(const initializer_list<initializer_list<T>>& m)`

При некорректном использовании операторов может быть выброшено исключение `runtime_error`

## Сборка тестов

Перед сборкой убедитесь что у вас установлен GTest  
(`sudo pacman -S gtest` для Manjaro Linux)

```sh
mkdir build
cd build
cmake ..
make
```

## Запуск тестов

Находясь в директории coursework/build/

```sh
./test
```
