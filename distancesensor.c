#include "distancesensor.h"
#include "pico/stdlib.h"
#include <stdio.h>

void init_distance_sensor(void)
{
    gpio_init(ECHO);
    gpio_set_dir(ECHO, GPIO_IN);
    gpio_pull_up(ECHO);

    gpio_init(TRIG);
    gpio_set_dir(TRIG, GPIO_OUT);
    gpio_put(TRIG, 0);
}

float get_distance(void)
{

    const int timeout = 100000;
    int iter = 0;

    gpio_put(TRIG, 1);
    sleep_us(10);
    gpio_put(TRIG, 0);

    while (gpio_get(ECHO) == 0) // Czekaj na początek wysokiego impulsu
    {
        iter++;
        if (iter >= timeout)
        {
            return -1.0f;
        }
    }
    uint64_t start_time = time_us_64();

    int iter2 = 0;
    while (gpio_get(ECHO) == 1) // Czekaj na koniec wysokiego impulsu
    {
        iter2++;
        if (iter2 >= timeout)
        {
            return -1.0f;
        }
    }
    uint64_t end_time = time_us_64();

    uint64_t duration = end_time - start_time; // Czas trwania wysokiego impulsu w mikrosekundach

    // Konwersja na sekundy i obliczenie odległości (prędkość dźwięku to około 343 metrów na sekundę)
    float distance = (float)duration / 1000000.0f * 343.0f / 2.0f;
    // (void)printf("Odleglosc: %f\n", distance);
    return distance;
}
