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
        while(pTWIx->EVENTS_TXDSENT == 0)
        {
            if(pTWIx->EVENTS_ERROR)
            {
                pTWIx->EVENTS_ERROR = 0;
                break;
            }
        }
        pTWIx->EVENTS_TXDSENT = 0;

        pTWIx->TXD = *(pTxBuffer++);
        Len--;
    } while (Len);
}

void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;

    pTWIx->TASKS_STARTRX = 1;

    for (uint8_t i = 0; i < Len; i++)
    {
        // Wait until the RX buffer is ready
        while (!pTWIx->EVENTS_RXDREADY)
        {
            if(pTWIx->EVENTS_ERROR)
            {
                pTWIx->EVENTS_ERROR = 0;
                break;
            }
        }

        pTWIx->TASKS_SUSPEND = 1;
        while(pTWIx->EVENTS_SUSPENDED == 0);
        pTWIx->EVENTS_SUSPENDED = 0;

        pRxBuffer[i] = (uint8_t)pTWIx->RXD;
        pTWIx->EVENTS_RXDREADY = 0;
        pTWIx->TASKS_RESUME = 1;

    }
    
    // Stop the reception
    pTWIx->TASKS_STOP = 1;

    //uint8_t temp = 0;
    //(void)(temp = (uint8_t)pTWIx->RXD);
    
    // Wait until the stop condition is sent
    while (!pTWIx->EVENTS_STOPPED);
    pTWIx->EVENTS_STOPPED = 0;
}