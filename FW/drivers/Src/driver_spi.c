/*
 * ==========================================================================================
 *      File: driver_spi.c
 *      Author: William Sleman
 *
 *      Description:
 *      This source file contains the implementation of functions for configuring and 
 *      managing the Serial Peripheral Interface (SPI). It includes functions for 
 *      initializing the SPI peripheral, controlling its operation, and handling data 
 *      transmission and reception. This implementation supports a variety of configurations 
 *      for SPI communication.
 *
 *      Note:
 *      For details on the structures and function prototypes, see the header file: 
 *      driver_spi.h.
 * ==========================================================================================
 */
#include "driver_spi.h"


/*
 ********************************************************************************************
 * @fn              - SPI_PeriControl
 *
 * @brief           - Enables or disables the clock for the SPI peripheral.
 *
 * @param[in]       - pSPIx: Pointer to the SPI peripheral base address.
 *
 * @param[in]       - EnorDi: Flag indicating whether to enable (ENABLE) or disable (DISABLE) the clock.
 *
 * @return          - none
 *
 * @Note            - none
 *
 ********************************************************************************************
 */
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->ENABLER = 1;
    }else
    {
        pSPIx->ENABLER = 0;
    }
}


/*
 ********************************************************************************************
 * @fn              - SPI_Init
 *
 * @brief           - Initializes the SPI peripheral based on the configuration settings 
 *                    provided in the SPI_Handle_t structure, including pin configuration 
 *                    and SPI parameters (CPHA, CPOL, Frequency).
 *
 * @param[in]       - pSPIHandle: Pointer to a SPI_Handle_t structure containing the 
 *                    configuration settings for the SPI peripheral.
 *
 * @return          - none
 *
 * @Note            - This function sets up pin multiplexing for SCK, MISO, and MOSI, 
 *                    configures the peripheral according to the specified parameters, 
 *                    and enables the SPI peripheral.
 *
 ********************************************************************************************
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    SPI_PeriControl(pSPIHandle->pSPIx, DISABLE);

    // 1, Config pins
    uint8_t psel_port = 0;
    uint32_t temp = 0;

    if(pSPIHandle->SCK.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->SCK.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.SCK = temp;

    psel_port = 0;
    if(pSPIHandle->MISO.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->MISO.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.MISO = temp;

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


/*
 ********************************************************************************************
 * @fn              - SPI_SendData
 *
 * @brief           - Sends data over the SPI bus.
 *
 * @param[in]       - pSPIx: Pointer to the SPI peripheral base address.
 *
 * @param[in]       - pTxBuffer: Pointer to the buffer containing the data to be sent.
 *
 * @param[in]       - Len: The number of bytes to send.
 *
 * @return          - none
 *
 * @Note            - This function continuously waits for the SPI to be ready and sends 
 *                    each byte from the transmission buffer.
 *
 ********************************************************************************************
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t temp = 0;

    pSPIx->EVENTS_READY = 0;
    while(Len)
    {
        pSPIx->TXD = *(pTxBuffer++);
        event_pooling(&pSPIx->EVENTS_READY);
        temp = pSPIx->RXD;

        (void)temp;
        Len--;
    }
}


/*
 ********************************************************************************************
 * @fn              - SPI_ReceiveData
 *
 * @brief           - Receives data over the SPI bus.
 *
 * @param[in]       - pSPIx: Pointer to the SPI peripheral base address.
 *
 * @param[in]       - pRxBuffer: Pointer to the buffer where received data will be stored.
 *
 * @param[in]       - Len: The number of bytes to receive.
 *
 * @return          - none
 *
 * @Note            - This function sends dummy data (0xFF) to generate clock pulses while
 *                    receiving data from the SPI device.
 *
 ********************************************************************************************
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t temp = 0xFF;

    pSPIx->EVENTS_READY = 0;
    while(Len)
    {
        pSPIx->TXD = temp;
        event_pooling(&pSPIx->EVENTS_READY);
        *(pRxBuffer++) = pSPIx->RXD;

        (void)temp;
        Len--;
    }
}