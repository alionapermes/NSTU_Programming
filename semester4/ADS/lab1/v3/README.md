# Лабораторная работа по АиСД №1. Вариант 3

Односвязная структура данных на базе массива с индексными указателями

## Сборка тестов

Убедитесь, что у вас установлен пакетный менеджер 
[conan](https://conan.io) и произведены его 
необходимые базовые настройки:  
```sh
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
```

```sh
mkdir build
cd build
conan install ..
cmake ..
make
```

## Запуск тестов

Находясь в v3/build  
`./bin/test`

