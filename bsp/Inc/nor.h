#ifndef NOR_H_
#define NOR_H_

#include <stdint.h>

typedef enum{
	NOR_ERASE_4K, /**< NOR_ERASE_4K */
	NOR_ERASE_32K,/**< NOR_ERASE_32K */
	NOR_ERASE_64K /**< NOR_ERASE_64K */
}nor_erase_method_e;


/* ================================================================================ */
/* ================             	  NOR COMMANDS 	               ================ */
/* ================================================================================ */

#define NOR_CMD_WRITE_EN			0x06
#define NOR_CMD_WRITE_DIS			0x04

#define NOR_SECTOR_ERASE_4K			0x20
#define NOR_SECTOR_ERASE_32K		0x52
#define NOR_SECTOR_ERASE_64K		0xD8
#define NOR_CHIP_ERASE				0xC7

#define NOR_CMD_SR1					0x05

#define NOR_CMD_READFAST			0x0B
#define NOR_PAGE_PROGRAM			0x02


/* ================================================================================ */
/* ================                NOR FUNCTIONS                   ================ */
/* ================================================================================ */

void nor_init(void);
void nor_waitBusy(void);
void nor_Erase_chip(void);

void NOR_EraseAddress(uint32_t Address, nor_erase_method_e method);
void NOR_EraseSector(uint32_t SectorAddr);
void NOR_EraseBlock(uint32_t BlockAddr);

/* **********************************
 * Memory programming functions
 * **********************************/

void NOR_WriteBytes(uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumBytesToWrite);
void NOR_WritePage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumBytesToWrite);
void NOR_WriteSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumBytesToWrite);
void NOR_WriteBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumBytesToWrite);

/* **********************************
 * Memory read functions
 * **********************************/

void NOR_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void NOR_ReadPage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumByteToRead);
void NOR_ReadSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumByteToRead);
void NOR_ReadBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumByteToRead);


#endif /* NOR_H_ */