#include "nor.h"
#include "driver_spi.h"
#include "driver_gpio.h"
#include <stdio.h>

#define NOR_SPI                 SPI0
#define NOR_CS_PORT             GPIOP0
#define NOR_CS_PIN              GPIO_PIN_NO_27

static void _nor_cs_assert(void)
{
    GPIO_WriteToOutputPin(NOR_CS_PORT, NOR_CS_PIN, GPIO_PIN_RESET);
}

static void _nor_cs_deassert(void)
{
    GPIO_WriteToOutputPin(NOR_CS_PORT, NOR_CS_PIN, GPIO_PIN_SET);
}

static void _nor_spi_tx(uint8_t *txBuf, uint32_t size)
{
    SPI_SendData(NOR_SPI, txBuf, size);
}

static void _nor_spi_rx(uint8_t *rxBuf, uint32_t size)
{
    SPI_ReceiveData(NOR_SPI, rxBuf, size);
}

void nor_waitBusy(void)
{
    uint8_t cmd = 0x05; // NOR_CMD_SR1
    uint8_t statusReg;

    _nor_cs_assert();
    _nor_spi_tx((uint8_t*)&cmd, 1);
    _nor_cs_deassert();
    printf("Nor busy\n");

    _nor_cs_assert();
	_nor_spi_rx(&statusReg, 1);
	do{
		_nor_spi_rx(&statusReg, 1);
	}while ((statusReg & (1 << 0))); // SR1_BUSY_BIT
	_nor_cs_deassert();
    printf("Nor not busy\n");
}