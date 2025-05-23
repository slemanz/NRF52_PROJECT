#include "driver_twi.h"

void TWI_Init(TWI_Handle_t *pTWIHandle)
{
    uint8_t psel_port = 0;
    uint32_t temp = 0;
    pTWIHandle->pTWIx->ENABLER = 0;


    if(pTWIHandle->SDA.port == GPIOP1) psel_port = 1;
    temp = ((0 << PSEL_CONNECT) | (psel_port << PSEL_PORT) | (pTWIHandle->SDA.pin << PSEL_PIN));
    pTWIHandle->pTWIx->PSEL.SDA = temp;

    psel_port = 0;
    if(pTWIHandle->SCL.port == GPIOP1) psel_port = 1;
    temp = ((0 << PSEL_CONNECT) | (psel_port << PSEL_PORT) | (pTWIHandle->SCL.pin << PSEL_PIN));
    pTWIHandle->pTWIx->PSEL.SCL = temp;

    pTWIHandle->pTWIx->FREQUENCY = pTWIHandle->config.FREQUENCY;

    pTWIHandle->pTWIx->ENABLER = 6;
}

void TWI_MasterSendData(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;
    pTWIx->SHORTS = (1 << 9);

    pTWIx->TXD.MAXCNT = Len;
    pTWIx->TXD.PTR = (uint32_t)pTxBuffer;

    pTWIx->EVENTS_STOPPED = 0;
    pTWIx->TASKS_STARTTX = 1;
    while (pTWIx->EVENTS_STOPPED == 0);
}

void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;
    pTWIx->SHORTS = (1 << 12);

    pTWIx->RXD.MAXCNT = Len;
    pTWIx->RXD.PTR = (uint32_t)pRxBuffer;

    pTWIx->EVENTS_STOPPED = 0;
    pTWIx->TASKS_STARTRX = 1;
    while (pTWIx->EVENTS_STOPPED == 0);
    
}