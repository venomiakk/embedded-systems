#include "ssi.h"
#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "accelerometer.h"
#include "lightsensor.h"

// SSI tags - tag length limited to 8 bytes by default
const char *ssi_tags[] = {"led", "accx", "accy", "accz", "light"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
  size_t printed;
  switch (iIndex)
  {
  case 0: // led
  {
    bool led_status = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
    if (true == led_status)
    {
      printed = snprintf(pcInsert, iInsertLen, "ON");
    }
    else
    {
      printed = snprintf(pcInsert, iInsertLen, "OFF");
    }
  }
  break;
  case 1: // accx
  {
    float x, y, z;
    adxl345_read_data(&x, &y, &z);
    printed = snprintf(pcInsert, iInsertLen, "%f", x);
  }
  break;
  case 2: // accy
  {
    float x, y, z;
    adxl345_read_data(&x, &y, &z);
    printed = snprintf(pcInsert, iInsertLen, "%f", y);
  }
  break;
  case 3: // accz
  {
    float x, y, z;
    adxl345_read_data(&x, &y, &z);
    printed = snprintf(pcInsert, iInsertLen, "%f", z);
  }
  break;
  case 4: // light
  {
    uint16_t light_value = get_light_value();
    printed = snprintf(pcInsert, iInsertLen, "%d", light_value);
  }
  default:
    printed = 0;
    break;
  }

  return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init()
{
  // Initialise ADC (internal pin)
  // adc_init();
  // adc_set_temp_sensor_enabled(true);
  // adc_select_input(4);

  http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}