# **Отчет о выполнении Домашнего задания №4**

## *Выполнил* Миронов Павел Андреевич БПИ212

## *Вариант 12*

---

## На 4 балла

### Условие задачи

В гостинице 30 номеров, клиенты гостиницы снимают номер на одни или несколько суток. Если в гостинице нет свободных номеров, клиенты не уходят, а устраиваются на рядом с гостиницей на скамейках и ждут, пока любой номеров не освободится. Создать многопоточное приложение, моделирующее работу гостиницы.


### Модель вычисления

Программа использует модель вычисления **Взаимодействующие равные**

А конкретно модель "портфель задач".
Программа использует разделяемую переменную, доступ к которой в один момент времени имеет только один процесс.
В этой переменной хранится количество доступных клиентам (потокам) номеров.

### Входные данные

При запуске пользователь может передать входные данные через аргументы командой строки:

1. Первый аргумент: количество клиентов гостиницы (потоков). Диапозон значений от 1 до 100.
2. Второй аргумент: время в секундах, на которое клиент останавливается в номере. Диапозон значений от 1 до 60 секунд.

Также если один или оба аргументы не указаны при запуске, программа предложит ввести данные с помощью консольного ввода.

Если данные не соответствуют диапозону значений, то будут автоматически сгенерированы значения в доступном диапозоне.

### Приложение

Консольное приложение написано на языке C с использованием библиотеки PThread. Исходный код программы можно найти [здесь](main.c).

### Ввод данных в приложение c помощью консоли

Выше в пункте [входные данные](#входные-данные) описана возможность ввода данных с помощью консоли.

### Результаты работы приведены в отчете

Пример работы програмы с параметрами 10 и 3 (клиентов и времени остановки)
```
Клиент №0 забронировал номер. Осталось свободных номеров: 29
Клиент №1 забронировал номер. Осталось свободных номеров: 28
Клиент №2 забронировал номер. Осталось свободных номеров: 27
Клиент №3 забронировал номер. Осталось свободных номеров: 26
Клиент №4 забронировал номер. Осталось свободных номеров: 25
Клиент №5 забронировал номер. Осталось свободных номеров: 24
Клиент №6 забронировал номер. Осталось свободных номеров: 23
Клиент №7 забронировал номер. Осталось свободных номеров: 22
Клиент №8 забронировал номер. Осталось свободных номеров: 21
Клиент №9 забронировал номер. Осталось свободных номеров: 20
Клиент №0 освободил номер. Осталось свободных номеров: 21
Клиент №2 освободил номер. Осталось свободных номеров: 22
Клиент №1 освободил номер. Осталось свободных номеров: 23
Клиент №4 освободил номер. Осталось свободных номеров: 24
Клиент №3 освободил номер. Осталось свободных номеров: 25
Клиент №5 освободил номер. Осталось свободных номеров: 26
Клиент №7 освободил номер. Осталось свободных номеров: 27
Клиент №8 освободил номер. Осталось свободных номеров: 28
Клиент №6 освободил номер. Осталось свободных номеров: 29
Клиент №9 освободил номер. Осталось свободных номеров: 30
Все клиенты переночевали в отеле
```

## на 5 баллов

### Комментарии

Программа содержит подробные комментарии на русском языке.
Исходный код программы с комментариями можно найти [здесь](main.c).


### Сценарий поведения потоковой единицы

Каждый клиент (поток) приходит в гостиницу и проверяет наличие свободных номеров (разделяемую переменную). Если в гостинице есть свободные номера, то клиент бронирует его и останавливается в нём на заданное количество секунд.
Если нет свободных номеров, то клиент садится на лавочку и ожидает освобождения номеров, каждую секунду проверяет наличие свободных.

## На 6 баллов

### Описание работы программы

Программа получает входные данные: количество клиентов (поток) и время остановки клиентов в номере. Далее каждый клиент (поток) приходит в гостиницу и пытается забронировать номер. Если есть свободные номера, то бронирует на заданное время. Если нет, то ждёт на лавочке, пока свободные номера не появятся.
Когда все клиенты поживут в гостинице - программа завершается.

Подробные алгоритмы работы описаны [здесь](#входные-данные) (входные данные), [здесь](#модель-вычисления)(модель вычисления), и [здесь](#сценарий-поведения-потоковой-единицы) (сценарий потока)

### Ввод данных из командной строки

Ввод данных организован с помощью параметров командой строки, описанными [здесь](#входные-данные).

## На 7 баллов

### Ввод и вывод данных при помощи файлов

Ввод данных из файла доступен с помощью перенаправления потоков в OC Linux.
Входной файл должен содержать два целых числа:
1. Количество потоков в диапозоне от 1 до 100
2. Время остановки клиента в номере в диапозоне от 1 до 60

Результаты работы программы доступны при помощи перенаправления потоков вывода в OC Linux.

Примеры входных данных находятся [здесь](./input/).
Примеры соответсвующих выходных данных находятся [здесь](./output/).

## На 8 баллов

### Генератор значений

При отсутствии входных данных или их несоотвествии необходимому диапозону - число потоков и время остановки клиента в номере генерируется автоматически в допустимом диапозоне значений.