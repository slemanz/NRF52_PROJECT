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

#define NOR_CMD_SR1					0x05

#define NOR_CMD_READFAST			0x0B


/* ================================================================================ */
/* ================                NOR FUNCTIONS                   ================ */
/* ================================================================================ */

void nor_init(void);
void nor_waitBusy(void);
void nor_erase_chip(void);

void nor_eraseAddress(uint32_t Address, nor_erase_method_e method);
void nor_eraseSector(uint32_t SectorAddr);
void nor_eraseBlock(uint32_t BlockAddr);

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