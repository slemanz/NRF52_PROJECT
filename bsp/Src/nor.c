#include "nor.h"
#include "driver_spi.h"
#include "driver_gpio.h"


#define NOR_DEBUG
#if defined (NOR_DEBUG)
#include <stdarg.h>
#include <stdio.h>
#endif

#if defined (NOR_DEBUG)
#define NOR_PRINTF(...)			printf(__VA_ARGS__)
#else
#define NOR_PRINTF(...)
#endif

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
    uint8_t cmd = NOR_CMD_SR1;
    uint8_t statusReg;

    _nor_cs_assert();
    _nor_spi_tx((uint8_t*)&cmd, 1);
    _nor_cs_deassert();
    NOR_PRINTF("Nor busy\n");

    _nor_cs_assert();
	_nor_spi_rx(&statusReg, 1);
	do{
		_nor_spi_rx(&statusReg, 1);
	}while ((statusReg & (1 << 0))); // SR1_BUSY_BIT
	_nor_cs_deassert();
    NOR_PRINTF("%x\n", statusReg);
    NOR_PRINTF("Nor not busy\n");
}

void NOR_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
    uint8_t ReadCmd[5];

    if (NumByteToRead == 0)
    {
		return;
	}

    nor_waitBusy();
	ReadCmd[0] = NOR_CMD_READFAST;
	ReadCmd[1] = ((ReadAddr >> 16) & 0xFF);
	ReadCmd[2] = ((ReadAddr >> 8) & 0xFF);
	ReadCmd[3] = ((ReadAddr) & 0xFF);
	ReadCmd[4] = 0x00;

    _nor_cs_assert();
	_nor_spi_tx(ReadCmd, 5);
	_nor_spi_rx(pBuffer, NumByteToRead);

    NOR_PRINTF("Buffer readed from NOR:\n\r");
	NOR_PRINTF("====================== Values in HEX ========================");
	for (uint32_t i = 0; i < NumByteToRead; i++)
	{
		if (i % 16 == 0)
		{
			NOR_PRINTF("\r\n");
			NOR_PRINTF("0x%08X | ", (uint8_t)(ReadAddr + i));
		}
		NOR_PRINTF("%02X ", pBuffer[i]);
	}
	NOR_PRINTF("\n\r=============================================================\n\r");
}