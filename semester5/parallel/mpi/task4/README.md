# 4. Сортировка слиянием (merge sort)

Используемая технология: MPI

## Сборка

```sh
make
```

## Запуск

Запуск с параметрами по умолчанию:
```sh
make run
```

Ручной запуск:
```sh
mpirun [--mca opal_warn_on_missing_libcuda 0] -n <processes> ./out <array_size>
```

## Результаты
Сохранение результатов выполнения программы производится в файл `resuls.txt`

