/*
 * =====================================================================
 *              File:           nor.c
 *              Author:         William Sleman
 *              Description:    nor source file
 * =====================================================================
 */
#include "nor.h"
#include "driver_spi.h"
#include "driver_gpio.h"


//#define NOR_DEBUG
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

static void _nor_WriteEnable(void)
{
	uint8_t WriteEnCmd = NOR_CMD_WRITE_EN;

	_nor_cs_assert();
	_nor_spi_tx(&WriteEnCmd, 1);
	_nor_cs_deassert();
}

void _nor_WriteDisable(void)
{
	uint8_t WriteDisCmd = NOR_CMD_WRITE_DIS;

	_nor_cs_assert();
	_nor_spi_tx(&WriteDisCmd, 1);
	_nor_cs_deassert();
}

void nor_waitBusy(void)
{
    uint8_t cmd = NOR_CMD_SR1;
    uint8_t statusReg;

	do{
        _nor_cs_assert();
        _nor_spi_tx((uint8_t*)&cmd, 1);
		_nor_spi_rx(&statusReg, 1);
        _nor_cs_deassert();
	}while ((statusReg & (1 << 0))); // SR1_BUSY_BIT
}

/* ================================================================================ */
/* ================           NOR READ FUNCTIONS                   ================ */
/* ================================================================================ */

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
    _nor_cs_deassert();

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
void NOR_ReadPage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumByteToRead)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_PAGE)
    {
		PageAddr++;
		Offset -= NOR_SIZE_PAGE;
	}

	Address = (PageAddr * NOR_SIZE_PAGE) + Offset;
	NOR_ReadBytes(pBuffer, Address, NumByteToRead);
}

void NOR_ReadSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumByteToRead)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_SECTOR){
		SectorAddr++;
		Offset -= NOR_SIZE_SECTOR;
	}

	Address = (SectorAddr * NOR_SIZE_SECTOR) + Offset;
	NOR_ReadBytes(pBuffer, Address, NumByteToRead);
}

void NOR_ReadBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumByteToRead)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_BLOCK){
		BlockAddr++;
		Offset -= NOR_SIZE_BLOCK;
	}

	Address = (BlockAddr * NOR_SIZE_BLOCK) + Offset;
	NOR_ReadBytes(pBuffer, Address, NumByteToRead);
}

/* ================================================================================ */
/* ================           NOR ERASE FUNCTIONS                  ================ */
/* ================================================================================ */

void NOR_EraseAddress(uint32_t Address, nor_erase_method_e method){
	uint8_t EraseChipCmd[4];

	switch (method){
	case NOR_ERASE_4K:
		NOR_PRINTF("Erasing 4 KBytes on 0x%08X Address... ", (uint8_t)Address);
		EraseChipCmd[0] = NOR_SECTOR_ERASE_4K;
		break;
	case NOR_ERASE_32K:
		NOR_PRINTF("Erasing 32 KBytes on 0x%08X Address... ", (uint8_t)Address);
		EraseChipCmd[0] = NOR_SECTOR_ERASE_32K;
		break;
	case NOR_ERASE_64K:
		NOR_PRINTF("Erasing 64 KBytes on 0x%08X Address... ", (uint8_t)Address);
		EraseChipCmd[0] = NOR_SECTOR_ERASE_64K;
		break;
	}
	EraseChipCmd[1] = ((Address >> 16) & 0xFF);
	EraseChipCmd[2] = ((Address >> 8) & 0xFF);
	EraseChipCmd[3] = ((Address) & 0xFF);

	//_nor_mtx_lock(nor);
	_nor_WriteEnable();
	_nor_cs_assert();
	_nor_spi_tx(EraseChipCmd, 4);
	_nor_cs_deassert();

	nor_waitBusy();

	_nor_WriteDisable();
		
    NOR_PRINTF("Erased complete\n");
}

void NOR_EraseSector(uint32_t SectorAddr){
	uint32_t Address;


	Address = SectorAddr * NOR_SIZE_SECTOR;
	return NOR_EraseAddress(Address, NOR_ERASE_4K);
}

void NOR_EraseBlock(uint32_t BlockAddr){
	uint32_t Address;

	Address = BlockAddr * NOR_SIZE_BLOCK;
	return NOR_EraseAddress(Address, NOR_ERASE_64K);
}

/* ================================================================================ */
/* ================           NOR WRITE FUNCTIONS                  ================ */
/* ================================================================================ */

void NOR_WriteBytes(uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumBytesToWrite)
{
	uint8_t WriteCmd[4];
	uint32_t _BytesToWrite;


	if (NumBytesToWrite == 0){
		NOR_PRINTF("ERROR: Invalid parameters on NOR_WriteBytes\n\r");
		return;
	}
	// TODO check if Address is not grater than the Flash size
	NOR_PRINTF("Writing %d bytes into Address %08X.\n\r", (uint8_t)NumBytesToWrite, (uint8_t)WriteAddr);
	NOR_PRINTF("Buffer to Write into Flash:\n\r");
	NOR_PRINTF("====================== Values in HEX ========================");
	for (uint32_t i = 0; i < NumBytesToWrite; i++)
	{
		if (i % 16 == 0)
		{
			NOR_PRINTF("\r\n");
			NOR_PRINTF("0x%08X | ", (uint8_t)(WriteAddr + i));
		}
		NOR_PRINTF("%02X ", pBuffer[i]);
	}
	NOR_PRINTF("\n\r=============================================================\n\r");

	do{
		// Wait for Busy is deasserted to write any information
		nor_waitBusy();

		if (((WriteAddr%256)+NumBytesToWrite) > 256){
            _BytesToWrite = 256 - (256); // 256 = page size
        }
        else
        {
            _BytesToWrite = NumBytesToWrite;
        }
        _nor_WriteEnable();
		nor_waitBusy();
		WriteCmd[0] = NOR_PAGE_PROGRAM;
		WriteCmd[1] = ((WriteAddr >> 16) & 0xFF);
		WriteCmd[2] = ((WriteAddr >> 8) & 0xFF);
		WriteCmd[3] = ((WriteAddr) & 0xFF);
		_nor_cs_assert();
		_nor_spi_tx(WriteCmd, sizeof(WriteCmd));
		_nor_spi_tx(pBuffer, _BytesToWrite);
		_nor_cs_deassert();
		pBuffer += _BytesToWrite;
		WriteAddr += _BytesToWrite;
		NumBytesToWrite -= _BytesToWrite;

        _nor_WriteDisable();
		nor_waitBusy();
	}while (NumBytesToWrite > 0);
	// release the routine only when the data is writted
	nor_waitBusy();
	NOR_PRINTF("Write done.!\n\r\n\r");
}

void NOR_WritePage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumBytesToWrite)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_PAGE)
	{
		PageAddr++;
		Offset -= NOR_SIZE_PAGE;
	}

	Address = (PageAddr * NOR_SIZE_PAGE) + Offset;
	NOR_WriteBytes(pBuffer, Address, NumBytesToWrite);
}


void NOR_WriteSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumBytesToWrite)
{
	int32_t Address;

	while (Offset >= NOR_SIZE_SECTOR)
	{
		SectorAddr++;
		Offset -= NOR_SIZE_SECTOR;
	}

	Address = (SectorAddr * NOR_SIZE_SECTOR) + Offset;
	NOR_WriteBytes(pBuffer, Address, NumBytesToWrite);
}


void NOR_WriteBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumBytesToWrite)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_BLOCK)
	{
		BlockAddr++;
		Offset -= NOR_SIZE_BLOCK;
	}

	Address = (BlockAddr * NOR_SIZE_BLOCK) + Offset;
	NOR_WriteBytes(pBuffer, Address, NumBytesToWrite);
}