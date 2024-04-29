#ifndef CGI_H
#define CGI_H


extern const char *cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

extern const char *cgi_servo_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

extern const char *cgi_motor_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

extern const char *cgi_pwmspeaker_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

extern void cgi_init(void);

#endif // CGI_H