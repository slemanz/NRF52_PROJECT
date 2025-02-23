#include "driver_twi.h"

void TWI_Init(TWI_Handle_t *pTWIHandle)
{
    uint8_t psel_port = 0;
    uint32_t temp = 0;


    if(pTWIHandle->SDA.port == GPIOP1) psel_port = 1;
    temp = ((0 << PSEL_CONNECT) | (psel_port << PSEL_PORT) | (pTWIHandle->SDA.pin << PSEL_PIN));
    pTWIHandle->pTWIx->PSEL.SDA = temp;

    psel_port = 0;
    if(pTWIHandle->SCL.port == GPIOP1) psel_port = 1;
    temp = ((0 << PSEL_CONNECT) | (psel_port << PSEL_PORT) | (pTWIHandle->SCL.pin << PSEL_PIN));
    pTWIHandle->pTWIx->PSEL.SCL = temp;

    pTWIHandle->pTWIx->FREQUENCY = pTWIHandle->config.FREQUENCY;

    pTWIHandle->pTWIx->ENABLER = 5;
}

void TWI_MasterSendData(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;

    pTWIx->TASKS_STARTTX = 1;
    do
    {
        pTWIx->TXD = *(pTxBuffer++);
        event_pooling(&pTWIx->EVENTS_TXDSENT);
        
        Len--;
    } while (Len);
    pTWIx->TASKS_STOP = 1;
    event_pooling(&pTWIx->EVENTS_STOPPED);
    
}

void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr)
{

}