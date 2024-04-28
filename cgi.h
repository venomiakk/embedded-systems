#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "servo.h"
#include "motor.h"
#include "hardware/pwm.h"

const int SERVO_PIN = 15;
int SERVO_POS = 1500;
const int MOTOR_PWM_PIN=16;
const int MOTOR_CW_PIN=17;
const int MOTOR_ACW_PIN=18;

// CGI handler which is run when a request for /led.cgi is detected
const char *cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if an request for LED has been made (/led.cgi?led=x)
    if (strcmp(pcParam[0], "led") == 0)
    {
        // Look at the argument to check if LED is to be turned on (x=1) or off (x=0)
        if (strcmp(pcValue[0], "0") == 0)
        {
            printf("\nLED OFF");
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
        else if (strcmp(pcValue[0], "1") == 0)
        {
            printf("\nLED ON");
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
    }

    // Send the index page back to the user
    return "/index.shtml";
}


const char *cgi_servo_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {

    if (strcmp(pcParam[0], "servo") == 0)
    {
        if (strcmp(pcValue[0], "p") == 0)
        {
            if (SERVO_POS != 600)
            {
                printf("prawo\n");
                SERVO_POS = 600;
                setMillis(SERVO_PIN, SERVO_POS);
            }
            
        } else if (strcmp(pcValue[0], "l") == 0)
        {
            if (SERVO_POS != 2400)
            {
                printf("lewo\n");
                SERVO_POS = 2400;
                setMillis(SERVO_PIN, SERVO_POS);
            }
            
        } else if (strcmp(pcValue[0], "s") == 0)
        {
            if (SERVO_POS != 1500)
            {
                printf("lewo\n");
                SERVO_POS = 1500;
                setMillis(SERVO_PIN, SERVO_POS);
            }
        }
        
        
        
    }
    return "/index.shtml";
}

const char *cgi_motor_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {

    if (strcmp(pcParam[0], "motor") == 0)
    {
        init_h_bridge(MOTOR_ACW_PIN, MOTOR_CW_PIN, MOTOR_PWM_PIN);
        uint slice = pwm_gpio_to_slice_num(MOTOR_PWM_PIN);
        uint chan = pwm_gpio_to_channel(MOTOR_PWM_PIN);
        if (strcmp(pcValue[0], "p") == 0)
        {
            printf("jedziemy do przodu\n");
            gpio_put(MOTOR_CW_PIN, 1);
            gpio_put(MOTOR_ACW_PIN, 0);
            uint wrap = motor_move(slice, chan, 100, 75);
            pwm_set_enabled(slice,true);
            
        } else if (strcmp(pcValue[0], "t") == 0)
        {
            printf("jedziemy do tylu\n");
            gpio_put(MOTOR_CW_PIN, 0);
            gpio_put(MOTOR_ACW_PIN, 1);
            uint wrap = motor_move(slice, chan, 100, 75);
            pwm_set_enabled(slice,true);
            
        } else if (strcmp(pcValue[0], "s") == 0)
        {
            printf("STOP\n");
            gpio_put(MOTOR_CW_PIN, 0);
            gpio_put(MOTOR_ACW_PIN, 0);
            motor_move(slice, chan, 0, 0);
            pwm_set_enabled(slice,false);
        }
        
        
        
    }
    return "/index.shtml";
}
// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {// Html request for "/led.cgi" triggers cgi_handler
     "/led.cgi", cgi_led_handler},
     {"/servo.cgi", cgi_servo_handler},
     {"/motor.cgi", cgi_motor_handler}
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 3);
}