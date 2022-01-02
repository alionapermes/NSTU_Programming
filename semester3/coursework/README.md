# РГР по программированию. 3 семестр
## Вариант 13
---
| Способ обмена данными | Синхронизация | Обработка данных |
| --------------------- | ------------- | ---------------- |
| сокеты TCP | - | Замена одной пары символов в файле на другую |

## О программе
---
Данная работа представляет из себя клиент-серверное приложение для обработки текстовых файлов на стороне сервера. В качестве ответа клиенту возвращается число выполненных замен в файле.

Поскольку это демонстрационный пример, в программе действуют следующие ограничения:
* Максимальное количество обрабатываемых файлов - 16 (17-ый и последующие файлы будут проигнорированны)
* Максимальное количество символов в одном файле - 127
* Максимальная длина имени/пути файла - 255

## Сборка
Для корректной сборки проекта необходимо изменить имя пользователя в unit-файле и путь к исполняемому файлу
#### Находясь в директории `coursework/src/server`
```sh
vim myserver.service
```
```
[Service]
    ExecStart=/home/<username>/<path_to_repo>/NSTU_Programming/semester3/coursework/bin/server/server
    WorkingDirectory=/home/<username>/<path_to_repo>/NSTU_Programming/semester3/coursework/bin/server
```
#### Находясь в директории `coursework/src`
```sh
sudo make all
```

## Использование
---
| Ключ | Описание |
| ---- | -------- |
| -t | Пара символов, которую требуется заменить. По умолчанию "FF". |
| -p | Пара символов, которой будет произведена замена. По умолчанию "#@". |
| -f | Имя файла для обработки. Указывается для каждого файла. |
| -h | Информация об использовании. |

### Пример
```sh
git clone https://github.com/alionapermes/NSTU_Programming.git
```
```sh
cd NSTU_Programming/semester3/coursework/src/server
```
```sh
vim myserver.service
```
```sh
[Service]
    ExecStart=/home/linadl/projects/c/NSTU_Programming/semester3/coursework/bin/server/server
    WorkingDirectory=/home/linadl/projects/c/NSTU_Programming/semester3/coursework/bin/server
```
```sh
cd ..
```
```sh
sudo make all
```
```sh
sudo systemctl daemon-reload
```
##### Вид каталога `coursework/bin` после сборки
```
coursework
└── bin
    ├── client
    │   └── client
    └── server
        ├── file1.txt
        ├── file2.txt
        ├── funclib.so
        ├── processor
        └── server
```

#### __Запуск сервера__
```sh
sudo systemctl start myserver
```
#### __Запуск клиента__
##### Находясь в директории `coursework/bin/client`
```sh
./client -t "FF" -p "#@" -f file1.txt -f file2.txt
```
или
```sh
./client -f file1.txt -f file2.txt
```
##### __Примечания:__
 * *Для запуска приложения рекомендуется использовать разные окна (или вкладки) терминала, чтобы не смешивать вывод клиентской и серверной части*
 * *Некоторые символы терминал может интерпретировать особым образом, поэтому стоит ставить кавычки*
 * *Порт, используемый по умолчанию - 5000*

## Рабочее окружение и инструменты
---
- [Manjaro Linux]
- [VS Code]
- [GCC]
- [Make]

## Вопросы и предложения
---
##### Связаться со мной можно одним из следующих способов:
- [Telegram] - @alionapermes
- [VK] - @boolka_breada
- [email] - alionapermes@gmail.com

[//]: # (http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)
   [Manjaro Linux]: <https://manjaro.org/>
   [VS Code]: <https://code.visualstudio.com/>
   [GCC]: <https://gcc.gnu.org/>
   [Make]: <https://ru.wikipedia.org/wiki/Make>
   [Telegram]: <https://t.me/alionapermes>
   [VK]: <https://vk.com/boolka_breada>
   [email]: <https://www.google.com/intl/ru/gmail/about/#>
