#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"
#include "servo.h"
// #include "motor.h"
#include "irsensor.h"
#include "lightsensor.h"
#include "speaker.h"

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
    while (true == cyw43_arch_wifi_connect_timeout_ms(wifiSSID, wifiPASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        (void)printf("\nAttempting to connect...");
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

    setServo(15, 1500);

    // binary_detection();
    // measure_light();
    init_pwm_speaker();
    // play_tone(440.0f, 500);

    while (true)
    {
    }
}