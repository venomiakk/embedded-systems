#ifndef SSI_H
#define SSI_H

#include "lwip/arch.h"

static u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);

extern void ssi_init(void);

#endif // SSI_H