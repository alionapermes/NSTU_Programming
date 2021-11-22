# РГР по программированию. 3 семестр.
## Вариант 13
---
| Способ обмена данными | Синхронизация | Обработка данных |
| --------------------- | ------------- | ---------------- |
| сокеты TCP | - | Замена одной пары символов в файле на другую |

## О программе
---
Данная работа представляет из себя клиент-серверное приложение для обработки текстовых файлов.

## Сборка
---
```sh
make all
```

## Использование
---
| Ключ | Описание |
| ---- | -------- |
| -t | Пара символов, которую требуется заменить. По умолчанию равен "FF". |
| -p | Пара символов, которой будет произведена замена. По умолчанию равен "#@". |

#### Примеры
```sh
./bin/server
```
```sh
./bin/client -t FF -p #@ file1.txt file2.txt
```
или
```sh
./bin/server
```
```sh
./bin/client file1.txt file2.txt
```
##### *__Примечание:__ для запуска приложения рекомендуется использовать разные окна (или вкладки) терминала, чтобы не смешивать вывод клиентской и серверной части*

## Моё рабочее окружение
---
- [Manjaro Linux]
- [VS Code]
- [GCC]
- [Make]

## Вопросы и предложения
---
##### Связаться со мной можно одним из следующих способов:
- [Telegram] - @alionapermes
- [VK] - @cpp_is_power
- [email] - cpp.is.power@gmail.com

[//]: # (http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)
   [Manjaro Linux]: <https://manjaro.org/>
   [VS Code]: <https://code.visualstudio.com/>
   [GCC]: <https://gcc.gnu.org/>
   [Make]: <https://ru.wikipedia.org/wiki/Make>
   [Telegram]: <https://t.me/alionapermes>
   [VK]: <https://vk.com/cpp_is_power>
   [email]: <https://www.google.com/intl/ru/gmail/about/#>
