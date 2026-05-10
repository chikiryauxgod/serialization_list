# Serialization List

Реализуется структура:

```cpp
struct ListNode {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr;
    std::string data;
};
````


## Возможности

* Чтение списка из текстового файла
* Построение двусвязного списка в памяти
* Поддержка `rand`-ссылок
* Сериализация в бинарный файл
* Десериализация обратно в структуру
* Проверка корректности через unit-тесты (GoogleTest)


## Формат входного файла (`inlet.in`)

Каждая строка:

```
<data>;<rand_index>
```

* `data` — строка (UTF-8, может содержать пробелы и символы)
* `rand_index` — индекс узла или `-1`

Пример:

```
apple;2
banana;-1
carrot;1
```


## Бинарный формат (`outlet.out`)

Сохраняется:

1. количество узлов
2. каждый узел:

   * длина строки
   * строка
   * индекс rand (`int32`)

## Сборка

```bash
cmake -S . -B build
cmake --build build
```

## Запуск

```bash
./build/app
```

## Тесты

```bash
./build/tests/run_tests
```

## Структура проекта

``` fs
app/            - main
include/        - заголовки
src/            - реализация
tests/          - unit tests (GoogleTest)
build/          - сборка (не в репозитории)
```


