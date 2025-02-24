#ifndef DRIVER_TWI_H_
#define DRIVER_TWI_H_

#include "nrf52.h"

typedef struct
{
	uint32_t FREQUENCY;
}TWI_Config_t;

typedef struct{
    TWI_RegDef_t *pTWIx;
    TWI_Config_t config;
    PSEL_t SCL;
    PSEL_t SDA;
}TWI_Handle_t;

/*
 *@TWI_FREQUENCY
 *Possible options for TWI_Frequency
 */
#define TWI_FREQUENCY_K100      0x01980000U
#define TWI_FREQUENCY_K250      0x04000000U
#define TWI_FREQUENCY_K400      0x06680000U

void TWI_Init(TWI_Handle_t *pTWIHandle);

/*
 * Data send and receive
 */

void TWI_MasterSendData(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);
void TWI_MasterSendDataRS(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);
void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr);

#endif /* DRIVER_I2C_H_ */