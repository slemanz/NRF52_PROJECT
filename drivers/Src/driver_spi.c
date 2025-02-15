#include "driver_spi.h"



void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->ENABLER = (1 << 0);
    }else
    {
        pSPIx->ENABLER = 0;
    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // 1, Config pins
    uint8_t psel_port = 0;
    uint32_t temp = 0;

    if(pSPIHandle->SCK.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->SCK.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.SCK = temp;

    psel_port = 0;
    if(pSPIHandle->MISO.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->MISO.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.SCK = temp;

    psel_port = 0;
    if(pSPIHandle->MOSI.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->MOSI.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.MOSI = temp;

    // 2. config peripheral
    temp = (pSPIHandle->SPI_Config.CPOL << 2) | (pSPIHandle->SPI_Config.CPHA << 1);
    pSPIHandle->pSPIx->CONFIG = temp;
    pSPIHandle->pSPIx->FREQUENCY = pSPIHandle->SPI_Config.Frequency;

    // 3. Init
    SPI_PeriControl(pSPIHandle->pSPIx, ENABLE);
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t temp = 0;

    pSPIx->EVENTS_READY = 0;
    while(Len)
    {
        //pSPIx->TXD = *(pTxBuffer++);
        *((uint8_t*)&pSPIx->TXD) = 0x55;
        //while(!(pSPIx->EVENTS_READY = 0));
        temp = pSPIx->RXD;
        pSPIx->EVENTS_READY = 0;

        (void)temp;
        Len--;
    }
}