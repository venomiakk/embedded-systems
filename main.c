#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"
#include "servo.h"
#include "motor.h"
#include "lightsensor.h"
#include "speaker.h"
#include "diodes.h"
#include "distancesensor.h"
#include "accelerometer.h"
#include "lcd.h"
#include <stdbool.h>

int main(void)
{

    /*
    WIFI Credentials
    */
    const char wifiSSID[] = "";
    const char wifiPASSWORD[] = "";

    /*
        Initialise all needed resources
    */

    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    /*
        Attempting to connect to the WiFI
    */
    bool connection_status = cyw43_arch_wifi_connect_timeout_ms(wifiSSID, wifiPASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000);
    while (true == connection_status)
    {
        (void)printf("\nAttempting to connect...");
        connection_status = cyw43_arch_wifi_connect_timeout_ms(wifiSSID, wifiPASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000);
    }

    /*
        Connected to the newtwork
    */
    (void)printf("\nConnected to the network.");

    /*
        Initialise HTTP server
    */
    httpd_init();
    (void)printf("\nHTTP Server initialised!\n");

    ssi_init();
    (void)printf("\nSSI Handler inistialised!\n");

    cgi_init();
    (void)printf("\nCGI Handler initialised!\n");

    /*
        Initialise components
    */
    setServo(15, 1500);

    init_h_bridge(MOTOR_ACW_PIN, MOTOR_CW_PIN, MOTOR_PWM_PIN);

    // Akcelerometr
    bool adxl345_status = false;
    init_i2c0();
    adxl345_status = init_adxl345();

    init_light_sensor();

    init_diode22();
    init_pwm_led();

    init_distance_sensor();
    init_pwm_speaker();

    play_melody();

    uint16_t light_value;
    uint16_t light_trigger = 3500;
    float accelX;
    float accelY;
    float accelZ;
    float distance;
    uint16_t fill = 0;
    while (true)
    {
        // Kontrolowanie swiatla
        light_value = get_light_value();
        (void)printf("Swiatlo: %d\n", light_value);
        if (light_trigger <= light_value)
        {
            fill = light_value - light_trigger;
            set_pwm_led(fill);
        }
        else
        {
            set_pwm_led(0);
        }

        sleep_ms(200);

        // Kontrolowanie glosnika
        distance = get_distance();
        (void)printf("Distance: %f\n", distance);
        if ((distance < 0.20f) && (distance >= 0.10f))
        {
            dst_warning1();
            (void)printf("Distance: %f\n", distance);
        }
        else if ((distance < 0.10f) && (distance >= 0.0f))
        {
            dst_warning2();
            (void)printf("Distance: %f\n", distance);
        }
        else
        {
        }

        sleep_ms(200);

        // Kontrolowanie przechylenia
        if (true == adxl345_status)
        {
            adxl345_read_data(&accelX, &accelY, &accelZ);
            (void)printf("X: %f, Y: %f, Z: %f\n", accelX, accelY, accelZ);
            if ((accelX > 0.5) || (accelX < -0.5) || (accelY > 0.5) || (accelY < -0.5))
            {
                diode_22_mode(1);
            }
            else
            {
                diode_22_mode(0);
            }
        }
        else
        {
            int state = gpio_get(DIODE_22);
            if (state == 1)
            {
                gpio_put(DIODE_22, 0);
            }
            else
            {
                gpio_put(DIODE_22, 1);
            }
        }

        sleep_ms(200);
    }

    return 0;
}