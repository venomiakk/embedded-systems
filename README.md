# embedded-systems
Raspberry Pi Pico RC Car

- [x] bezprzewodowa łączność (sterowanie) - serwer http, protokół lwip (chip Infineon CYW43439) ***nie liczy sie jako funkcjonalnosc...***
- [x] poruszanie - silniczek + mostek H (PWM)
- [x] skręcanie - serwo (PWM)
- [x] głośnik - pwm, dac, filtr dolnoprzepustowy ***w tym momencie pwm i granie pojedynczych czestliwosci***
- [ ] czujnik odległości ir - GPIO ***jest cyfrowy wiec odczyt 0 lub 1, wiec to sie chyba nie liczy do funkcjonalnosci***
- [ ] Czujnik natężenia światła - I2C ***w tym momencie dziala tylko na GPIO/(ADC?) (bo nie obsluguje I2C)***
- [ ] diody - GPIO, PWM
- [ ] wyświetlacz LCD - I2C
