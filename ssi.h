#ifndef SSI_H
#define SSI_H

#include "lwip/arch.h"

/**
 * @brief Fumkcja obslugujaca SSI wykonywana podczas odswiezenia strony
 * @param iIndex Indeks tagu SSI
 * @param pcInsert Wartosc tagu SSI
 * @param iInsertLen Dlugosc tagu SSI
 * @return
 */
static u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);

/**
 * @brief Inicjalizacja SSI
 */
extern void ssi_init(void);

#endif // SSI_H