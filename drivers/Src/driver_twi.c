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
        while(pTWIx->EVENTS_TXDSENT == 0)
        {
            if(pTWIx->EVENTS_ERROR)
            {
                pTWIx->EVENTS_ERROR = 0;
                break;
            }
        }
        pTWIx->EVENTS_TXDSENT = 0;
        Len--;
    } while (Len);
    pTWIx->TASKS_STOP = 1;
    event_pooling(&pTWIx->EVENTS_STOPPED);
}

void TWI_MasterSendDataRS(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;

    pTWIx->TASKS_STARTTX = 1;
    do
    {
        pTWIx->TXD = *(pTxBuffer++);
        while(pTWIx->EVENTS_TXDSENT == 0)
        {
            if(pTWIx->EVENTS_ERROR)
            {
                pTWIx->EVENTS_ERROR = 0;
                break;
            }
        }
        pTWIx->EVENTS_TXDSENT = 0;
        Len--;
    } while (Len);
}

void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr)
{
    if(pTWIx->EVENTS_RXDREADY == 1) pTWIx->EVENTS_RXDREADY = 0;
    pTWIx->ADDRESS = SlaveAddr;

    pTWIx->TASKS_STARTRX = 1;
    do
    {
       *(pRxBuffer) = (uint8_t)(0xFF & pTWIx->RXD);
       pRxBuffer++;
        while(pTWIx->EVENTS_RXDREADY == 0)
        {
            if(pTWIx->EVENTS_ERROR)
            {
                pTWIx->EVENTS_ERROR = 0;
                break;
            }
        }
       pTWIx->EVENTS_RXDREADY = 0;

        
        Len--;
    }while(Len);
    pTWIx->TASKS_STOP = 1;
    event_pooling(&pTWIx->EVENTS_STOPPED);
}