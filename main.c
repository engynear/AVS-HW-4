#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int available_rooms = 30;  // Количество свободных номеров
pthread_mutex_t mutex;  // Мьютекс для блокировки доступа к количеству свободных номеров

// Количество клиентов (потоков). По умолчанию 100
int clients = 10;
// Время пребывания клиента в номере (слип потока) в секундах. По умолчанию 10 секунд
int stayTime = 3;

// Функция, выполняемая клиентами (потоками)
void* client_task(void* arg) {
    // Получаем номер клиента (потока)
    int clientNumber = (int)arg;
    // Состояние клиента: 0 - не на скамейке, 1 - на скамейке
    int on_bench = 0;
    while (1) {
        // Блокируем доступ к количеству свободных номеров мьютексом
        pthread_mutex_lock(&mutex);

        if (available_rooms > 0) {
            // Если клиент уже на скамейке, то выводит сообщение и встаёт со скамейки
            if (on_bench) {
                printf("Клиент встал со скамейки\n");
                on_bench = 0;
            }
            // Есть свободные номера, клиент забирает один из них
            available_rooms--;
            printf("Клиент №%d забронировал номер. Осталось свободных номеров: %d \n", clientNumber,
                   available_rooms);

            // Разблокируем мьютекс
            pthread_mutex_unlock(&mutex);
            // Клиент остаётся в номере заданное количество времени
            sleep(stayTime);
            pthread_mutex_lock(&mutex);
            // Клиент освобождает номер
            available_rooms++;
            printf("Клиент №%d освободил номер. Осталось свободных номеров: %d \n", clientNumber,
                   available_rooms);

            // Разблокируем мьютекс
            pthread_mutex_unlock(&mutex);
            break;
        } else {
            // Нет свободных номеров, клиент садится на скамейку и ждёт освобождения номера
            if (!on_bench) {
                printf("Нет свободных номеров, клиент №%d устроился на скамейке\n", clientNumber);
                on_bench = 1;
            }
            // Разблокируем мьютекс
            pthread_mutex_unlock(&mutex);

            // Клиент ждёт прежде чем проверить наличие свободных номеров
            sleep(1);
        }
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t threads[100];
    pthread_mutex_init(&mutex, NULL);

    // Ввод количества клиентов (потоков)
    if (argc > 1) {
        clients = atoi(argv[1]);
    } else {
        printf("Введите количество клиентов: ");
        scanf("%d", &clients);
    }
    if (clients < 1 || clients > 100) {
        clients = rand() % 100 + 1;
        printf(
            "Количество клиентов должно быть от 1 до 100. Установлено случайное значение в "
            "доступном диапозоне: %d \n",
            clients);
    }

    // Ввод времени, на которое клиент бронирует номер
    if (argc > 2) {
        stayTime = atoi(argv[2]);
    } else {
        printf("Введите время, на которое клиент бронирует номер (в секундах): ");
        scanf("%d", &stayTime);
    }
    if (stayTime < 1 || stayTime > 60) {
        // generate random number between 1 and 60
        stayTime = rand() % 60 + 1;
        printf(
            "Время, на которое клиент бронирует номер, должно быть от 1 до 60 секунд. Установлено "
            "случайное значение в доступном диапозоне: %d \n",
            stayTime);
    }

    // Клиенты отправляются в отель
    for (int i = 0; i < clients; i++) {
        pthread_create(&threads[i], NULL, client_task, (void*)i);
    }

    // Дожидаемся пока все клиенты переночуют в отеле (потоки завершатся)
    for (int i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Все клиенты переночевали в отеле \n");

    pthread_mutex_destroy(&mutex);
    return 0;
}
