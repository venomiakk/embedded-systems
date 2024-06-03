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

/*!
 *  @brief    Krótko co procedura robi.
 *  @param nazwa  parametru 1
 *             opis parametru 1
 *  @param nazwa  parametru 2
 *             opis parametru 2
 *  @param nazwa  parametru n
 *             opis parametru n
 *  @returns  np. tak: true on success, false otherwise
 *  @side effects:
 *            efekty uboczne
 */

int main(void)
{
    /*
    WIFI Credentials
    */
    const char wifiSSID[] = "WLAN1_home";
    const char wifiPASSWORD[] = "rX16Hba7HvZ";

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
    //! while (cyw43_arch_wifi_connect_timeout_ms(wifiSSID, wifiPASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
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
    init_i2c0();
    init_adxl345();

    init_light_sensor();

    // initi_diodes();
    init_pwm_led();

    init_distance_sensor();
    init_pwm_speaker();

    lcd_init();
    lcd_draw_text(10, 10, "Hello, World!", 0xFFFF, 0x0000);

    play_melody();

    uint16_t light_value;
    uint16_t light_trigger = 3500;
    float x;
    float y;
    float z;
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

        sleep_ms(500);

        // Kontrolowanie glosnika
        distance = get_distance();
        (void)printf("Distance: %f\n", distance);
        if (distance < 0.15 && distance > 0)
        {
            dst_warning();
            (void)printf("Distance: %f\n", distance);
        }

        sleep_ms(500);

        // Kontrolowanie predkosci pojazdu (przyspieszenie)
    }

    return 0;
}