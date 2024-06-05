#ifndef CGI_H
#define CGI_H

/**
 * @brief Funkcja obslugujaca wbudowany LED
 * @param iIndex Indeks CGI
 * @param iNumParams  Liczba parametrow
 * @param pcParam  Tablica parametrow
 * @param pcValue  Tablica wartosci parametrow
 * @return
 */
extern const char *cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

/**
 * @brief Funkcja obslugujaca serwo
 * @param iIndex Indeks CGI
 * @param iNumParams  Liczba parametrow
 * @param pcParam  Tablica parametrow
 * @param pcValue  Tablica wartosci parametrow
 * @return
 */
extern const char *cgi_servo_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

/**
 * @brief Funkcja obslugujaca mostek H i silnik
 * @param iIndex Indeks CGI
 * @param iNumParams  Liczba parametrow
 * @param pcParam  Tablica parametrow
 * @param pcValue  Tablica wartosci parametrow
 * @return
 */
extern const char *cgi_motor_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

/**
 * @brief Funkcja obslugujaca glosnik PWM
 * @param iIndex Indeks CGI
 * @param iNumParams  Liczba parametrow
 * @param pcParam  Tablica parametrow
 * @param pcValue  Tablica wartosci parametrow
 * @return
 */
extern const char *cgi_pwmspeaker_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

/**
 * @brief Inicjalizacja CGI
 */
extern void cgi_init(void);

#endif // CGI_H