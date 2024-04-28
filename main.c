#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"
#include "servo.h"
#include "motor.h"


/*
    WIFI Credentials
*/
const char WIFI_SSID[] = "WLAN1_home";
const char WIFI_PASSWORD[] = "rX16Hba7HvZ";

int main(void)
{
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
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("\nAttempting to connect...");
    }

    /*
        Connected to the newtwork
    */
    printf("\nConnected to the network.");

    /*
        Initialise HTTP server
    */
    httpd_init();
    printf("\nHTTP Server initialised!");

    ssi_init();
    printf("\nSSI Handler inistialised!");

    cgi_init();
    printf("\nCGI Handler initialised!");

    setServo(15,1500);

    while (1)
        ;
}